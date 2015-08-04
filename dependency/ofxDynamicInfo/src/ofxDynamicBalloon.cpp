#include "ofxDynamicBalloon.h"


ofxDynamicBalloon::settings::settings()
{
	lineColor.setName("lineColor");
	bgColor.setName("bgColor");
	lineSize.setName("lineSize");
	rectWidth.setName("rectWidth");
	rectHeight.setName("rectHeight");
	rectRound.setName("rectRound");

	lineColor = ofColor::black;
	bgColor = ofColor::white;
	lineSize = 1.0f;
	rectWidth = 100.0f;
	rectHeight = 100.0f;
	rectRound = 3.0f;
}

ofXml ofxDynamicBalloon::settings::serialize()
{
	ofXml X;

	ofParameterGroup G;
	G.setName("fxDynamicBalloon_Settings");
	G.add(lineColor);
	G.add(bgColor);
	G.add(lineSize);
	G.add(rectWidth);
	G.add(rectHeight);
	G.add(rectRound);

	X.serialize(G);
	X.reset();
	return X;
}

bool ofxDynamicBalloon::settings::deserialize( ofXml X )
{
	ofParameterGroup G;
	G.setName("ofxDynamicBalloon_Settings");

	X.deserialize(G);
	bool bSuc = X.exists(G.getName());
	if(bSuc)
	{
		lineColor = G.getColor("lineColor");
		bgColor = G.getColor("bgColor");
		lineSize = G.getFloat("lineSize");
		rectWidth = G.getFloat("rectWidth");
		rectHeight = G.getFloat("rectHeight");
		rectRound = G.getFloat("rectRound");
	}

	return bSuc;	
}

ofxDynamicBalloon::ofxDynamicBalloon()
{	
	//serialize(Settings.serialize());
}

ofxDynamicBalloon::~ofxDynamicBalloon()
{

}

void ofxDynamicBalloon::set(ofXml X)
{
	Settings.deserialize(X);
}


void ofxDynamicBalloon::set(float rectWidth,float rectHeight,float rectRound,ofColor lineColor,ofColor bgColor,float lineSize)
{
	Settings.rectWidth = rectWidth;
	Settings.rectHeight = rectHeight;
	Settings.rectRound = rectRound;
	Settings.lineSize = lineSize;
	Settings.lineColor = lineColor;
	Settings.bgColor = bgColor;
}

void ofxDynamicBalloon::update()
{	

}

void ofxDynamicBalloon::draw()
{
	ofPushStyle();
	ofEnableAlphaBlending();
	
	ofSetColor(Settings.bgColor);
	ofFill();
	ofRectangle R;
	R.setFromCenter(0,0,Settings.rectWidth,Settings.rectHeight);
	ofRectRounded(R,Settings.rectRound);

	ofSetLineWidth(Settings.lineSize);
	ofSetColor(Settings.lineColor);
	ofNoFill();
	ofRectRounded(R,Settings.rectRound);

	ofPopStyle();
}

void ofxDynamicBalloon::draw(float x,float y)
{
	set(100,100);
	draw();
}

void ofxDynamicBalloon::draw(float x, float y,float w,float h)
{
	set(w,h);
	draw();
}

float ofxDynamicBalloon::getWidth()
{
	return Settings.rectWidth;
}

float ofxDynamicBalloon::getHeight()
{
	return Settings.rectHeight;
}

void ofxDynamicBalloon::changAlpha(int alpha)
{
	ofColor lCol = Settings.lineColor; 
	lCol.a = alpha;
	Settings.lineColor = lCol;
	ofColor bCol = Settings.bgColor;
	bCol.a = alpha;
	Settings.bgColor = bCol;

}

void ofxDynamicBalloon::resetTime()
{

}

void ofxDynamicBalloon::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxDynamicBalloon::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}

