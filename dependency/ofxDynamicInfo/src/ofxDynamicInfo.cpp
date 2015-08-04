#include "ofxDynamicInfo.h"

ofxDynamicInfo::ofxDynamicInfo(ofPoint pos,ofPtr<ofxVisibleThing> vis,ofPtr<ofxNodeAnimation> nodeAn,ofPtr<ofxStyleAnimation> styleAn)
{
	init(pos,vis,nodeAn,styleAn);
}
ofxDynamicInfo::ofxDynamicInfo(ofPoint Pos, string VisibleThingXmlFile,string NodeAnimXmlFile,string StyAnimXmlFile)
{
	setPosition(pos);

	ofXml vis,noAn,styAn;
	vis.load(VisibleThingXmlFile);
	noAn.load(NodeAnimXmlFile);
	styAn.load(StyAnimXmlFile);
	this->visibleThing->deserialize(vis);
	this->nodeAn->deserialize(noAn);
	this->styleAn->deserialize(styAn);

	ang=0;
}

ofxDynamicInfo::ofxDynamicInfo(ofPoint Pos,ofXml  VisibleThingXmlFile,ofXml  NodeAnimXmlFile,ofXml  StyAnimXmlFile)
{
	setPosition(pos);
	ofXml();

	this->visibleThing->deserialize(VisibleThingXmlFile);
	this->nodeAn->deserialize(NodeAnimXmlFile);
	this->styleAn->deserialize(StyAnimXmlFile);

	ang=0;
}

void ofxDynamicInfo::init(ofPoint pos,ofPtr<ofxVisibleThing> vis,ofPtr<ofxNodeAnimation> nodeAn,ofPtr<ofxStyleAnimation> styleAn)
{
	setPosition(pos);
	this->pos = pos;
	this->visibleThing = vis;
	this->nodeAn = nodeAn;
	this->styleAn = styleAn;

	ang=0;
}

void ofxDynamicInfo::customDraw()
{
	ofPushStyle();
	ofPushMatrix();
	ofEnableAlphaBlending();

	ofVec3f r(0,0,1);
	if (nodeAn.use_count()>0)
	{
		this->rotate((nodeAn->getAng()-ang),r);
		this->setScale(nodeAn->getScl());

		ang=nodeAn->getAng();
	}

	visibleThing->draw();

	ofPopMatrix();
	ofPopStyle();

}

void ofxDynamicInfo::update()
{
	if (nodeAn.use_count()>0)
	{
		nodeAn->update();
		ofPoint offPos = nodeAn->getOffset();
		//ofPoint pos = getPosition();
		setPosition(pos.x+offPos.x,pos.y+offPos.y,0);
	}
	if (styleAn.use_count()>0)
	{
		visibleThing->changAlpha(styleAn->getAlpha());
	}
}


void ofxDynamicInfo::changePos(float x,float y)
{
	ofPoint p(x,y);
	setPosition(p);

	init(p,visibleThing,nodeAn,styleAn); 
}

void ofxDynamicInfo::addNodeAnimation(ofPtr<ofxNodeAnimation> _nodeAn)
{
	ofPoint p =getPosition();
	init(p,this->visibleThing,_nodeAn,this->styleAn);
}

void ofxDynamicInfo::addStyleAnimation(ofPtr<ofxStyleAnimation> _styleAn)
{
	ofPoint p =getPosition();
	init(p,this->visibleThing,this->nodeAn,_styleAn);

}

void ofxDynamicInfo::serialize(ofXml& X)
{
	this->visibleThing->serialize(X);
	this->nodeAn->serialize(X);
	this->styleAn->serialize(X);
}

void ofxDynamicInfo::serialize(string xmlFile)
{
	ofXml X;
	X.load(xmlFile);
	this->visibleThing->serialize(X);
	this->nodeAn->serialize(X);
	this->styleAn->serialize(X);
}

void ofxDynamicInfo::deserialize(ofXml& X)
{

}

void ofxDynamicInfo::deserialize(string xmlFile)
{

}