#pragma once
#ifndef OFXROTATE_H
#define OFXROTATE_H

#include "ofxNodeAnimation.h"

class ofxRotate:
	public ofxNodeAnimation
{
public:
	struct settings
	{
		typedef float(ofxTransitions::* easeFunction)(float,float,float,float);
		settings();
		ofXml serialize();
		bool deserialize(ofXml X);

		ofParameter<float> ang;
		ofParameter<float> time;
		ofParameter<bool> repeat;
		ofParameter<float> delay;
		ofParameter<float> bezierPoint;
		ofParameter<bool> useBezier;
	};
public:
	ofxRotate();
	virtual ~ofxRotate();

	ofxRotate::settings getSettings();
	void setSettings(ofxRotate::settings S);	

	virtual void update();
	virtual void resetTime();
	virtual void serialize(ofXml& X);
	virtual void deserialize(ofXml& X);

	void copy(ofPtr<ofxRotate> pRotate);

	void set(ofXml X);
	void set(float angle, float time);
	void set(float angle, float time,bool repeat, float(ofxTransitions::*ease)(float,float,float,float)=&ofxTransitions::linear);
private:
	void set(float angle, float time,bool repeat, float (ofxTransitions::*ease) (float,float,float,float), float delay, float bezierPoint, bool useBezier, void (*callback)(float * arg)=NULL);

private:
	ofxRotate::settings Settings;

	typedef float(ofxTransitions::* easeFunction)(float,float,float,float);
	easeFunction mode;  

};


#endif