#pragma once
#ifndef OFXSHAKE_H
#define OFXSHAKE_H
#include "ofMain.h"
#include "ofxTweener.h"

class ksShake
{
public:
	ksShake();
	virtual ~ksShake();

	virtual void update();
	virtual void resetTime();

	float getOffset();

	void set(float to, float time,int count=2, float (ofxTransitions::*ease) (float,float,float,float)=&ofxTransitions::easeInSine);

	void enable();
	void disable();

private:
	float dy,time,num,creatTime;
	float x1,x2,y1,y2;

	bool able,bShake;

	typedef float(ofxTransitions::* easeFunction)(float,float,float,float);
	easeFunction mode;
	int _count;

	float offSet_y; 
	ofxTweener n_tweener;

};


#endif