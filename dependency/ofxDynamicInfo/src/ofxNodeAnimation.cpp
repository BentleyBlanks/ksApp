#include "ofxNodeAnimation.h"



ofxNodeAnimation::ofxNodeAnimation()
{
	this->ang = 0;
	this->sal = 1.0f;
	offSet.x = 0;
	offSet.y = 0;

	// 默认动画类型
	animationType = NODEANIMATION_ROTATE;
}
ofxNodeAnimation::~ofxNodeAnimation()
{

}

ofPoint ofxNodeAnimation::getOffset()
{
	update();
	return this->offSet;
}

float ofxNodeAnimation::getAng()
{
	return this->ang;
}

float ofxNodeAnimation::getScl()
{
	return this->sal;
}

ofxNodeAnimation::ofxNodeAnimationType ofxNodeAnimation::getType()
{
	return animationType;
}
