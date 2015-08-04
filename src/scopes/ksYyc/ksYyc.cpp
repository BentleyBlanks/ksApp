#include "ksYyc.h"
#include <ks/base/ksResource.h>

ksRegisterClass(ksYyc);

ksYyc::ksYyc()
{

}

ksYyc::~ksYyc()
{

}

void ksYyc::init()
{
	/////////////////////////////////////////////////////
	Mode = 1;
	ScaleX = 1.0f;
	ScaleY = 1.0f;
	Rotation = 0.0f;

	Speed = 5.0f;
	////////////////////////////////////////////////////
	// to use uniform texture coordinates
	ofDisableArbTex(); 


	Mesh.addColor(ofColor (255,0,0));
	Mesh.addVertex(
		ofPoint(-1.5*sin(PI/6),1.5*cos(PI/6)));//1

	Mesh.addColor(ofColor (255,255,0));
	Mesh.addVertex(
		ofPoint(0,2/(cos(PI/6))));//2

	Mesh.addColor(ofColor (255,0,255));
	Mesh.addVertex(
		ofPoint(1.5*sin(PI/6),1.5*sin(PI/3.0)));//3

	Mesh.addColor(ofColor (0,255,0));
	Mesh.addVertex(
		ofPoint(2,2*tan(PI/6)));//4

	Mesh.addColor(ofColor (255,255,0));
	Mesh.addVertex(
		ofPoint(1.5,0));//5

	Mesh.addColor(ofColor (0,255,255));
	Mesh.addVertex(
		ofPoint(2,-2*tan(PI/6)));//6

	Mesh.addColor(ofColor (0,0,255,222));
	Mesh.addVertex(
		ofPoint(1.5*sin(PI/6),-1.5*sin(PI/3)));//7

	Mesh.addColor(ofColor (0,0,0));
	Mesh.addVertex(
		ofPoint(0,-2/cos(PI/6)));//8

	Mesh.addColor(ofColor (255,0,255,222));
	Mesh.addVertex(
		ofPoint(-1.5*sin(PI/6),-1.5*sin(PI/3)));//9

	Mesh.addColor(ofColor (0,0,0));
	Mesh.addVertex(
		ofPoint(-2,-2*tan(PI/6)));//10

	Mesh.addColor(ofColor (0,0,255,222));
	Mesh.addVertex(
		ofPoint(-1.5,0));//11

	Mesh.addColor(ofColor (0,0,0));
	Mesh.addVertex(
		ofPoint(-2,2*tan(PI/6)));//12

	Mesh.addColor(ofColor (0,255,255,222));
	Mesh.addVertex(
		ofPoint(0,0));


	//	Mesh.addColor(ofColor (255,0,0));
	////////////////////////////////////////////////////


	Mesh.addTexCoord(ofVec2f(0,1));//1
	Mesh.addTexCoord(ofVec2f(1,1));//2
	Mesh.addTexCoord(ofVec2f(1,0));//3
	Mesh.addTexCoord(ofVec2f(1,1));//2
	Mesh.addTexCoord(ofVec2f(0,1));//3
	Mesh.addTexCoord(ofVec2f(1,1));//2
	Mesh.addTexCoord(ofVec2f(1,0));//3
	Mesh.addTexCoord(ofVec2f(1,1));//2
	Mesh.addTexCoord(ofVec2f(0,1));//3
	Mesh.addTexCoord(ofVec2f(1,1));//2
	Mesh.addTexCoord(ofVec2f(1,0));//3
	Mesh.addTexCoord(ofVec2f(1,1));//2
	Mesh.addTexCoord(ofVec2f(0,0));

	ofIndexType ids[36] =
	{
		12,0,2,
		12,2,4,
		12,4,6,
		12,6,8,
		12,8,10,
		12,10,0,
		0,1,2,
		2,3,4,
		4,5,6,
		6,7,8,
		8,9,10,
		10,11,0,
	};
	Mesh.addIndices(ids,36);


	T =0;

}

void ksYyc::update( float dt )
{
	T += dt;

	vector<ofVec2f> TC = 
		Mesh.getTexCoords();

	//////////////////////////////////////////////////////////////

	dt *= Speed;

	Rotation += dt;

	ScaleX = 1.0f + 0.5f*sin(0.2*Rotation);
	ScaleY = 1.0f + 0.5f*cos(0.1*Rotation);
}

void ksYyc::draw( int x, int y, int width, int height )
{
    ofPushMatrix();
	////////////////////////////////////////////////////////
	ofScale(ScaleX,ScaleY,0.5f);

	//    ofRotate( 1 * 25+ofGetFrameNum());


	//////////////////////////////////////////////////////////
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
	ofTranslate(width/2,height/2);
	ofScale(width/10,height/10,1.0f);

	ofTexture T = F.getTextureReference();

	T.bind();
	Mesh.draw();

	float R = 4*sin(PI/3);
	float Theta= PI/6;

	for(int i=0;i<6;i++)
	{
		ofPoint P(R*cos(Theta), R*sin(Theta));
		ofTranslate(P);
		Mesh.draw();
		ofTranslate(-P);

		Theta += PI/3;

		//      Theta = PI/a;	
		//		Mesh.draw();
	}

	T.unbind();

	ofSetColor(ofColor::black);
	//Mesh.drawWireframe();

	ofPopMatrix();
	ofPopStyle();
    
    ofPopMatrix();
}
