#pragma once
#ifndef OFXNODEANIMATION_H
#define OFXNODEANIMATION_H

#include "ofMain.h"
#include "ofxTweener.h"

class ofxNodeAnimation
{
public:
	enum ofxNodeAnimationType
	{
		NODEANIMATION_ROTATE = 0,
		NODEANIMATION_SCALE,
		NODEANIMATION_SHAKE
	};

	ofxNodeAnimation();
	virtual ~ofxNodeAnimation();

	float getAng();
	float getScl();
	ofPoint getOffset();
	ofxNodeAnimationType getType();

	virtual void update()=0;
	virtual void serialize(ofXml& X)=0;
	virtual void deserialize(ofXml& X)=0;

protected:		
	ofPoint offSet; 
	float ang;
	float sal;
	ofxTweener n_tweener;

	ofxNodeAnimationType animationType;
};







#endif