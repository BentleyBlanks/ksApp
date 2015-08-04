#include <scopes/ksSphere12101/ksSphere12101.h>

#include <ks/utility/ksSettings.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksSphere12101);

ksSphere12101::ksSphere12101()
{

}

ksSphere12101::~ksSphere12101()
{
    
}

void ksSphere12101::init(){
    setupMesh();
    initComponents();
    initSphere();
    
    //gui->addLabel("ksSphereLbl");
    RadiusSlider = gui->addSlider(Radius.getName(),Radius.getMin(),Radius.getMax(),Radius);
    SpeedSlider = gui->addSlider(Speed.getName(),Speed.getMin(),Speed.getMax(),Speed);
    WScaleSlider = gui->addSlider(WScale.getName(),WScale.getMin(),WScale.getMax(),WScale);
    HScaleSlider = gui->addSlider(HScale.getName(),HScale.getMin(),HScale.getMax(),HScale);
    RotateXSlider = gui->addSlider(RotateX.getName(),RotateX.getMin(),RotateX.getMax(),RotateX);
    RotateYSlider = gui->addSlider(RotateY.getName(),RotateY.getMin(),RotateY.getMax(),RotateY);
    RotateZSlider = gui->addSlider(RotateZ.getName(),RotateZ.getMin(),RotateZ.getMax(),RotateZ);
    
    //ofAddListener(gui->newGUIEvent,this,&ksSphere12101::guiEvent);
}

void ksSphere12101::draw(int x, int y, int w, int h)
{
	ofBaseDraws *pDrawSrc = ksResource::getResource();

//    ofPtr<ofBaseDraws> pDrawSrc = getSrc(0);				//获取数据源
    //ofBackgroundGradient(ofColor(255),ofColor(128));		//设置渐变背景
    
    // if(pDrawSrc.use_count()==0)
    // {
    //     return;
    // }
    
    if(!fbo.isAllocated())
        fbo.allocate(pDrawSrc->getWidth(),		//为fbo分配内存
                     pDrawSrc->getHeight(),
                     GL_RGBA);
    if(!fbo2.isAllocated())
        fbo2.allocate(w, h,GL_RGBA);			//为fbo2分配内存
    
    //fbo上绘制数据源
    fbo.begin();
    ofClear(0,0,0,0);
    pDrawSrc->draw(0,0,fbo.getWidth(),fbo.getHeight());
    fbo.end();
    
    //fbo2上绘制mesh,mesh绑定fbo的纹理
    fbo2.begin();
    ofClear(0,0,0,0);
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(w/2,h/2);
    ofScale(w/WScale, h/HScale,1.0f);
    ofTexture& T = fbo.getTextureReference();
    float R = 4*sin(PI/3);
    float Theta = PI/6;
    T.bind();
    mesh.draw();				//绘制中心六角星
    for(int i=0;i<6;i++)		//绘制中心外第一层六角星
    {
        ofPoint P(2*R*cos(Theta), 2*R*sin(Theta));
        ofTranslate(P);
        mesh.draw();
        for(int i=0;i<6;i++)	//绘制中心外第二层六角星，类似递归？
        {
            ofPoint P(2*R*cos(Theta), 2*R*sin(Theta));
            ofTranslate(P);
            mesh.draw();
            ofTranslate(-P);
            Theta += PI/3;
        }
        ofTranslate(-P);
        Theta += PI/3;
    }
    T.unbind();
    ofPopMatrix();
    ofPopStyle();
    fbo2.end();
    
    //绘制sphere，绑定fbo2的纹理
    ofPushStyle();
    ofPushMatrix();
    ofTranslate(w/2,h/2);
    float t = ofGetElapsedTimef();
    ofRotate(t*Speed*2,0,1,0);
    ofRotateX(X);
    ofRotateY(Y);
    ofRotateZ(Z);
    ofTexture& T2 = fbo2.getTextureReference();
    T2.bind();
    sphere.draw(OF_MESH_FILL);
    T2.unbind();
    ofPopMatrix();
    ofPopStyle();
}


void ksSphere12101::update( float dt )
{
    Radius = RadiusSlider->getValue();		//球的半径
    Speed = SpeedSlider->getValue();		//旋转速度
    WScale = WScaleSlider->getValue();		//mesh宽度的缩放
    HScale = HScaleSlider->getValue();		//mesh高度的缩放
    RotateX = RotateXSlider->getValue();		//绕X轴旋转角度
    RotateY = RotateYSlider->getValue();		//绕Y轴旋转角度
    RotateZ = RotateZSlider->getValue();
}

void ksSphere12101::setupMesh()
{
    ofDisableArbTex();
    
    //mesh中心点0
    mesh.addVertex(ofPoint(0,0));
    //第二层点1~6
    mesh.addVertex(ofPoint(1.0f, 2*sin(PI/3)));
    mesh.addVertex(ofPoint(2.0f, 0));
    mesh.addVertex(ofPoint(1.0f, -2*sin(PI/3)));
    mesh.addVertex(ofPoint(-1.0f, -2*sin(PI/3)));
    mesh.addVertex(ofPoint(-2.0f, 0));
    mesh.addVertex(ofPoint(-1.0f,2*sin(PI/3)));
    //第三层点7~12
    mesh.addVertex(ofPoint(0, 4*sin(PI/3)));
    mesh.addVertex(ofPoint(3.0f, 2*sin(PI/3)));
    mesh.addVertex(ofPoint(3.0f, -2*sin(PI/3)));
    mesh.addVertex(ofPoint(0, -4*sin(PI/3)));
    mesh.addVertex(ofPoint(-3.0f, -2*sin(PI/3)));
    mesh.addVertex(ofPoint(-3.0f, 2*sin(PI/3)));
    
    mesh.addTexCoord(ofVec2f(0,0));		//0
    //1~6
    mesh.addTexCoord(ofVec2f(1,0));
    mesh.addTexCoord(ofVec2f(0,1));
    mesh.addTexCoord(ofVec2f(1,0));
    mesh.addTexCoord(ofVec2f(0,1));
    mesh.addTexCoord(ofVec2f(1,0));
    mesh.addTexCoord(ofVec2f(0,1));
    //7~12
    mesh.addTexCoord(ofVec2f(1,1));
    mesh.addTexCoord(ofVec2f(1,1));
    mesh.addTexCoord(ofVec2f(1,1));
    mesh.addTexCoord(ofVec2f(1,1));
    mesh.addTexCoord(ofVec2f(1,1));
    mesh.addTexCoord(ofVec2f(1,1));
    
    
    ofIndexType ids[36] =
    {
        0,1,2,
        0,2,3,
        0,3,4,
        0,4,5,
        0,5,6,
        0,6,1,
        7,6,1,
        8,1,2,
        9,2,3,
        10,3,4,
        11,4,5,
        12,5,6
    };
    mesh.addIndices(ids,36);
}

ofParameterGroup& ksSphere12101::genParamGroup()
{
    Group.clear();
    Group.setName("ksSphereParameters");
    Group.add(Radius);
    Group.add(Speed);
    Group.add(WScale);
    Group.add(HScale);
    Group.add(RotateX);
    Group.add(RotateY);
    Group.add(RotateZ);
    
    return Group;
}

void ksSphere12101::RadiusChanged(float& radius)
{
    initSphere();
}

void ksSphere12101::SpeedChanged(float& speed)
{
    initSphere();
}

void ksSphere12101::WScaleChanged(float& wscale)
{
    initSphere();
}

void ksSphere12101::HScaleChanged(float& wscale)
{
    initSphere();
}

void ksSphere12101::RotateXchanged(float& RotateX)
{
    initSphere();
    X = RotateX;
}

void ksSphere12101::RotateYchanged(float& RotateY)
{
    initSphere();
    Y = RotateY;
}

void ksSphere12101::RotateZchanged(float& RotateZ)
{
    initSphere();
    Z = RotateZ;
}

//void ksSphere12101::guiEvent( ofxUIEventArgs& E )
//{
//    string EName = E.widget->getName();
//    
//    cout << "EName is changed!" << endl;
//    
//    E.widget->stateChange();
//    if(EName==Radius.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        Radius = sd->getValue();
//    }
//    else if(EName == Speed.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        Speed = sd->getValue();
//    }
//    else if(EName == WScale.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        WScale = sd->getValue();
//    }
//    else if(EName == HScale.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        HScale = sd->getValue();
//    }
//    else if(EName == RotateX.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        RotateX = sd->getValue();
//    }
//    else if(EName == RotateY.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        RotateY = sd->getValue();
//    }
//    else if(EName == RotateZ.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        RotateZ = sd->getValue();
//    }
//}

void ksSphere12101::initSphere()
{
    sphere.setRadius(Radius);
}

void ksSphere12101::initComponents()
{
    Radius = 150.0f;
    Radius.setName("Radius");
    Radius.setMin(50.0f);
    Radius.setMax(250.0f);
    Radius.addListener(this,&ksSphere12101::RadiusChanged);
    
    Speed = 10.0f;
    Speed.setName("Speed");
    Speed.setMin(0.0f);
    Speed.setMax(100.0f);
    Speed.addListener(this,&ksSphere12101::SpeedChanged);
    
    WScale = 20.0f;
    WScale.setName("WidthScale");
    WScale.setMin(10.0f);
    WScale.setMax(30.0f);
    WScale.addListener(this,&ksSphere12101::WScaleChanged);
    
    HScale = 20.0f;
    HScale.setName("HeightScale");
    HScale.setMin(10.0f);
    HScale.setMax(30.0f);
    HScale.addListener(this,&ksSphere12101::HScaleChanged);
    
    RotateX = 0.0f;
    RotateX.setName("RotateX");
    RotateX.setMin(0.0f);
    RotateX.setMax(360.0f);
    RotateX.addListener(this,&ksSphere12101::RotateXchanged);
    
    RotateY = 0.0f;
    RotateY.setName("RotateY");
    RotateY.setMin(0.0f);
    RotateY.setMax(360.0f);
    RotateY.addListener(this,&ksSphere12101::RotateYchanged);
    
    RotateZ = 0.0f;
    RotateZ.setName("RotateZ");
    RotateZ.setMin(0.0f);
    RotateZ.setMax(360.0f);
    RotateZ.addListener(this,&ksSphere12101::RotateZchanged);
}
