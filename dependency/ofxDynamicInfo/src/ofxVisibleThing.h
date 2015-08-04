#pragma once
#ifndef OFXVISIBLETHING_H
#define OFXVISIBLETHING_H

#include "ofMain.h"

class ofxVisibleThing:
	public ofBaseDraws, ofBaseUpdates 
{
public:
	ofxVisibleThing();
	virtual ~ofxVisibleThing();

	virtual void draw()=0;
	virtual void draw(float x, float y)=0;
	virtual void draw(float x, float y, float w, float h)=0;
	virtual void draw(const ofPoint & point) {
		draw(point.x, point.y);
	}
	virtual void draw(const ofRectangle & rect) {
		draw(rect.x, rect.y, rect.width, rect.height);
	}
	virtual void draw(const ofPoint & point, float w, float h) {
		draw(point.x, point.y, w, h);
	}

	virtual float getHeight()=0;
	virtual float getWidth()=0;

	virtual void update()=0; 
	virtual void resetTime()=0;
	virtual void serialize(ofXml& X)=0;
	virtual void deserialize(ofXml& X)=0;

	virtual void changAlpha(int alpha)=0;

protected:	

};







#endif