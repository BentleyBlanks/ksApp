#include "ofxScale.h"


ofxScale::settings::settings()
{
	scaFrom.setName("scaFrom");
	scaTo.setName("scaTo");
	time.setName("time");
    repeat.setName("repeat");
	delay.setName("delay");
	bezierPoint.setName("bezierPoint");
	useBezier.setName("useBezier");

	scaFrom = 1.0f;
	scaTo = 0;
	time = 2.0f;
	repeat = true;
	delay = 0;
	bezierPoint = 0;
	useBezier = false;
}

ofXml ofxScale::settings::serialize()
{
	ofXml X;

	ofParameterGroup G;
	G.setName("fxRotate_Settings");
	G.add(scaFrom);
	G.add(scaTo);
	G.add(time);
	G.add(repeat);
	G.add(delay);
	G.add(bezierPoint);
	G.add(useBezier);

	X.serialize(G);
	X.reset();
	return X;
}

bool ofxScale::settings::deserialize( ofXml X )
{
	ofParameterGroup G;
	G.setName("ofxScale_Settings");

	X.deserialize(G);
	bool bSuc = X.exists(G.getName());
	if(bSuc)
	{
		scaFrom = G.getFloat("scaFrom");
		scaTo = G.getFloat("scaTo");
		time = G.getFloat("time");
		delay = G.getFloat("delay");
		//mode = G.getFloat("mode");
		bezierPoint = G.getFloat("bezierPoint");
		useBezier = G.getFloat("useBezier");
	}

	return bSuc;	
}

ofxScale::ofxScale()
{
	n_tweener.removeAllTweens();

	animationType = NODEANIMATION_SCALE;
}

ofxScale::~ofxScale()
{

}

void ofxScale::set(ofXml X)
{
	Settings.deserialize(X);
}



void ofxScale::set(float scaFrom,float scaTo, float time){
	set(scaFrom,scaTo,time,true,&ofxTransitions::linear,0,0,false);
}

void ofxScale::set(float scaFrom,float scaTo, float time,bool repeat,float (ofxTransitions::*ease) (float,float,float,float)){
	set(scaFrom,scaTo,time,repeat,ease,0,0,false);
}

void ofxScale::set(float scaFrom,float scaTo, float time, bool repeat, 
				   float (ofxTransitions::*ease) (float,float,float,float), float delay, float bezierPoint, bool useBezier){
	Settings.scaFrom = scaFrom;
	Settings.scaTo = scaTo;
	Settings.time = time;
	Settings.repeat = repeat;
	mode = ease;
	Settings.delay = delay;
	Settings.bezierPoint = bezierPoint;
	Settings.useBezier = useBezier;

	sal = Settings.scaFrom;

}

void ofxScale::update()
{	
	n_tweener.update();
	if (Settings.repeat)
	{
		if (sal==Settings.scaFrom)
		{
			n_tweener.removeTween(sal);
			n_tweener.addTween(sal,Settings.scaTo, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
		}
		if (sal==Settings.scaTo)
		{
			n_tweener.removeTween(sal);
			n_tweener.addTween(sal,Settings.scaFrom, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
		}
	}
	else
	{
		if (sal==Settings.scaFrom)
		{
			n_tweener.removeTween(sal);
			n_tweener.addTween(sal,Settings.scaTo, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
		}
	}
	
}

void ofxScale::copy(ofPtr<ofxScale> pScale)
{
	this->Settings.scaFrom = pScale->Settings.scaFrom;
	this->Settings.scaTo = pScale->Settings.scaTo;
	this->Settings.time = pScale->Settings.time;
	this->Settings.repeat = pScale->Settings.repeat;
	this->mode = pScale->mode;
	this->Settings.delay = pScale->Settings.delay;
	this->Settings.bezierPoint = pScale->Settings.bezierPoint;
	this->Settings.useBezier = pScale->Settings.useBezier;

	sal = Settings.scaFrom;
}

void ofxScale::resetTime()
{

}

void ofxScale::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxScale::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}