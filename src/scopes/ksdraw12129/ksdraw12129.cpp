#include <scopes/ksdraw12129/ksdraw12129.h>

#include <ks/utility/ksSettings.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksdraw12129);


//
ksdraw12129::ksdraw12129()
{
    
}



//--------------------------------------------------------------
void ksdraw12129::init(){
    
    ofDisableArbTex();
    initSetting();
    
    //绘制一个基本图形
    mesh.addVertex(
                   ofPoint(0.0f,-141.0f));
    mesh.addVertex(
                   ofPoint(141.0f,0.0f));
    mesh.addVertex(
                   ofPoint(0.0f,141.0f));
    mesh.addVertex(
                   ofPoint(-141.0f,0.0f));
    mesh.addVertex(
                   ofPoint(0.0f,0));
    
    
    mesh.addTexCoord(ofVec2f(0,1));
    mesh.addTexCoord(ofVec2f(1,1));
    mesh.addTexCoord(ofVec2f(0,1));
    mesh.addTexCoord(ofVec2f(1,1));
    mesh.addTexCoord(ofVec2f(0.5,0.5));
    
    ofIndexType ids[12] =
    {
        4,0,1,
        4,1,2,
        4,2,3,
        4,3,0,
        
    };
    mesh.addIndices(ids,12);
    
    //gui->addLabel("ksDraw");
    speed1Slider = gui->addSlider(Speed1.getName(),Speed1.getMin(),Speed1.getMax(),Speed1);
    speed2Slider = gui->addSlider(Speed2.getName(),Speed2.getMin(),Speed2.getMax(),Speed2);
    
    //ofAddListener(gui->newGUIEvent, this, &ksdraw12129::guiEvent);
    ofBaseDraws *pDrawSrc = ksResource::getResource();
    
    if(!F.isAllocated())
        F.allocate(pDrawSrc->getWidth(), pDrawSrc->getHeight(), GL_RGBA);
}


//--------------------------------------------------------------
void ksdraw12129::update(float dt){
    Speed1 = speed1Slider->getValue();
    Speed2 = speed2Slider->getValue();
}


//--------------------------------------------------------------
void ksdraw12129::draw (int x, int y, int w, int h )
{
    ofBaseDraws *pDrawSrc = ksResource::getResource();
    
    F.begin();
    ofClear(0,0,0,0);
    pDrawSrc->draw(0,0,F.getWidth(),F.getHeight());
    F.end();
    
    ofPushStyle();
    ofPushMatrix();
    
    ofTranslate(w/2,h/2);
    draw5cross();
    
    ofPopMatrix();
    ofPopStyle();
}

void ksdraw12129::drawcross()
{
    float w=ofGetWidth();
    float h=ofGetHeight();
    
    ofPushStyle();
    ofPushMatrix();
    //ofTranslate(w/2,h/2);
    //ofScale(w/20,h/20,1.0f);
    
    ofTexture T = F.getTextureReference();
    
    T.bind();
    mesh.draw();
    //围绕中心图形画的四个正方形
    float R =282*sin(PI/4);
    float Theta = PI/4;
    for(int i=0;i<4;i++)
    {
        ofPoint P(R*cos(Theta), R*sin(Theta));
        ofTranslate(P);
        mesh.draw();
        ofTranslate(-P);
        
        Theta += PI/2;
    }
    T.unbind();
    
    ofPopMatrix();
    ofPopStyle();
}

//实现图形的旋转和速度的控制
void ksdraw12129::draw5cross()
{
    drawcross();
    ofRotate(45);
    drawcross();
    ofRotate(-45);
    
    ofScale(0.85f,0.85f,0);
    float a2 = ofGetElapsedTimef()*(-Speed2);
    ofRotate(a2);
    drawcross();
    
    ofRotate(22.5f);
    
    drawcross();
    ofRotate(-a2);
    
    ofScale(0.6f,0.6f,0);
    float a1 = ofGetElapsedTimef()*Speed1;
    ofRotate(a1);
    drawcross();
    
}

void ksdraw12129::initSetting()
{
    Speed1.setName("Speed1");
    Speed1.setMax(200);
    Speed1.setMin(0);
    Speed1=10;
    Speed1.addListener(this,&ksdraw12129::Speed1Changed);
    
    Speed2.setName("Speed2");
    Speed2.setMax(200);
    Speed2.setMin(0);
    Speed2=40;
    Speed2.addListener(this,&ksdraw12129::Speed2Changed);
    
    genParamGroup();
}
void ksdraw12129::Speed1Changed(float& Speed1)
{
    draw5cross();
}
void ksdraw12129::Speed2Changed(float& Speed2)
{
    draw5cross();
}
//void ksdraw12129::guiEvent( ofxUIEventArgs& E )
//{
//    string EName = E.widget->getName();
//    
//    //cout << "EName is changed!" << endl;
//    
//    E.widget->stateChange();
//    
//    if(EName==Speed1.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        Speed1 = sd->getValue();
//    }
//    
//    if(EName==Speed2.getName())
//    {
//        ofxUISlider* sd = dynamic_cast<ofxUISlider*>(E.widget);
//        Speed2= sd->getValue();
//    }
//}

ofParameterGroup& ksdraw12129::genParamGroup()
{
    Group.clear();
    Group.setName("ksdraw12129");
    Group.add(Speed1);
    Group.add(Speed2);
    return Group;
}