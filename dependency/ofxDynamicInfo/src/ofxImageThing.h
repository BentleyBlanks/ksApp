#pragma once
#ifndef OFXIMAGETHING_H
#define OFXIMAGETHING_H

#include "ofxVisibleThing.h"

class ofxImageThing:
	public ofxVisibleThing
{
public:
	struct settings
	{
		settings();
		ofXml serialize();
		bool deserialize(ofXml X);

		ofParameter<string> imgPath;
        ofParameter<ofColor> imgColor;
		ofParameter<float> imgAlpha;
		ofParameter<float> width;
		ofParameter<float> height;
	};
public:
	ofxImageThing();
	virtual ~ofxImageThing();

	ofxImageThing::settings getSettings();
	void set(ofXml X);		
	void set(string imgPath,int imgAlpha=255);
	void set(string imgPath,float width,float height,int imgAlpha=255,ofColor imgColor=ofColor::white);
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

private:
	void setSettings();

private:
	ofxImageThing::settings Settings;
    ofImage img;

};


#endif