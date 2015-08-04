#include <scopes/ksRflower/ksRflower.h>

#include <ks/utility/ksSettings.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksRflower);

ksRflower::ksRflower()
{
	
	ScaleX = 1.0f;
	ScaleY = 1.0f;
	Rotation = 0.0f;
	Speed = 10.0f;
	number=6;
	time=0;

}

ksRflower::~ksRflower()
{

}

void ksRflower::init()
{

}

void ksRflower::draw(int x, int y, int width, int height)
{
	ofBaseDraws *pDraw = ksResource::getResource();

	ofPushMatrix();

	ofTranslate(width/2,height/2);
	ofScale(1.5f,-1.5f,1.0f);
	float scaleX,scaleY,scaleZ;
	scaleX = width/3;
	scaleY = height/3;
	scaleZ = 1.0f;
	ofScale(scaleX,scaleY,scaleZ);
	ofRotate(Rotation);

	for(int i=0;i<10;i++)
	{		
		ofScale(0.5f,0.5f,1.0f);
		draw4Leaves(pDraw);		
	}	

	ofDrawAxis(5);
	ofPopMatrix();
}

void ksRflower::draw4Leaves(ofBaseDraws *pDraws ) 
{
	for(int i=0;i<number;i++)
	{
		draw1Leaf(pDraws);
		
	}		
}


void ksRflower::draw1Leaf(ofBaseDraws *pDraws ) 
{
	ofRotate(360/number);
	pDraws->draw(-2,2,3,-1);
}




void ksRflower::update(float dt) 
{
	float dts = ofGetElapsedTimef() - time;
	time = ofGetElapsedTimef(); 
	dts *= Speed;

	Rotation += dts;

	ScaleX = 1.0f + 0.5f*sin(1.2343f*Rotation);
	ScaleY = 1.0f + 0.5f*cos(0.9912f*Rotation);
}

void ksRflower::mousePressed(int x, int y, int button )
{
	if(x<(y/2))
	{
		number--;
    }
	else
    {
		number++;
	}
	if(number>20)
	{
		number=20;
	}
	if(number<3)
	{
		number=3;
	}
}
