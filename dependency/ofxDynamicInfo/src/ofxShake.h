#pragma once
#ifndef OFXSHAKE_H
#define OFXSHAKE_H

#include "ofxNodeAnimation.h"

class ofxShake:
	public ofxNodeAnimation
{
public:
	struct settings
	{
		typedef float(ofxTransitions::* easeFunction)(float,float,float,float);
		settings();
		ofXml serialize();
		bool deserialize(ofXml X);

		ofParameter<float> dx;
		ofParameter<float> time;
		ofParameter<float> delay;
		ofParameter<float> bezierPoint;
		ofParameter<bool> useBezier;
		ofParameter<int> num;
		ofParameter<bool> direction;
	};
public:
	ofxShake();
	virtual ~ofxShake();

	ofxShake::settings getSettings();
	void setSettings(ofxShake::settings S);	

	virtual void update();
	virtual void resetTime();
	virtual void serialize(ofXml& X);
	virtual void deserialize(ofXml& X);

	void copy(ofPtr<ofxShake> pShake);

	void set(ofXml X);

	void set(float to, float time);
	void set(float to, float time,float (ofxTransitions::*ease) (float,float,float,float),bool direction=true,int count=0);

private:
	void set(float dx, float time,float (ofxTransitions::*ease) (float,float,float,float),bool direction,int count, float delay, 
		float bezierPoint, bool useBezier,void (*callback)(float * arg)=NULL);

	
private:
	// configuration
	ofxShake::settings Settings;
	float x1,x2,y1,y2;

	typedef float(ofxTransitions::* easeFunction)(float,float,float,float);
	easeFunction mode;
	int _count;
	//ofxTweener s_tweener;

};


#endif