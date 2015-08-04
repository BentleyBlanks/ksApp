#pragma once
#ifndef OFXTEXTTHING_H
#define OFXTEXTTHING_H

#include "ofxVisibleThing.h"

class ofxTextThing:
	public ofxVisibleThing
{
public:
	struct settings
	{
		settings();
		ofXml serialize();
		bool deserialize(ofXml X);

		ofParameter<ofColor> textColor;
		ofParameter<string> text;
		ofParameter<string> fontPath;

		ofParameter<float> textSize;
	};
public:
	ofxTextThing();
	virtual ~ofxTextThing();

	ofxTextThing::settings getSettings();
	void set(ofXml X);	
	//void set(string text);
    void set(string text,string fontPath,float textSize=20.0f,ofColor textColor=ofColor::black,bool center=true);
	void set(string text,string fontPath,float textWidth,float textHeight,ofColor textColor=ofColor::black,bool center=true);
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
	bool center;
	ofxTextThing::settings Settings;
	ofTrueTypeFont textFont;
	

};


#endif