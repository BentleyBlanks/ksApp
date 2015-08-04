#pragma once
#ifndef OFXMOVESHAKE_H
#define OFXMOVESHAKE_H

#include "ofxNodeAnimation.h"

class ofxMoveShake:
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
	ofxMoveShake();
	virtual ~ofxMoveShake();

	ofxMoveShake::settings getSettings();
	void setSettings(ofxMoveShake::settings S);	

	virtual void update();
	virtual void resetTime();
	virtual void serialize(ofXml& X);
	virtual void deserialize(ofXml& X);

	void copy(ofPtr<ofxMoveShake> pShake);

	void set(ofXml X);

	void set(float to, float time,int count=3,bool direction=true, float (ofxTransitions::*ease) (float,float,float,float)=&ofxTransitions::easeInSine);


private:
	// configuration
	ofxMoveShake::settings Settings;
	float x1,x2,y1,y2;
	bool bShake;

	typedef float(ofxTransitions::* easeFunction)(float,float,float,float);
	easeFunction mode;
	int _count;
	//ofxTweener s_tweener;

};


#endif