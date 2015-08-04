#include <scopes/kswht12102/kswht12102.h>

#include <ks/utility/ksSettings.h>
#include <ks/base/ksResource.h>

ksRegisterClass(kswht12102);


kswht12102::kswht12102()
{
}



kswht12102::~kswht12102()
{
    
}


void kswht12102::init(){
    // to use uniform texture coordinates
    
    ofDisableArbTex();
    
    HexagonMesh.addVertex(
                          ofPoint(-1.0f,2.0f*sin(PI/3.0f)));//A
    HexagonMesh.addVertex(
                          ofPoint(0,2.0f*sin(PI/3.0f)));//B
    HexagonMesh.addVertex(
                          ofPoint(0.5f,1.0f*sin(PI/3.0f)));//C
    HexagonMesh.addVertex(
                          ofPoint(1.5f,1.0f*sin(PI/3.0f)));//D
    HexagonMesh.addVertex(
                          ofPoint(2.0f,0));//E
    HexagonMesh.addVertex(
                          ofPoint(1.5f,-1.0f*sin(PI/3.0f)));//F
    HexagonMesh.addVertex(
                          ofPoint(0.5f,-1.0f*sin(PI/3.0f)));//G
    HexagonMesh.addVertex(
                          ofPoint(0,-2.0f*sin(PI/3.0f)));//H
    HexagonMesh.addVertex(
                          ofPoint(-1.0f,-2.0f*sin(PI/3.0f)));//I
    HexagonMesh.addVertex(
                          ofPoint(-1.5f,-1.0f*sin(PI/3.0f)));//J
    HexagonMesh.addVertex(
                          ofPoint(-1.0f,0));//K
    HexagonMesh.addVertex(
                          ofPoint(-1.5f,1.0f*sin(PI/3.0f)));//L
    HexagonMesh.addVertex(
                          ofPoint(0,0));//M
    
    
    HexagonMesh.addTexCoord(ofVec2f(0,1));
    HexagonMesh.addTexCoord(ofVec2f(1,1));
    HexagonMesh.addTexCoord(ofVec2f(1,0));
    HexagonMesh.addTexCoord(ofVec2f(1,1));
    HexagonMesh.addTexCoord(ofVec2f(0,1));
    HexagonMesh.addTexCoord(ofVec2f(1,1));
    HexagonMesh.addTexCoord(ofVec2f(1,0));
    HexagonMesh.addTexCoord(ofVec2f(1,1));
    HexagonMesh.addTexCoord(ofVec2f(0,1));
    HexagonMesh.addTexCoord(ofVec2f(1,1));
    HexagonMesh.addTexCoord(ofVec2f(1,0));
    HexagonMesh.addTexCoord(ofVec2f(1,1));
    HexagonMesh.addTexCoord(ofVec2f(0,0));
    
    
    
    ofIndexType ids[36] =
    {
        12,0,1,
        12,1,2,
        12,2,3,
        12,3,4,
        12,4,5,
        12,5,6,
        12,6,7,
        12,7,8,
        12,8,9,
        12,9,10,
        12,10,11,
        12,11,0,
        
        
    };
    HexagonMesh.addIndices(ids,36);
    
    
    T =0;
}



void kswht12102::draw( int x, int y, int w, int h )
{
    ofBaseDraws *pDrawSrc = ksResource::getResource(); 
    
    if(!F.isAllocated())
    {
        F.allocate(pDrawSrc->getWidth(),
                   pDrawSrc->getHeight(),
                   GL_RGBA);
    }
    //ofTexture& T = F.getTextureReference();
    
    F.begin();
    ofClear(0,0,0,0);
    pDrawSrc->draw(0,0,
                   F.getWidth(),F.getHeight());
    F.end();
    
    
    ofPushMatrix();
    ofPushStyle();
    ofTranslate(w/2,h/2);
    ofScale(w/10,h/10,1.0f);
    
    ofTexture T = F.getTextureReference();
    
    T.bind();
    HexagonMesh.draw();
    
    float R = 3.0f;
    float Theta = PI/3;	
    for(int i=0;i<6;i++)
    {
        ofPoint P(R*cos(Theta), R*sin(Theta));
        ofTranslate(P);
        HexagonMesh.draw();
        ofTranslate(-P);
        
        Theta += PI/3;
    }
    T.unbind();
    
    ofSetColor(ofColor::black);
    //HexagonMesh.drawWireframe();
    
    ofPopMatrix();
    ofPopStyle();
    
    
}


void kswht12102::update( float dt )
{
    T += dt;
    
    
    vector<ofVec2f> TC = HexagonMesh.getTexCoords();
    
    int NumTC = TC.size();
    
}