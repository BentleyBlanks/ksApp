#include "ofxDynamicInfoGroup.h"


ofxDynamicInfoGroup::ofxDynamicInfoGroup(vector<ofPtr<ofxDynamicInfo> > _Dyns)
{
	Dyns = _Dyns;
	visible = true;
}

ofxDynamicInfoGroup::ofxDynamicInfoGroup(vector<ofPtr<ofxVisibleThing> > VThings,
	ofPtr<ofxNodeAnimation> pNodeAnim,ofPtr<ofxStyleAnimation> pStyAnim,ofPoint Pos)
{
	for (int i = 0; i < VThings.size(); i++)
	{
		ofPtr<ofxDynamicInfo> pDyn;
		pDyn.reset(new ofxDynamicInfo(Pos,VThings[i],pNodeAnim,pStyAnim));
		Dyns.push_back(pDyn);
	}

	visible = true;
}

ofxDynamicInfoGroup::~ofxDynamicInfoGroup()
{

}

void ofxDynamicInfoGroup::customDraw()
{
	if (visible)
	{
		for (int i = 0; i < Dyns.size(); i++)
		{
			Dyns[i]->update();
			Dyns[i]->draw();
		}
	}
	

}

void ofxDynamicInfoGroup::update()
{
	if (visible)
	{
		for (int i = 0; i < Dyns.size(); i++)
		{
			Dyns[i]->update();
		}
	}
	
}

void ofxDynamicInfoGroup::addDynInfo(ofPtr<ofxDynamicInfo> pDynInfo)
{
	Dyns.push_back(pDynInfo);
}

void ofxDynamicInfoGroup::addDynInfo(ofPtr<ofxVisibleThing> pThing, ofPoint Pos,ofPtr<ofxNodeAnimation> pNodeAnim,ofPtr<ofxStyleAnimation> pStyAnim )
{
	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(Pos,pThing,pNodeAnim,pStyAnim));
	Dyns.push_back(pDyn);
}

void ofxDynamicInfoGroup::setNodeAnimationToAll(ofPtr<ofxNodeAnimation> pNodeAnim)
{
	for (int i = 0; i < Dyns.size(); i++)
	{
		Dyns[i]->addNodeAnimation(pNodeAnim);
	}

}

void ofxDynamicInfoGroup::setStyleAnimationToAll(ofPtr<ofxStyleAnimation> pStyAnim)
{
	for (int i = 0; i < Dyns.size(); i++)
	{
		Dyns[i]->addStyleAnimation(pStyAnim);
	}

}

void ofxDynamicInfoGroup::setPosToAll(ofPoint P)
{
	for (int i = 0; i < Dyns.size(); i++)
	{
	Dyns[i]->changePos(P.x,P.y);
	}	
}

void ofxDynamicInfoGroup::disableVisible()
{
	visible=false;
}
void ofxDynamicInfoGroup::visable()
{
	visible=true;
}
void ofxDynamicInfoGroup::changeVisible()
{
	visible=!visible;
}

void ofxDynamicInfoGroup::reseet()
{
	Dyns.clear();
}