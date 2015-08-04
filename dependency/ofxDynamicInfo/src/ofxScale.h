#pragma once
#ifndef OFXSCALE_H
#define OFXSCALE_H

#include "ofxNodeAnimation.h"

class ofxScale:
	public ofxNodeAnimation
{
public:

	struct settings
	{
		typedef float(ofxTransitions::* easeFunction)(float,float,float,float);
		settings();
		ofXml serialize();
		bool deserialize(ofXml X);

		ofParameter<float> scaFrom;
		ofParameter<float> scaTo;
		ofParameter<float> time;
		ofParameter<bool> repeat;
		ofParameter<float> delay;
		ofParameter<float> bezierPoint;
		ofParameter<bool> useBezier;
	};
public:
	ofxScale();
	virtual ~ofxScale();

	ofxScale::settings getSettings();
	void setSettings(ofxScale::settings S);	

	virtual void update();
	virtual void resetTime();
	virtual void serialize(ofXml& X);
	virtual void deserialize(ofXml& X);

	void copy(ofPtr<ofxScale> pScale);

	void set(ofXml X);
	void set(float scaFrom,float scaTo, float time);
	void set(float scaFrom,float scaTo, float time,bool repeat,float (ofxTransitions::*ease) (float,float,float,float)=&ofxTransitions::linear);

private:
	void set(float scaFrom,float scaTo, float time,bool repeat,float (ofxTransitions::*ease) (float,float,float,float), float delay, float bezierPoint, bool useBezier);

private:
	ofxScale::settings Settings;

	typedef float(ofxTransitions::* easeFunction)(float,float,float,float);
	easeFunction mode;   

};


#endif