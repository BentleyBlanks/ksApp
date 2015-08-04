#include <scopes/ksPalette/ksPalette.h>
#include <ks/utility/ksSettings.h>
#include <ks/ui/ksMessageQueue.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksPalette);

ksPalette::~ksPalette()
{
    
}

ksPalette::ksPalette()
{

}

void ksPalette::init()
{
    // to use uniform texture coordinates
    ofDisableArbTex();
    bTranslateMousePosition = true;
    
    Index = 0;
    initGUIValues();
    sound = ksResource::getMusic("ksPalette", "backgroud.mp3");
    sound->setLoop(true);
    //sound->play();
    
    bdrag = false;
    bpressed=false;
    spectrum=1;
    
    NPolygonSlider = gui->addSlider("NPolygon", 3, 20, &GUIN);
    gui->addButton("PointFace");
    gui->addButton("Point");
    gui->addButton("");
    gui->addButton("");
    gui->addButton("PointDrag");
    
    gui->addButton("Clear");
}

void ksPalette::update( float dt )
{
    guiEvent();
}

void ksPalette::draw(int x, int y, int w, int h)
{
    copySrcToFbo(w, h);
    
    halfW = w/2;
    halfH = h/2;
    //ofClear(ofColor(255,255,255, 255));
    //ofBackgroundGradient(ofColor(255), ofColor(128));
    
    for (int i = 0; i < mesh.size(); i ++)
    {
        ofPushMatrix();
        ofPushStyle();
        ofPushView();
        ofTranslate(halfW, halfH);
        ofScale(w/10*(1.0),h/10*(1.0),1.0f);
        if(ChooseIndex[i]==3/*GUIChooseIndex==3*/){
            ofTranslate(centerPoints[i]);
            //	ofRotate(RotateDeg[i]);
            for(int an=0;an<360;an=an+40)
            {
                for (int j=0;j<9;j++)
                {
                    ofPushMatrix();
                    ofPushStyle();
                    ofPushView();
                    
                    ofEnableDepthTest();
                    ofSoundUpdate();
                    float *val = ofSoundGetSpectrum(ofClamp(i*15+j*8+8,1,256));
                    
                    spectrum = 100* val[8];
                    ofRotateY(an+100*spectrum);
                    ofRotateX(an+61.8*spectrum);
                    ofRotateZ(an+33.2*spectrum);
                    
                    float Posx=ofClamp(100*spectrum,0.2,1.5)*cos(j);
                    float Posy=ofClamp(100*spectrum,0.2,1.5)*sin(j);
                    
                    ofTranslate(Posx,Posy);
                    fbo.getTextureReference().bind();
                    //ofSetColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255),100);
                    mesh[i].draw();
                    fbo.getTextureReference().unbind();
                    ofDisableDepthTest();
                    
                    ofPopMatrix();
                    ofPopStyle();
                    ofPopView();
                }
            }
        }
        else if(ChooseIndex[i]==0/*GUIChooseIndex==0*/){
            fbo.getTextureReference().bind();
            mesh[i].draw();
            fbo.getTextureReference().unbind();
        }
        else if(ChooseIndex[i]==4/*GUIChooseIndex==4*/){
            ofTranslate(centerPoints[i]);
            ofRotate(RotateDeg[i]);
            fbo.getTextureReference().bind();
            mesh[i].draw();
            fbo.getTextureReference().unbind();
        }
        ofPopMatrix();
        ofPopStyle();
        ofPopView();
        
    }
    for (int j = 0; j < PressPoint.size(); j ++){
        ofPushMatrix();
        ofPushStyle();
        ofPushView();
        ofSetColor(ofColor::red);
        ofTranslate(halfW, halfH);
        ofScale(w/10*(1.0),h/10*(1.0),1.0f);
        ofCircle(PressPoint[j], 0.05);
        ofPopMatrix();
        ofPopStyle();
        ofPopView();
    }
    if (bdrag)
    {
        ofPushMatrix();
        ofPushStyle();
        ofPushView();
        
        ofSetColor(ofColor::red);
        ofTranslate(halfW, halfH);
        ofScale(w/10*(1.0),h/10*(1.0),1.0f);
        
        ofNoFill();
        ofCircle(centerPoints[Index], 0.1);
        ofCircle(tempPoint, 0.1);
        ofLine(centerPoints[Index],tempPoint);
        
        ofPopMatrix();
        ofPopStyle();
        ofPopView();
    }
}

void ksPalette::mouseDragged( int x, int y, int button )
{
    if(x < 0 || y < 0 )
        return;
    
    if(GUIChooseIndex==4)
    {
        ofPoint p(x, y);
        p.x = ofMap(p.x, 0, fbo.getWidth(), -5, 5);
        p.y = ofMap(p.y, 0, fbo.getHeight(), -5, 5);
        
        r[Index] = ofDist(centerPoints[Index].x, centerPoints[Index].y, p.x, p.y);
        if (p.x - centerPoints[Index].x != 0)
            RotateDeg[Index] = atan((p.y - centerPoints[Index].y)/(p.x - centerPoints[Index].x));
        else
            RotateDeg[Index] = 0;
        RotateDeg[Index] *= 180/PI;
        initMesh(Index);
        tempPoint = p;
        
        bdrag = true;
    }
}

void ksPalette::mousePressed( int x, int y, int button)
{
    if(x < 0 || y < 0 )
        return;
    
    ofCircle(x,y,1);
    bpressed=true;
    ofPoint p(x, y);
    p.x = ofMap(p.x, 0, fbo.getWidth(), -5, 5);
    p.y = ofMap(p.y, 0, fbo.getHeight(), -5, 5);
    centerPoints.push_back(p);
    NowPos=ofVec2f(x,y);
    initSettings();
    if(GUIChooseIndex==0||GUIChooseIndex==3){
        if(GUIChooseIndex==0)
            PressPoint.push_back(p);
        initMesh(Index);
    }
}

void ksPalette::mouseReleased(int x, int y, int button )
{
    if(x < 0 || y < 0 )
        return;
    
    bpressed=false;
    bdrag = false;
    Index ++;
}

void ksPalette::guiEvent()
{
    if(ksMessageQueue::messages.size() > 0)
    {
        for(int i=0; i<ksMessageQueue::messages.size(); i++)
        {
            if(!strcmp("PointFace", ksMessageQueue::messages[i].c_str()))
            {
                GUIChooseIndex = 0;
            }
            else if(!strcmp("Point", ksMessageQueue::messages[i].c_str()))
            {
                GUIChooseIndex = 1;
            }
            else if(!strcmp("PointDrag", ksMessageQueue::messages[i].c_str()))
            {
                GUIChooseIndex = 2;
            }
            else if(!strcmp("NPolygon", ksMessageQueue::messages[i].c_str()))
            {
                GUIN = NPolygonSlider->getValue();
            }
            else if(!strcmp("Clear", ksMessageQueue::messages[i].c_str()))
            {
                clear();
            }
        }
    }
}


void ksPalette::initGUIValues()
{
    GUIChooseIndex=0;
    GUIN=3;
}

void ksPalette::initSettings()
{
    r.push_back(0.1);
    n.push_back(GUIN);
    RotateDeg.push_back(0);
    //	PressPoint.push_back(ofPoint(0,0));
    ChooseIndex.push_back(GUIChooseIndex);
    mesh.push_back(*new ofMesh);
}

void ksPalette::initMesh(int i)
{
    switch (GUIChooseIndex)
    {
        case 0:
            CreatFace(i);
            break;
        case 1:
            initLine(i);
            break;
        case 2:
            initFace(i);
            break;
        case 3:
        case 4:
            initPolygon(i);
            break;
    }
}

void ksPalette::CreatFace(int i)
{
    mesh[i].clear();
    for (int j = 0;j < PressPoint.size(); j++)
    {
        //ofSetColor(ofRandom(0,255),ofRandom(0,255),ofRandom(0,255),128);
        ofFloatColor a(ofRandom(128,255),ofRandom(128,255),ofRandom(128,255),255);
        mesh[i].addColor(a);
        
        mesh[i].addVertex(PressPoint[j]);
        mesh[i].addTexCoord(ofPoint(ofRandom(0,1),ofRandom(0,1)));
        
    }
}

void ksPalette::initPolygon(int i)
{
    mesh[i].clear();
    float st;
    st=(360.0/n[i])*(3.14/180);
    
    for(int j=0;j<n[i]+1;j++)
    {
        ofPoint R(r[i]*cos(j*st),r[i]*sin(j*st),0);
        ofPoint R1(r[i]*cos((j+1)*st),r[i]*sin((j+1)*st),0);
        ofPoint O(0,0,0);
        
        mesh[i].addVertex(O);
        mesh[i].addVertex(R);
        mesh[i].addVertex(R1);
        
        ofPoint T1(0,0);
        ofPoint T2(0,1);
        ofPoint T3(1,1);
        
        mesh[i].addTexCoord(T1);
        mesh[i].addTexCoord(T2);
        mesh[i].addTexCoord(T3);
    }
}

void ksPalette::initLine(int i)
{
    
}

void ksPalette::initFace(int i)
{
    
}

void ksPalette::clear()
{
    ChooseIndex.clear();
    mesh.clear();
    PressPoint.clear();
    centerPoints.clear();
    RotateDeg.clear();
    r.clear();
    n.clear();
    Index = 0;
}

void ksPalette::copySrcToFbo(float w, float h)
{
    ofBaseDraws *pDraw = ksResource::getResource();
    
    if(!fbo.isAllocated())
    {
        fbo.allocate(w,h,GL_RGBA);
        fbo.getTextureReference().setTextureWrap(
                                                 GL_MIRRORED_REPEAT,GL_MIRRORED_REPEAT);
        ofClear(ofColor(255,255,255, 255));
        //centerPoints.push_back(ofPoint(w/2, h/2));
    }
    
    fbo.begin();
    ofClear(255, 255, 255);
    pDraw->draw(0,0,fbo.getWidth(),fbo.getHeight());
    fbo.end();
}





