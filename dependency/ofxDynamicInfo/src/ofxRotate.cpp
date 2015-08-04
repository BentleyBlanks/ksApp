#include "ofxRotate.h"


ofxRotate::settings::settings()
{
	ang.setName("ang");
	time.setName("time");
	repeat.setName("repeat");
	delay.setName("delay");
	bezierPoint.setName("bezierPoint");
	useBezier.setName("useBezier");

	ang = 360;
	time = 2.0f;
	repeat = true;
	delay = 0;
	bezierPoint = 0;
	useBezier = false;
}

ofXml ofxRotate::settings::serialize()
{
	ofXml X;

	ofParameterGroup G;
	G.setName("fxRotate_Settings");
	G.add(ang);
	G.add(time);
	G.add(repeat);
	G.add(delay);
	G.add(bezierPoint);
	G.add(useBezier);

	X.serialize(G);
	X.reset();
	return X;
}

bool ofxRotate::settings::deserialize( ofXml X )
{
	ofParameterGroup G;
	G.setName("ofxRotate_Settings");

	X.deserialize(G);
	bool bSuc = X.exists(G.getName());
	if(bSuc)
	{
		ang = G.getFloat("ang");
		time = G.getFloat("time");
		delay = G.getFloat("delay");
		//mode = G.getFloat("mode");
		bezierPoint = G.getFloat("bezierPoint");
		useBezier = G.getFloat("useBezier");
	}

	return bSuc;	
}

ofxRotate::ofxRotate()
{	
	n_tweener.removeAllTweens();
	ang = 0;

	animationType = NODEANIMATION_ROTATE;
}

ofxRotate::~ofxRotate()
{

}

void ofxRotate::set(ofXml X)
{
	Settings.deserialize(X);
}


void ofxRotate::set(float angle, float time){
	set(angle,time,true, &ofxTransitions::linear,0,0,false);
}

void ofxRotate::set(float angle, float time,bool repeat, float (ofxTransitions::*ease) (float,float,float,float)){
	set(angle,time,repeat,ease,0,0,false);
}

void ofxRotate::set(float angle, float time, bool repeat,float (ofxTransitions::*ease) (float,float,float,float), float delay, float bezierPoint, bool useBezier, void (*callback)(float * arg)){
	Settings.ang = angle;
	Settings.time = time;
	Settings.repeat = repeat;
	mode = ease;
	Settings.delay = delay;
	Settings.bezierPoint = bezierPoint;
	Settings.useBezier = useBezier;
	
	ang = 0;
}

void ofxRotate::update()
{	
	if (Settings.repeat)
	{
		n_tweener.update();
		if (ang==0)
		{
			n_tweener.removeTween(ang);
			n_tweener.addTween(ang,Settings.ang, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
		}
		if (ang==Settings.ang)
		{
			n_tweener.removeTween(ang);
			ang = 0;
		}

	}
	else
	{
		n_tweener.update();
		if (ang==0)
		{
			n_tweener.removeTween(ang);
			n_tweener.addTween(ang,Settings.ang, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
		}
		n_tweener.update();
	}
	
}


void ofxRotate::copy(ofPtr<ofxRotate> pRotate)
{
	this->Settings.ang = pRotate->Settings.ang;
	this->Settings.time = pRotate->Settings.time;
	this->Settings.repeat = pRotate->Settings.repeat;
	this->mode = pRotate->mode;
	this->Settings.delay = pRotate->Settings.delay;
	this->Settings.bezierPoint = pRotate->Settings.bezierPoint;
	this->Settings.useBezier = pRotate->Settings.useBezier;

	ang = 0;
}

void ofxRotate::resetTime()
{

}

void ofxRotate::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxRotate::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}