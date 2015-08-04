#pragma once
#ifndef OFXDYNAMICINFOGROUP_H
#define OFXDYNAMICINFOGROUP_H

#include "ofxDynamicInfo.h"

class ofxDynamicInfoGroup:
	public ofNode
{
public:
	ofxDynamicInfoGroup(vector<ofPtr<ofxDynamicInfo> > _Dyns);
	ofxDynamicInfoGroup(
		vector<ofPtr<ofxVisibleThing> > VThings,
		ofPtr<ofxNodeAnimation> pNodeAnim = ofPtr<ofxNodeAnimation>(),
		ofPtr<ofxStyleAnimation> pStyAnim = ofPtr<ofxStyleAnimation>(),
		ofPoint Pos = ofPoint(0,0,0)
		);	
	~ofxDynamicInfoGroup();

	virtual void update();
	virtual void customDraw();

	void addDynInfo(ofPtr<ofxDynamicInfo> pDynInfo);
	void addDynInfo(		
		ofPtr<ofxVisibleThing> pThing, 
		ofPoint Pos = ofPoint(0,0),
		ofPtr<ofxNodeAnimation> pNodeAnim = ofPtr<ofxNodeAnimation>(),
		ofPtr<ofxStyleAnimation> pStyAnim = ofPtr<ofxStyleAnimation>()
		);	

	void setNodeAnimationToAll(ofPtr<ofxNodeAnimation> pNodeAnim);
	void setStyleAnimationToAll(ofPtr<ofxStyleAnimation> pStyAnim);

	void setPosToAll(ofPoint P);
	void disableVisible();
	void visable();
	void changeVisible();
	void reseet();

	void serialize(ofXml& X);
	void deserialize(ofXml& X);
	
	void serialize(string xmlFile);
	void deserialize(string xmlFile);

private:
	vector<ofPtr<ofxDynamicInfo> > Dyns;
	bool visible;
};

#endif