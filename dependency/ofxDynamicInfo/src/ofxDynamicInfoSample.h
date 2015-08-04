#pragma once
#ifndef OFXDYNAMICINFOSAMPLE_H
#define OFXDYNAMICINFOSAMPLE_H

#include "ofxDynamicInfoGroup.h"

class ofxDynamicInfoSample
{
public:
	ofxDynamicInfoSample();
	~ofxDynamicInfoSample();

	virtual void update();
	virtual void draw();

	void staticText(string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void staticImage(string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),float width=200,float height=150,int imgAlpha=255,ofColor imgColor=ofColor::white);

	void sraticImageInfo(string info,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void staticRectInfo(string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void staticDialogInfo(string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	
	void fadeInText(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeInImage(float time,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		float width=200,float height=150,int imgAlpha=255,ofColor imgColor=ofColor::white);
	void fadeInImageInfo(float time,string info,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeInRectInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeInDialogInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);

	void fadeOutText(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeOutImage(float time,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		float width=200,float height=150,int imgAlpha=255,ofColor imgColor=ofColor::white);
	void fadeOutImageInfo(float time,string info,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeOutRectInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeOutDialogInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);

	void rotateText(float ang,float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black,bool repeat=false);
	void rotateImage(float ang,float time,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		float width=200,float height=150,int imgAlpha=255,ofColor imgColor=ofColor::white,bool repeat=false);
	void rotateImageInfo(float ang,float time,string info,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black,bool repeat=false);
	void rotateRectInfo(float ang,float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black,bool repeat=false);
	void rotateDialogInfo(float ang,float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black,bool repeat=false);

	void fadeScaleInText(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeScaleInImage(float time,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		float width=200,float height=150,int imgAlpha=255,ofColor imgColor=ofColor::white);
	void fadeScaleInImageInfo(float time,string info,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeScaleInRectInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeScaleInDialogInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);

	void fadeScaleOutText(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeScaleOutImage(float time,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		float width=200,float height=150,int imgAlpha=255,ofColor imgColor=ofColor::white);
	void fadeScaleOutImageInfo(float time,string info,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeScaleOutRectInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeScaleOutDialogInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);

	void fadeShakeText(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeShakeImage(float time,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		float width=200,float height=150,int imgAlpha=255,ofColor imgColor=ofColor::white);
	void fadeShakeImageInfo(float time,string info,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeShakeRectInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void fadeShakeDialogInfo(float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);

	void rollText(float Distance,float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),bool horizon=true,string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void rollImage(float Distance,float time,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),bool horizon=true,
		float width=200,float height=150,int imgAlpha=255,ofColor imgColor=ofColor::white);
	void rollImageInfo(float Distance,float time,string info,string imgPath,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),bool horizon=true,
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void rollRectInfo(float Distance,float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),bool horizon=true,
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);
	void rollDialogInfo(float Distance,float time,string info,ofPoint pos = ofPoint(ofGetWidth()/2,ofGetHeight()/2),bool horizon=true,
		string fontPath="text1.ttf",int infoSize=20,ofColor textColor=ofColor::black);


private:
	float width,height;
	string info;
	ofPtr<ofxDynamicInfoGroup> dynGroup;
	vector<ofPtr<ofxDynamicInfo> > Dyns;
};

#endif