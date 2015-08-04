#include "ksHexagonRoll.h"
#include <ks/base/ksResource.h>

ksRegisterClass(ksHexagonRoll);

ksHexagonRoll::ksHexagonRoll()
{

}

ksHexagonRoll::~ksHexagonRoll()
{

}

void ksHexagonRoll::pushMSV()
{
	ofPushMatrix();
	ofPushView();
	ofPushStyle();
}

void ksHexagonRoll::popMSV()
{
	ofPopStyle();
	ofPopView();
	ofPopMatrix();
}
void ksHexagonRoll::updateIrolat()
{
	Roloat+=1;
}
void ksHexagonRoll::setupIrolat()
{
	//Frolat.allocate(500,500,GL_RGBA);
	Roloat=0;
	//ofImage ITemps;
	
	/*Frolat.begin();
	ofPushMatrix();
	ofPushStyle();*/

	/*getSrc(0)->draw(0,0,
		Frolat.getWidth(),Frolat.getHeight());*/
	/*ofPopMatrix();
	ofPopStyle();
	Frolat.end();*/
	
}

void ksHexagonRoll::update( float dt )
{

	updateIrolat();
}

void ksHexagonRoll::draw( int x, int y, int width, int height )
{
	c01.rotate(Rotation,certain);
	c11.rotate(Rotation,certain);
	c10.rotate(Rotation,certain);
	c050.rotate(Rotation,certain);

    static bool bFirst = true;
    
    if(!bFirst)
    {
        Hexagon.setTexCoord(0, c01);
        Hexagon.setTexCoord(1, c11);
        Hexagon.setTexCoord(2, c01);
        Hexagon.setTexCoord(3, c11);
        Hexagon.setTexCoord(4, c01);
        Hexagon.setTexCoord(5, c11);
        Hexagon.setTexCoord(6, c050);
    }
    else
    {
        Hexagon.addTexCoord(c01);
        Hexagon.addTexCoord(c11);
        Hexagon.addTexCoord(c01);
        Hexagon.addTexCoord(c11);
        Hexagon.addTexCoord(c01);
        Hexagon.addTexCoord(c11);
        Hexagon.addTexCoord(c050);
        bFirst = false;
    }

	if(!F.isAllocated())
	{
		F.allocate(width,height,GL_RGBA);
	}
	//ofTexture& T = F.getTextureReference();


	pushMSV();
	F.begin();


	ofClear(0,0,0,0);
	ofTranslate(width/2,height/2);
	ofRotate(Roloat);
	ofScale(2,2);
	ofTranslate(-width/2,-height/2);
	ksResource::getResource()->draw(0,0,F.getWidth(),F.getHeight());


	F.end();
	popMSV();


	ofPushMatrix();
	ofPushStyle();
	ofTranslate(0,0);

	ofScale(width/10,height/10,1.0f);
	//ofScale(ScaleX,ScaleY,1.0f);
	//ofRotate(Rotation);

	ofTexture T = F.getTextureReference();

	T.bind();
	ofTranslate(0,-4*sin(PI/3));
	Hexagon.draw();
	for(int i=1;i<5;i++)
	{		
		ofTranslate(0,4*sin(PI/3));
		Hexagon.draw();
		ofPushMatrix();
		for(int j=2;j<5;j++)
		{

			if(j%2==0){
				ofTranslate(3,-2*sin(PI/3));
				Hexagon.draw();}
			else{
				ofTranslate(3,2*sin(PI/3));
				Hexagon.draw();}

		}
		ofPopMatrix();

	}	


	T.unbind();



	ofPopMatrix();
	ofPopStyle();

}

void ksHexagonRoll::init()
{

	setupIrolat();

	ScaleX = 1.0f;
	ScaleY = 1.0f;
	Rotation = 0.0f;
	certain.x=0.5;
	certain.y=0.5;
	certain.z=0;
	c01.x=0;
	c01.y=1;
	c10.x=1;
	c10.y=0;
	c11.x=1;
	c11.y=1;
	c050.x=0.5;
	c050.y=0;
	Speed = 5.0f;	
	// to use uniform texture coordinates
	ofDisableArbTex(); 
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



	ofIndexType ids[18] =
	{
		6,0,1,
		6,1,2,
		6,2,3,
		6,3,4,
		6,4,5,
		6,5,0
	};
	Hexagon.addIndices(ids,18);
}
