#include <scopes/kstzhroll/kstzhroll.h>

#include <ks/utility/ksSettings.h>
#include <ks/base/ksResource.h>

ksRegisterClass(kstzhroll);

kstzhroll::kstzhroll()
{
    
}



kstzhroll::~kstzhroll()
{

}


void kstzhroll::init()
{
    
    // to use uniform texture coordinates
    ofDisableArbTex();
    Roloate=0;
    Hexagon.addVertex(
                      ofPoint(-1.0f,2.0f*sin(PI/3.0f)));
    Hexagon.addVertex(
                      ofPoint(1.0f,2.0f*sin(PI/3.0f)));
    Hexagon.addVertex(
                      ofPoint(2.0f,0));
    Hexagon.addVertex(
                      ofPoint(1.0f,-2.0f*sin(PI/3.0f)));
    Hexagon.addVertex(
                      ofPoint(-1.0f,-2.0f*sin(PI/3.0f)));
    Hexagon.addVertex(
                      ofPoint(-2.0f,0));
    Hexagon.addVertex(
                      ofPoint(0.0f,0));
    
    
    Hexagon.addTexCoord(ofVec2f(1,1));
    Hexagon.addTexCoord(ofVec2f(1,1));
    Hexagon.addTexCoord(ofVec2f(1,1));
    Hexagon.addTexCoord(ofVec2f(1,1));
    Hexagon.addTexCoord(ofVec2f(1,1));
    Hexagon.addTexCoord(ofVec2f(1,1));
    Hexagon.addTexCoord(ofVec2f(0,0));
    
    
    ofIndexType ids[18] =
    {
        6,0,1,
        6,1,2,
        6,2,3,
        6,3,4,
        6,4,5,
        6,5,0
    };
    Hexagon.addIndices(ids,18);//画六边形
}

void kstzhroll::draw(int x, int y, int width, int height)
{
	if(!F.isAllocated())
	{
		F.allocate(width,height,GL_RGBA);
	}
	//ofTexture& T = F.getTextureReference();
	ofBaseDraws *pDraw = ksResource::getResource();

	F.begin();
	ofClear(0,0,0,0);
	pDraw->draw(0,0,
		F.getWidth(),F.getHeight());
	F.end();


	ofPushMatrix();
	ofPushStyle();
	ofTranslate(width/2,height/2);
	ofScale(width/4,height/4,1.0f);

	ofTexture T = F.getTextureReference();
	
	T.bind();//去掉后背景变白
	ofRotate(Roloate);
	Hexagon.draw();//去掉后自动填充背景
	

	T.unbind();    //去掉没啥影响

	ofSetColor(ofColor::black);
	Hexagon.drawWireframe();

	ofPopMatrix();
	ofPopStyle();
}

void kstzhroll::update(float dt)
{
Roloate+=1;
}



void kstzhroll::pushMSV()
{
	ofPushMatrix();
	ofPushView();
	ofPushStyle();
}

void kstzhroll::popMSV()
{
	ofPopStyle();
	ofPopView();
	ofPopMatrix();
}

