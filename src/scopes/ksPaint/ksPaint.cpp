#include <scopes/ksPaint/ksPaint.h>
#include <ks/utility/ksSettings.h>
#include <ks/ui/ksMessageQueue.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksPaint);

ksPaint::ksPaint()
{
    
}

ksPaint::~ksPaint()
{
    
}

void ksPaint::init()
{
    bTranslateMousePosition = true;
    bClear = false;
    
    initPaint1();
    ppmouseX=ofGetMouseX();
    ppmouseY=ofGetMouseY();
    initSetting();
    
    gui->addButton("Clear");
    gui->addButton("Paint1");
    gui->addButton("Paint2");
}

void ksPaint::initPaint1()
{
    med_mouseX=ofGetMouseX();
    med_mouseY=ofGetMouseY();
    old_mouseX=0;
    old_mouseY=0;
    red=ofRandom(0,255);
    is_pressed=false;
    cout=0;
}

void ksPaint::initMesh(ofPoint p1,ofPoint p2,ofPoint p3)
{
    ofDisableArbTex();
    _myMesh[cout].addVertex(p1);
    _myMesh[cout].addVertex(p2);
    _myMesh[cout].addVertex(p3);
    
    _myMesh[cout].addTexCoord(ofVec2f(0,1));
    _myMesh[cout].addTexCoord(ofVec2f(1,1));
    _myMesh[cout].addTexCoord(ofVec2f(1,0.5));
    
    ofIndexType ids[3] =
    {
        0,1,2
    };
    _myMesh[cout].addIndices(ids,3);
    
}

void ksPaint::drawPaint1(float dY)
{
    //mouseX=ofGetMouseX();
    //mouseY=ofGetMouseY();
    
    pmouseX = mouseX;
    pmouseY = mouseY;
    
    mouseX = (ofGetMouseX() - 396.0 * ofGetWidth() / 2048.0) * ofGetWidth() / (1624.0 * ofGetWidth() / 2048.0);
    mouseY = (ofGetMouseY() - 28.0 * ofGetWidth() / 2048.0) * ofGetHeight() / (1480.0 * ofGetHeight() / 1536.0);

    //pmouseX = ofGetPreviousMouseX();
    //pmouseY = ofGetPreviousMouseY();
    
    if(GUIShapeOfMesh == 0)
    {
        med_mouseX=(mouseX+pmouseX)*0.5+ofRandom(-40,40);
        med_mouseY=(mouseY+pmouseY)*0.5+ofRandom(-40,40);
        
        if(is_pressed){
            if(old_mouseX==0){
                old_mouseX=mouseX;
            }
            if(old_mouseY==0){
                old_mouseY=mouseY;
            }
            
            initMesh(ofPoint(old_mouseX,old_mouseY),ofPoint(med_mouseX,med_mouseY),ofPoint(pmouseX,pmouseY));
            //cout<<mouseX<<"---"<<mouseY<<"---"<<med_mouseX<<"---"<<med_mouseY<<"---"<<pmouseX<<"---"<<pmouseY<<"---"<<endl;
            T.bind();
            ofPushStyle();
            ofSetColor(ofRandom(0,255),0,0,ofRandom(100,255));
            _myMesh[cout].draw();
            ofPopStyle();
            cout++;
            T.unbind();
            
            ofPushStyle();
            ofSetColor(ofRandom(0,255),0,0,ofRandom(50,180));
            
            ofBeginShape();
            ofVertex(mouseX,mouseY);
            ofVertex(med_mouseX,med_mouseY);
            ofVertex(pmouseX,pmouseY);
            ofEndShape();
            ofPopStyle();
            
            initMesh(ofPoint(mouseX,mouseY),ofPoint(med_mouseX,med_mouseY),ofPoint(pmouseX,pmouseY));
            T.bind();
            ofPushStyle();
            ofSetColor(ofRandom(0,255),0,0,ofRandom(100,200));
            _myMesh[cout].draw();
            ofPopStyle();
            cout++;
            T.unbind();
            
            ofPushStyle();
            ofFill();
            ofSetColor(ofRandom(0,255),0,0,ofRandom(0,255));
            ofBeginShape();
            ofVertex(med_mouseX,med_mouseY);
            ofVertex(pmouseX,pmouseY);
            ofVertex(old_mouseX,old_mouseY);
            ofEndShape();
            ofPopStyle();
            
            old_mouseX=med_mouseX;
            old_mouseY=med_mouseY;
        }
    }
    //pen2
    else if (GUIShapeOfMesh ==1)
    {
        if(is_pressed)
        {
            float d = ofPoint(mouseX, mouseY).distance( ofPoint(pmouseX, pmouseY));
            // distance between pmouseX and ppmouseX
            float pd = ofPoint(pmouseX, pmouseY).distance( ofPoint(ppmouseX, ppmouseY));
            
            // deltaX and deltaY
            float deltaX = mouseX-pmouseX;
            float deltaY = mouseY-pmouseY;
            float pdeltaX = pmouseX-ppmouseX;
            float pdeltaY = pmouseY-ppmouseY;
            
            // daltaX/2
            float midPointx = mouseX-deltaX/2;
            float midPointy = mouseY-deltaY/2;
            float pmidPointx = pmouseX-pdeltaX/2;
            float pmidPointy = pmouseY-pdeltaY/2;
            
            // angle between mouseX mouseY
            // atan2(deltaY, deltaX)
            float directionAngle = atan2(deltaY, deltaX);
            float pdirectionAngle = atan2(pdeltaY, pdeltaX);
            
            float x = d * cos(ofRadToDeg(90) + directionAngle);
            float y = d * sin(ofRadToDeg(90) + directionAngle);
            float px = pd * cos(ofRadToDeg(90) + pdirectionAngle);
            float py = pd * sin(ofRadToDeg(90) + pdirectionAngle);
            
            initMesh(ofPoint(pmouseX, pmouseY),ofPoint(midPointx+x, midPointy+y),ofPoint(mouseX, mouseY));
            T.bind();
            ofPushStyle();
            ofSetColor(ofRandom(0,255),255,255,ofRandom(200,250));
            _myMesh[cout].draw();
            ofPopStyle();
            cout++;
            
            initMesh(ofPoint(pmouseX, pmouseY),ofPoint(midPointx-x, midPointy-y),ofPoint(mouseX,mouseY));
            T.bind();
            ofPushStyle();
            ofSetColor(ofRandom(0,255),255,255,ofRandom(200,250));
            _myMesh[cout].draw();
            ofPopStyle();
            cout++;
            
            initMesh(ofPoint(pmouseX,pmouseY),ofPoint(midPointx+x, midPointy+y),ofPoint(pmidPointx+px, pmidPointy+py));
            T.bind();
            ofPushStyle();
            ofSetColor(ofRandom(0,255),255,255,ofRandom(200,250));
            _myMesh[cout].draw();
            ofPopStyle();
            cout++;
            
            initMesh(ofPoint(pmouseX,pmouseY),ofPoint(midPointx-x, midPointy-y),ofPoint(pmidPointx-px, pmidPointy-py));
            T.bind();
            ofPushStyle();
            ofSetColor(ofRandom(0,255),255,255,ofRandom(200,250));
            _myMesh[cout].draw();
            ofPopStyle();
            cout++;
            
            //create a previous-previous mouseX
            ppmouseX = pmouseX;
            ppmouseY = pmouseY;
        }
    }
}

void ksPaint::copySrcToFbo(float w, float h)
{
    ofBaseDraws *pDrawSrc = ksResource::getResource();
    
    if(!fbo.isAllocated())
    {
        fbo.allocate(pDrawSrc->getWidth(),pDrawSrc->getHeight(),GL_RGBA);
        ofBackgroundGradient(ofColor(255), ofColor(128));
    }
    
    fbo.begin();
    ofClear(0,0,0,0);
    pDrawSrc->draw(0,0,fbo.getWidth(),fbo.getHeight());
    fbo.end();
    T = fbo.getTextureReference();
}

void ksPaint::draw( int x, int y, int width, int height)
{
    if (clear)
    {
        clear=false;
        ofBackgroundGradient(ofColor(255), ofColor(128));
    }
    
    copySrcToFbo(width, height);
    drawPaint1(160);
}

void ksPaint::update(float dt)
{
    guiEvent();
}

void ksPaint::mouseDragged( int x, int y, int button )
{
    
}

void ksPaint::mousePressed( int x, int y, int button)
{
    if(x < 0 || y < 0 )
        return;
    
    med_mouseX=x;
    med_mouseY=y;
    old_mouseX=x;
    old_mouseY=y;
    
    is_pressed=true;
}

void ksPaint::mouseReleased(int x, int y, int button )
{
    if(x < 0 || y < 0 )
        return;
    
    is_pressed=false;
}

ofPoint ksPaint::getCenterOfScreen()
{
    ofPoint Center = ofVec2f(ofGetWidth()/2,ofGetHeight()/2);
    return Center;
}

void ksPaint::guiEvent()
{
    if(ksMessageQueue::messages.size() > 0)
    {
        for(int i=0; i<ksMessageQueue::messages.size(); i++)
        {
            if(!strcmp("Clear", ksMessageQueue::messages[i].c_str()))
            {
                _myMesh->clear();
                clear=true;
            }
            else if(!strcmp("Paint1", ksMessageQueue::messages[i].c_str()))
            {
                GUIShapeOfMesh = 0;
            }
            else if(!strcmp("Paint2", ksMessageQueue::messages[i].c_str()))
            {
                GUIShapeOfMesh = 1;
            }
        }
    }
}

void ksPaint::initSetting()
{
    paint1=true;
    paint2=false;
    clear=false;
    GUIShapeOfMesh = 0;
}