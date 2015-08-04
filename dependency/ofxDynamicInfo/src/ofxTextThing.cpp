#include "ofxTextThing.h"


ofxTextThing::settings::settings()
{
	textColor.setName("textColor");
	text.setName("text");
	fontPath.setName("fontPath");
	textSize.setName("textSize");

	textColor = ofColor::black;
	text = "ABCDEFG";
	fontPath="text1.ttf";
	textSize=10.0f;
}

ofXml ofxTextThing::settings::serialize()
{
	ofXml X;

	ofParameterGroup G;
	G.setName("fxDynamicBalloon_Settings");
	G.add(textColor);
	G.add(text);
	G.add(fontPath);
	G.add(textSize);

	X.serialize(G);
	X.reset();
	return X;
}

bool ofxTextThing::settings::deserialize( ofXml X )
{
	ofParameterGroup G;
	G.setName("ofxDynamicBalloon_Settings");

	X.deserialize(G);
	bool bSuc = X.exists(G.getName());
	if(bSuc)
	{
		textColor = G.getColor("textColor");
		text = G.getString("text");
		fontPath = G.getString("fontPath");
		textSize = G.getFloat("textSize");
	}

	return bSuc;	
}

ofxTextThing::ofxTextThing()
{	
	//textFont.loadFont("text1.ttf",5);
	center = true;
}

ofxTextThing::~ofxTextThing()
{

}

void ofxTextThing::set(ofXml X)
{
	//Settings.deserialize(X);
}

//void ofxTextThing::set(string text)
//{
//	set(text,"text1.ttf");
//}


void ofxTextThing::set(string text,string fontPath,float textSize,ofColor textColor,bool center)
{
	Settings.text = text;
	Settings.fontPath = fontPath;
	Settings.textColor = textColor;
	Settings.textSize = textSize;
	this->center = center;

	textFont.loadFont(fontPath,textSize);
}

void ofxTextThing::set(string text,string fontPath,float textWidth,float textHeight,ofColor textColor,bool center)
{
	Settings.text = text;
	Settings.fontPath = fontPath;
	Settings.textColor = textColor;
	this->center = center;

	ofRectangle r;
	int n=1;
	
	textFont.loadFont(fontPath,1);
	float x=textFont.stringWidth(text);
	float y=textFont.stringHeight(text);

	while (x<=textWidth&&y<=textHeight)
	{
		n++;
		textFont.loadFont(fontPath,n);
		x=textFont.stringWidth(text);
		y=textFont.stringHeight(text);
	}

	Settings.textSize = n-1;
	textFont.loadFont(fontPath,n-1);
}

void ofxTextThing::update()
{	

}

void ofxTextThing::draw()
{
	ofPushStyle();
	ofEnableAlphaBlending();

	float x=textFont.stringWidth(Settings.text);
	float y=textFont.stringHeight(Settings.text);
	ofSetColor(Settings.textColor);
	if (center)
	{
		textFont.drawString(Settings.text,-x/2,y/2);
	}
	else textFont.drawString(Settings.text,0,0);
	ofPopStyle();
}

void  ofxTextThing::draw(float x,float y)
{
	draw();
}

void  ofxTextThing::draw(float x, float y,float w,float h)
{
	set(Settings.text,Settings.fontPath,w,h);
	draw();
}

float  ofxTextThing::getWidth()
{
	return (textFont.stringWidth(Settings.text));
}

float  ofxTextThing::getHeight()
{
	return (textFont.stringHeight(Settings.text));
}

void ofxTextThing::changAlpha(int alpha)
{
	ofColor tCol = Settings.textColor; 
	tCol.a = alpha;
	Settings.textColor = tCol;
}

void ofxTextThing::resetTime()
{

}

void ofxTextThing::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxTextThing::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}