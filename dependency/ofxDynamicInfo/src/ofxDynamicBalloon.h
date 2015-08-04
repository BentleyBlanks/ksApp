#pragma once
#ifndef OFXDYNAMICBALLOON_H
#define OFXDYNAMICBALLOON_H

#include "ofxVisibleThing.h"

class ofxDynamicBalloon:
	public ofxVisibleThing
{
public:
	//±ﬂøÚ Ù–‘
	struct settings
	{
		settings();
		ofXml serialize();
		bool deserialize(ofXml X);
		
		ofParameter<ofColor> lineColor;
		ofParameter<ofColor> bgColor;
		
		ofParameter<float> lineSize;
		ofParameter<float> rectWidth;
		ofParameter<float> rectHeight;
		ofParameter<float> rectRound;

	};
public:
	ofxDynamicBalloon();
	virtual ~ofxDynamicBalloon();
	
	ofxDynamicBalloon::settings getSettings();
	void set(ofXml X);	
    void set(float rectWidth,float rectHeight,float rectRound=3.0f,ofColor lineColor=ofColor::black,ofColor bgColor=ofColor::white,float lineSize=1.0f);
    void changAlpha(int alpha);

	virtual void draw(float x, float y);
	virtual void draw(float x, float y, float w, float h);
	virtual float getHeight();
	virtual float getWidth();

	virtual void draw();
	virtual void update();
	virtual void resetTime();
	virtual void serialize(ofXml& X);
	virtual void deserialize(ofXml& X);


	ofxDynamicBalloon::settings Settings;

private:
	
    int alphaCtrl;
};


#endif