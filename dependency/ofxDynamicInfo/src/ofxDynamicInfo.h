#pragma once
#ifndef OFXDYNAMICINFO_H
#define OFXDYNAMICINFO_H

#include "ofxDynamicBalloon.h"
#include "ofxDialogBox.h"
#include "ofxShake.h"
#include "ofxMoveShake.h"
#include "ofxTextThing.h"
#include "ofxStyleAnimation.h"
#include "ofxFadeEffect.h"
#include "ofxImageThing.h"
#include "ofxRotate.h"
#include "ofxScale.h"


class ofxDynamicInfo:
	public  ofNode
{
public:

	ofxDynamicInfo(ofPoint pos,ofPtr<ofxVisibleThing> vis,
		ofPtr<ofxNodeAnimation> nodeAn=ofPtr<ofxNodeAnimation>() ,
		ofPtr<ofxStyleAnimation> styleAn=ofPtr<ofxStyleAnimation>());
	ofxDynamicInfo(ofPoint pos,
		string VisibleThingXmlFile,
		string NodeAnimXmlFile = "",
		string StyAnimXmlFile = "");
	ofxDynamicInfo(ofPoint Pos, 
		ofXml VisibleThingXmlFile,
		ofXml NodeAnimXmlFile = ofXml(),
		ofXml StyAnimXmlFile = ofXml());

    virtual void customDraw();
	void init(ofPoint pos,ofPtr<ofxVisibleThing> vis,
		ofPtr<ofxNodeAnimation> nodeAn=ofPtr<ofxNodeAnimation>() ,
		ofPtr<ofxStyleAnimation> styleAn=ofPtr<ofxStyleAnimation>());

	void addNodeAnimation(ofPtr<ofxNodeAnimation> _nodeAn);
	void addStyleAnimation(ofPtr<ofxStyleAnimation> _styleAn);
	void changePos(float x,float y);

	void serialize(ofXml& X);
	void deserialize(ofXml& X);
	void serialize(string xmlFile);
	void deserialize(string xmlFile);

	void update();
	
private:

	bool bStyAn;
	bool bNodeAn;

	ofPoint pos;
	float ang;

	ofPtr<ofxVisibleThing> visibleThing;
	ofPtr<ofxNodeAnimation> nodeAn;
	ofPtr<ofxStyleAnimation> styleAn;

};

#endif