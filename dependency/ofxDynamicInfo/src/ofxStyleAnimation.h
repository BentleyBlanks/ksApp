#pragma once
#ifndef OFXSTYLEANIMATION_H
#define OFXSTYLEANIMATION_H

#include "ofMain.h"

class ofxStyleAnimation
{
public:
	ofxStyleAnimation();
	virtual ~ofxStyleAnimation();

	ofStyle updateStyle();

	virtual void update()=0;
	virtual void serialize(ofXml& X)=0;
	virtual void deserialize(ofXml& X)=0;

	virtual int getAlpha()=0;

protected:	
	ofStyle styleAnimation;
	int alpha;
};







#endif