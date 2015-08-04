#include <scopes/ksShaderPalette/ksShaderPalette.h>

#include <ks/utility/ksSettings.h>
#include <ks/ui/ksMessageQueue.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksShaderPalette)

ksShaderPalette::~ksShaderPalette()
{
    
}

ksShaderPalette::ksShaderPalette()
{
    
}

void ksShaderPalette::init()
{
    // 不需要系统自动清屏
    //bCleard = false;
    bTranslateMousePosition = true;
    
    // to use uniform texture coordinates
    ofDisableArbTex();
    shader = ksResource::getShader("ksShaderPalette", "palette");
    
    useTime = false;
    doRotate = false;
    isDrawing = false;
    isBrush = false, isClick = true;
    speed = 0.1;
    index = 0;
    initGUIValues();
    //initSettings();
    //initMesh(index);
    
    spectrum = 0.0001f;
    isPlaySound = false;
    //sound.loadSound( "surface.wav" );
    sound = ksResource::getMusic("ksShaderPalette", "surface.wav");
    sound->setLoop(true);
    //sound->play();
    
    radiusSlider = gui->addSlider("Radius", 0.0, 4.0, &GUIRadius);
    rotateDegSlider = gui->addSlider("RotateDeg", 0, 360, &GUIRotateDeg);
    segmentNumSlider = gui->addSlider("SegmentNum", 2, 20, GUISegmentNum);
    
    speedSlider = gui->addSlider("Speed", 0.0, 1.0, speed);
    parameterASlider = gui->addSlider("ParameterA", 0.0, 5.0, &GUIparameterA);
    parameterBSlider = gui->addSlider("ParameterB", 0.0, 5.0, &GUIparameterB);
    
    gui->addButton("Clear");
    gui->addButton("Click / Drag");
    gui->addButton("Brush");
    gui->addButton("Music");
    gui->addButton("Animate");
    
    gui->addButton("No Shader");
    gui->addButton("Shader1");
    gui->addButton("Shader2");
    gui->addButton("Shader3");
    gui->addButton("Shader4");
    
    gui->addButton("Triangle");
    gui->addButton("Square");
    gui->addButton("Circle");
    gui->addButton("Origin");
}

void ksShaderPalette::update(float dt)
{
    guiEvent();
    
    //updateGUIValues();
    
    //    if (doRotate)
    //    {
    //        deltaDeg = dt * 50.0;
    //    }
    
    //    if (isPlaySound)
    //    {
    //        ofSoundUpdate();
    //        float *val = ofSoundGetSpectrum(256);
    //        spectrum *= 0.97;
    //        spectrum = max(spectrum, val[8]);
    //    }
}

void ksShaderPalette::draw(int x, int y, int width, int height)
{
    ofBaseDraws *pDraw = ksResource::getResource();
    copySrcToFbo(width, height);
    
    float halfW, halfH;
    halfW = width/2.0f;
    halfH = height/2.0f;
    
    // --!实在是没有办法 一点都不清楚为什么copyToFbo()当中在向fbo上渲染baseDraws时会出现整体坐标翻转的问题
    
    //ofBackgroundGradient(ofColor(255), ofColor(128));
    //ofClear(ofColor(58, 174, 156, 20));
    //fboAlpha.draw(0, 0);
    
    for (int i = 0; i < mesh.size(); i ++)
    {
        ofxPushMSV();
        ofTranslate(halfW, halfH);
        
        ofScale(width / 10 * (1.0 + spectrum), height / 10 * (1.0 + spectrum), 1.0f);
        ofTranslate(centerPoints[i]);
        
        ofRotate(RotateDeg[i]);
        shader->begin();
        shader->setUniform1i("index", shaderIndex[i]);
        shader->setUniform1f("time", ofGetElapsedTimef());
        switch(ksResource::resourceType)
        {
            case ksResource::KS_RESOURCE_IMAGE:
                shader->setUniformTexture("tex", ((ofImage*)pDraw)->getTextureReference(), 1);
                break;
                
            case ksResource::KS_RESOURCE_CAMERA:
                shader->setUniformTexture("tex", ((ofVideoGrabber*)pDraw)->getTextureReference(), 1);
                break;
                
            case ksResource::KS_RESOURCE_VIDEO:
                shader->setUniformTexture("tex", ((ofVideoPlayer*)pDraw)->getTextureReference(), 1);
                break;
        }
        //shader->setUniformTexture("tex", fbo.getTextureReference(), 1);
        shader->setUniform1i("timeFlag", useTime);
        shader->setUniform1f("speed", speed);
        shader->setUniform1f("a", parameterA[i]);
        shader->setUniform1f("b", parameterB[i]);
        mesh[i].draw();
        shader->end();
        
        ofxPopMSV();
    }
    
    if ((!isBrush) && isDrawing)
    {
        ofxPushMSV();
        ofSetColor(ofColor::red);
        ofTranslate(halfW, halfH);
        ofScale(width / 10 * (1.0 + spectrum), height / 10 * ( 1.0 + spectrum ), 1.0f);
        
        ofNoFill();
        ofCircle(centerPoints[index], 10);
        ofCircle(tempPoint, 10);
        ofLine(centerPoints[index], tempPoint);
        cout<<"x =  "<< centerPoints[index].x <<", y = "<< centerPoints[index].y <<
        "--> x = " << tempPoint.x << ", y = " << tempPoint.y << endl;
        ofxPopMSV();
    }
    //cout<<"mesh: "<<mesh.size()<<endl;
    //cout<<"index: "<<index<<endl;
}

void ksShaderPalette::guiEvent()
{
    if(ksMessageQueue::messages.size() > 0)
    {
        for(int i=0; i<ksMessageQueue::messages.size(); i++)
        {
            // buttom
            if(!strcmp("Clear", ksMessageQueue::messages[i].c_str()))
            {
                clear();
            }
            // slider
            else if(!strcmp("Radius", ksMessageQueue::messages[i].c_str()))
            {
                GUIRadius = radiusSlider->getValue();
            }
            else if(!strcmp("RotateDeg", ksMessageQueue::messages[i].c_str()))
            {
                GUIRotateDeg = rotateDegSlider->getValue();
            }
            else if(!strcmp("SegmentNum", ksMessageQueue::messages[i].c_str()))
            {
                GUISegmentNum = segmentNumSlider->getValue();
            }
            else if(!strcmp("Speed", ksMessageQueue::messages[i].c_str()))
            {
                speed = speedSlider->getValue();
            }
            else if(!strcmp("ParameterA", ksMessageQueue::messages[i].c_str()))
            {
                GUIparameterA = parameterASlider->getValue();
            }
            else if(!strcmp("ParameterB", ksMessageQueue::messages[i].c_str()))
            {
                GUIparameterB = parameterASlider->getValue();
            }
            // button
            else if(!strcmp("Click / Drag", ksMessageQueue::messages[i].c_str()))
            {
                isClick = true;
                isBrush = !isClick;
            }
            else if(!strcmp("Brush", ksMessageQueue::messages[i].c_str()))
            {
                isBrush = true;
                isClick = !isBrush;
            }
            else if(!strcmp("Music", ksMessageQueue::messages[i].c_str()))
            {
                isPlaySound = !isPlaySound;
                if (isPlaySound)
                {
                    if (sound->getIsPlaying() && sound->getPosition()>0)
                    {
                        sound->setPaused(false);
                    }
                    else
                    {
                        sound->play();
                    }
                }
                else
                {
                    sound->setPaused(true);
                }
            }
            else if(!strcmp("Animate", ksMessageQueue::messages[i].c_str()))
            {
                useTime = !useTime;
            }
            else if(!strcmp("No Shader", ksMessageQueue::messages[i].c_str()))
            {
                GUIshaderIndex = 0;
            }
            else if(!strcmp("Shader1", ksMessageQueue::messages[i].c_str()))
            {
                GUIshaderIndex = 1;
            }
            else if(!strcmp("Shader2", ksMessageQueue::messages[i].c_str()))
            {
                GUIshaderIndex = 2;
            }
            else if(!strcmp("Shader3", ksMessageQueue::messages[i].c_str()))
            {
                GUIshaderIndex = 3;
            }
            else if(!strcmp("Shader4", ksMessageQueue::messages[i].c_str()))
            {
                GUIshaderIndex = 4;
            }
            else if(!strcmp("Triangle", ksMessageQueue::messages[i].c_str()))
            {
                GUIShapeOfMesh = 0;
            }
            else if(!strcmp("Square", ksMessageQueue::messages[i].c_str()))
            {
                GUIShapeOfMesh = 1;
            }
            else if(!strcmp("Circle", ksMessageQueue::messages[i].c_str()))
            {
                GUIShapeOfMesh = 2;
            }
            else if(!strcmp("Origin", ksMessageQueue::messages[i].c_str()))
            {
                GUIShapeOfMesh = 3;
            }
            
            if(strcmp("Clear", ksMessageQueue::messages[i].c_str()) && index > 0)
            {
                setMesh(index-1);
                initMesh(index -1);
            }
            
            //  else if (EName == "keepRotating")
            //  {
            //      ofxUILabelToggle *sd = dynamic_cast<ofxUILabelToggle*>(E.widget);
            //      doRotate = sd->getValue();
            //  }
        }
    }
}

void ksShaderPalette::mouseDragged( int x, int y, int button )
{
    if(x < 0 || y < 0 )
        return;
    
    ofPoint p(x, y);
    //    cout<<"x =  "<<x<<", y = "<<y<<endl;
    p.x = ofMap(p.x, 0, fbo.getWidth(), -5, 5);
    p.y = ofMap(p.y, 0, fbo.getHeight(), -5, 5);
    if (isBrush)
    {
        centerPoints.push_back(p);
        initSettings();
        initMesh(index);
        index ++;
    }
    else
    {
        Radius[index] = ofDist(centerPoints[index].x, centerPoints[index].y, p.x, p.y);
        //RotateDeg[index] = ofMap(y, 0, fbo.getHeight(), 0, 360);
        if (p.x - centerPoints[index].x != 0)
            RotateDeg[index] = atan((p.y - centerPoints[index].y)/(p.x - centerPoints[index].x));
        else
            RotateDeg[index] = 0;
        
        RotateDeg[index] *= 180/PI;
        initMesh(index);
        GUIRadius = Radius[index];
        GUIRotateDeg = RotateDeg[index];
        tempPoint = p;
        isDrawing = true;
    }
}

void ksShaderPalette::mousePressed( int x, int y, int button)
{
    if(x < 0 || y < 0 )
        return;
    
    ofPoint p(x, y);
    p.x = ofMap(p.x, 0, fbo.getWidth(), -5, 5);
    p.y = ofMap(p.y, 0, fbo.getHeight(), -5, 5);
    centerPoints.push_back(p);
    initSettings();
    if (isBrush)
    {
        initMesh(index);
        index ++;
    }
}

void ksShaderPalette::mouseReleased(int x, int y, int button )
{
    if(x < 0 || y < 0 )
        return;
    
    if (!isBrush)
    {
        isDrawing = false;
        index ++;
    }
}

void ksShaderPalette::initGUIValues()
{
    GUIRadius = 1.0;
    GUIRotateDeg = 0.0;
    GUISegmentNum = 8;
    GUIShapeOfMesh = 0;
    GUIshaderIndex = 0;
    GUIparameterA = 1.0;
    GUIparameterB = 1.0;
}

void ksShaderPalette::initSettings()
{
    Radius.push_back(GUIRadius);
    
    RotateDeg.push_back(GUIRotateDeg);
    
    SegmentNum.push_back(GUISegmentNum);
    
    ShapeOfMesh.push_back(GUIShapeOfMesh);
    
    shaderIndex.push_back(GUIshaderIndex);
    
    parameterA.push_back(GUIparameterA);
    
    parameterB.push_back(GUIparameterB);
    
    mesh.push_back(*new ofMesh);
    
}

void ksShaderPalette::updateGUIValues()
{
    GUIRadius = radiusSlider->getValue();
    GUIRotateDeg = rotateDegSlider->getValue();
    GUISegmentNum = segmentNumSlider->getValue();
    speed = speedSlider->getValue();
    GUIparameterA = parameterASlider->getValue();
    GUIparameterB = parameterBSlider->getValue();
}

void ksShaderPalette::setMesh(int i)
{
    Radius[i] = GUIRadius;
    
    RotateDeg[i] = GUIRotateDeg;
    
    SegmentNum[i] = GUISegmentNum;
    
    ShapeOfMesh[i] = GUIShapeOfMesh;
    
    shaderIndex[i] = GUIshaderIndex;
    
    parameterA[i] = GUIparameterA;
    
    parameterB[i] = GUIparameterB;
    
    mesh[i] = *new ofMesh;
    
}

void ksShaderPalette::initMesh(int i)
{
    switch (ShapeOfMesh[i])
    {
        case 0:
            initTriangleMesh(i);
            break;
        case 1:
            initSquareMesh(i);
            break;
        case 2:
            initCircleMesh(i);
            break;
        case 3:
            initOriginMesh(i);
            break;
    }
}

void ksShaderPalette::initTriangleMesh(int i)
{
    mesh[i].clear();
    float delta = 2 * PI /3;
    ofPoint *vert = new ofPoint(0, 0);
    ofPoint first, point1, point2;
    mesh[i].addVertex(ofPoint(0, 0));
    for (int j = 1; j <= 3; j++)
    {
        vert->x = Radius[i] * cos(j * delta - PI/2);
        vert->y = Radius[i] * sin(j * delta - PI/2);
        if (j ==1){
            point1 = first = *vert;
        }
        else
        {
            point2 = *vert;
            mesh[i].addVertex( 0.5 * (point1+point2) );
            point1 = *vert;
        }
        mesh[i].addVertex(*vert);
    }
    mesh[i].addVertex( 0.5 * (first+point2) );
    
    
    mesh[i].addTexCoord(ofVec2f(0, 0));
    mesh[i].addTexCoord(ofVec2f(0, 1));
    mesh[i].addTexCoord(ofVec2f(1, 0));
    mesh[i].addTexCoord(ofVec2f(0, 1));
    mesh[i].addTexCoord(ofVec2f(1, 0));
    mesh[i].addTexCoord(ofVec2f(0, 1));
    mesh[i].addTexCoord(ofVec2f(1, 0));
    
    addIndicesToMesh(i, 6);
}

void ksShaderPalette::initSquareMesh(int i)
{
    mesh[i].clear();
    float delta = 2 * PI / 4;
    ofPoint vert, first, point1, point2;
    mesh[i].addVertex(ofPoint(0, 0));
    for (int j = 1; j <= 4; j++)
    {
        vert.x = Radius[i] * cos(j * delta + PI/4);
        vert.y = Radius[i] * sin(j * delta + PI/4);
        if (j ==1){
            point1 = first = vert;
        }
        else
        {
            point2 = vert;
            mesh[i].addVertex( 0.5 * (point1+point2) );
            point1 = vert;
        }
        mesh[i].addVertex(vert);
    }
    mesh[i].addVertex( 0.5 * (first+point2) );
    
    mesh[i].addTexCoord(ofVec2f(0, 0));
    mesh[i].addTexCoord(ofVec2f(0, 1));
    mesh[i].addTexCoord(ofVec2f(1, 0));
    mesh[i].addTexCoord(ofVec2f(0, 1));
    mesh[i].addTexCoord(ofVec2f(1, 0));
    mesh[i].addTexCoord(ofVec2f(0, 1));
    mesh[i].addTexCoord(ofVec2f(1, 0));
    mesh[i].addTexCoord(ofVec2f(0, 1));
    mesh[i].addTexCoord(ofVec2f(1, 0));
    
    addIndicesToMesh(i, 8);
}

void ksShaderPalette::initCircleMesh(int i)
{
    mesh[i].clear();
    int resolution = 2 * SegmentNum[i];
    float delta = 2 * PI / resolution;
    ofPoint vert;
    mesh[i].addVertex(ofPoint(0, 0));
    for (int j = 0; j < resolution; j++)
    {
        vert.x = Radius[i] * cos(j * delta);
        vert.y = Radius[i] * sin(j * delta);
        mesh[i].addVertex(vert);
    }
    
    mesh[i].addTexCoord(ofVec2f(0, 0));
    for (int j = 0; j < resolution/2; j++)
    {
        mesh[i].addTexCoord(ofVec2f(1, 0));
        mesh[i].addTexCoord(ofVec2f(0, 1));
    }
    addIndicesToMesh(i, resolution);
}

void ksShaderPalette::initOriginMesh(int i)
{
    mesh[i].clear();
    mesh[i].addVertex(ofPoint(0, 0));
    mesh[i].addVertex(ofPoint(-Radius[i], -Radius[i]));
    mesh[i].addVertex(ofPoint(-Radius[i], Radius[i]));
    mesh[i].addVertex(ofPoint(Radius[i], Radius[i]));
    mesh[i].addVertex(ofPoint(Radius[i], -Radius[i]));
    
    mesh[i].addTexCoord(ofVec2f(0.5, 0.5));
    mesh[i].addTexCoord(ofVec2f(1, 0));
    mesh[i].addTexCoord(ofVec2f(1, 1));
    mesh[i].addTexCoord(ofVec2f(0, 1));
    mesh[i].addTexCoord(ofVec2f(0, 0));
    
    ofIndexType ids[12] = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1
    };
    
    mesh[i].addIndices(ids, 12);
}

void ksShaderPalette::copySrcToFbo(float w, float h)
{
    //ofBaseDraws *pDraw = ksResource::getResource();
    
    if(!fbo.isAllocated())
    {
        fbo.allocate(w,h,GL_RGBA);
        fbo.getTextureReference().setTextureWrap(GL_MIRRORED_REPEAT,GL_MIRRORED_REPEAT);
        //ofClear(ofColor(58, 174, 156, 20));
        ofBackgroundGradient(ofColor(255), ofColor(128));
        
        //        fboAlpha.allocate(w,h,GL_RGBA32F_EXT);
        //        fboAlpha.begin();
        //        ofPushStyle();
        //        ofEnableAlphaBlending();
        //        ofFill();
        //        ofSetColor(58, 174, 156, 20);
        //        ofRect(0, 0, w, h);
        //        ofPopStyle();
        //        fboAlpha.end();
    }
    
    //    fbo.begin();
    //    ofClear(255, 255, 255);
    //    pDraw->draw(0,0, fbo.getWidth(), fbo.getHeight());
    //    fbo.end();
}

void ksShaderPalette::addIndicesToMesh( int i, int triangleNum )
{
    ofIndexType *ids = new ofIndexType[3*triangleNum];
    for (int j = 0; j < triangleNum; j ++)
    {
        ids[j*3] = 0;
        ids[j*3 + 1] = j + 1;
        ids[j*3 + 2] = j + 2;
    }
    ids[3*triangleNum-1] = 1;
    
    mesh[i].addIndices(ids, 3*triangleNum);
    delete[] ids;
}

void ksShaderPalette::ofxPushMSV()
{
    ofPushMatrix();
    ofPushStyle();
    ofPushView();
}

void ksShaderPalette::ofxPopMSV()
{
    ofPopMatrix();
    ofPopStyle();
    ofPopView();
}

void ksShaderPalette::clear()
{
    centerPoints.clear();
    
    Radius.clear();
    
    RotateDeg.clear();
    
    SegmentNum.clear();
    
    ShapeOfMesh.clear();
    
    shaderIndex.clear();
    
    parameterA.clear();
    
    parameterB.clear();
    
    mesh.clear();
    
    index = 0;
}
