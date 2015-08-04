#pragma once
#ifndef OFXFADEEFFECT_H
#define OFXFADEEFFECT_H

#include "ofxStyleAnimation.h"

class ofxFadeEffect:
	public ofxStyleAnimation
{
public:
	struct settings
	{
		settings();
		ofXml serialize();
		bool deserialize(ofXml X);

		ofParameter<int> alphaFrom;
		ofParameter<int> alphaTo;
		ofParameter<float> time;
		ofParameter<float> delay;
	};
public:
	ofxFadeEffect();
	virtual ~ofxFadeEffect();

	ofxFadeEffect::settings getSettings();
	void setSettings(ofxFadeEffect::settings S);	

	void set(ofXml X);
	void set(float time,int alphaFrom=255,int alphaTo=0,float delay = 0);
	int getAlpha();

	virtual void update();
	virtual void serialize(ofXml& X);
	virtual void deserialize(ofXml& X);

	void copy(ofPtr<ofxFadeEffect> pFade); 

private:
	
	ofxFadeEffect::settings Settings;
	float creatTime;

};


#endif