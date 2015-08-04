#include "ofxDialogBox.h"


ofxDialogBox::settings::settings()
{
	lineColor.setName("lineColor");
	bgColor.setName("bgColor");
	lineSize.setName("lineSize");
	rectWidth.setName("rectWidth");
	rectHeight.setName("rectHeight");
	arrowsWidth.setName("arrowsWidth");
	arrowsHeigh.setName("arrowsHeight");
	ratio.setName("ratio");

	lineColor = ofColor::black;
	bgColor = ofColor::white;
	lineSize = 1.0f;
	rectWidth = 100.0f;
	rectHeight = 100.0f;
	arrowsWidth = 20.0f;
	arrowsHeigh = 30.0f;
	ratio = 0.5f;
}

ofXml ofxDialogBox::settings::serialize()
{
	ofXml X;

	ofParameterGroup G;
	G.setName("fxDynamicBalloon_Settings");
	G.add(lineColor);
	G.add(bgColor);
	G.add(lineSize);
	G.add(rectWidth);
	G.add(rectHeight);
	G.add(arrowsWidth);
	G.add(arrowsHeigh);
	G.add(ratio);

	X.serialize(G);
	X.reset();
	return X;
}

bool ofxDialogBox::settings::deserialize( ofXml X )
{
	ofParameterGroup G;
	G.setName("ofxDialogBox_Settings");

	X.deserialize(G);
	bool bSuc = X.exists(G.getName());
	if(bSuc)
	{
		lineColor = G.getColor("lineColor");
		bgColor = G.getColor("bgColor");
		lineSize = G.getFloat("lineSize");
		rectWidth = G.getFloat("rectWidth");
		rectHeight = G.getFloat("rectHeight");
		arrowsWidth = G.getFloat("arrowsWidth");
		arrowsHeigh = G.getFloat("arrowsheigh");
		ratio = G.getFloat("ratio");
	}

	return bSuc;	
}

ofxDialogBox::ofxDialogBox()
{	
	//serialize(Settings.serialize());
}

ofxDialogBox::~ofxDialogBox()
{

}

void ofxDialogBox::set(ofXml X)
{
	Settings.deserialize(X);
}


void ofxDialogBox::set(float rectWidth,float rectHeight,
					   float ratio/* =0.5f */,float arrowsWidth/* =20.0f */,float arrowsHeight/* =50.0f */,
					   ofColor lineColor/* =ofColor::black */,ofColor bgColor/* =ofColor::white */,float lineSize/* =1.0f */)
{
	Settings.rectWidth = rectWidth;
	Settings.rectHeight = rectHeight;
	Settings.ratio = ratio;
	Settings.arrowsWidth= arrowsWidth;
	Settings.arrowsHeigh = arrowsHeight;
	Settings.lineSize = lineSize;
	Settings.lineColor = lineColor;
	Settings.bgColor = bgColor;
}

void ofxDialogBox::update()
{	

}

void ofxDialogBox::draw()
{
	ofPushStyle();
	ofEnableAlphaBlending();

	ofSetColor(Settings.bgColor);
	ofFill();
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
	ofVertex(-Settings.rectWidth/2,-Settings.rectHeight/2);
	ofVertex(Settings.rectWidth/2,-Settings.rectHeight/2);
	ofVertex(Settings.rectWidth/2,Settings.rectHeight/2);
	ofVertex(Settings.arrowsWidth/2,Settings.rectHeight/2);
	ofVertex(-Settings.rectWidth/2+Settings.rectWidth*Settings.ratio,Settings.rectHeight/2+Settings.arrowsHeigh);
	ofVertex(-Settings.arrowsWidth/2,Settings.rectHeight/2);
	ofVertex(-Settings.rectWidth/2,Settings.rectHeight/2);
	ofEndShape();  

	ofNoFill();
	ofSetLineWidth(Settings.lineSize);
	ofSetColor(Settings.lineColor);
	ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
	ofVertex(-Settings.rectWidth/2,-Settings.rectHeight/2);
	ofVertex(Settings.rectWidth/2,-Settings.rectHeight/2);
	ofVertex(Settings.rectWidth/2,Settings.rectHeight/2);
	ofVertex(Settings.arrowsWidth/2,Settings.rectHeight/2);
	ofVertex(-Settings.rectWidth/2+Settings.rectWidth*Settings.ratio,Settings.rectHeight/2+Settings.arrowsHeigh);
	ofVertex(-Settings.arrowsWidth/2,Settings.rectHeight/2);
	ofVertex(-Settings.rectWidth/2,Settings.rectHeight/2);
	ofEndShape();  

	ofPopStyle();
}

void ofxDialogBox::draw(float x,float y)
{
	set(100,100);
	draw();
}

void ofxDialogBox::draw(float x, float y,float w,float h)
{
	set(w,h);
	draw();
}

float ofxDialogBox::getWidth()
{
	return Settings.rectWidth;
}

float ofxDialogBox::getHeight()
{
	return Settings.rectHeight;
}


void ofxDialogBox::changAlpha(int alpha)
{
	ofColor lCol = Settings.lineColor; 
	lCol.a = alpha;
	Settings.lineColor = lCol;
	ofColor bCol = Settings.bgColor;
	bCol.a = alpha;
	Settings.bgColor = bCol;

}

void ofxDialogBox::resetTime()
{

}

void ofxDialogBox::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxDialogBox::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}

