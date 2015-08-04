#pragma once
#ifndef OFXDIALOGBOX_H
#define OFXDIALOGBOX_H

#include "ofxVisibleThing.h"

class ofxDialogBox:
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
		ofParameter<float> ratio;
		ofParameter<float> arrowsWidth;
		ofParameter<float> arrowsHeigh;

	};
public:
	ofxDialogBox();
	virtual ~ofxDialogBox();

	ofxDialogBox::settings getSettings();
	void set(ofXml X);	
	void set(float rectWidth,
		float rectHeight,
		float ratio=0.5,
		float arrowsWidth=20.0f,
		float arrowsHeight=50.0f,
		ofColor lineColor=ofColor::black,
		ofColor bgColor=ofColor::white,
		float lineSize=1.0f);
	void changAlpha(int alpha);

	virtual void draw();
	virtual void draw(float x, float y);
	virtual void draw(float x, float y, float w, float h);
	virtual float getHeight();
	virtual float getWidth();

	virtual void update();
	virtual void resetTime();
	virtual void serialize(ofXml& X);
	virtual void deserialize(ofXml& X);


	ofxDialogBox::settings Settings;

private:

	int alphaCtrl;
};


#endif