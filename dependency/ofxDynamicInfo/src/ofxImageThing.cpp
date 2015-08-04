#include "ofxImageThing.h"


ofxImageThing::settings::settings()
{
	imgPath.setName("imgPath");
	imgColor.setName("imgColor");
	width.setName("width");
	height.setName("height");
	imgAlpha.setName("imgAlpha");

	imgPath="img1.jpg";
	imgColor=ofColor::white;
	imgAlpha=255;
}

ofXml ofxImageThing::settings::serialize()
{
	ofXml X;

	ofParameterGroup G;
	G.setName("ofxImageThing_Settings");
	G.add(imgPath);
	G.add(imgColor);
	G.add(width);
	G.add(height);
	G.add(imgAlpha);

	X.serialize(G);
	X.reset();
	return X;
}

bool ofxImageThing::settings::deserialize( ofXml X )
{
	ofParameterGroup G;
	G.setName("ofxImageThing_Settings");

	X.deserialize(G);
	bool bSuc = X.exists(G.getName());
	if(bSuc)
	{
		imgPath= G.getString("imgPath");
		imgColor = G.getColor("imgColor");
		width = G.getFloat("width");
		height = G.getFloat("height");
		imgAlpha = G.getFloat("imgAlpha");
	}

	return bSuc;	
}

ofxImageThing::ofxImageThing()
{	
	//img.loadImage("img1.jpg");
}

ofxImageThing::~ofxImageThing()
{

}

void ofxImageThing::set(ofXml X)
{
	Settings.deserialize(X);
}

void ofxImageThing::set(string imgPath,int imgAlpha)
{
	img.loadImage(Settings.imgPath);
	float w = img.getWidth();
	float h = img.getHeight();

	set(imgPath,w,h,imgAlpha,ofColor::white);
}

void ofxImageThing::set(string imgPath,float width,float height,int imgAlpha,ofColor imgColor)
{
	Settings.imgPath = imgPath;
	imgColor.a = imgAlpha;
	Settings.imgColor = imgColor;
	Settings.width = width;
	Settings.height = height;

	img.loadImage(Settings.imgPath);
}

void ofxImageThing::update()
{	

}

void ofxImageThing::draw()
{
	ofPushStyle();
	ofEnableAlphaBlending();
	//ofTranslate(this->changePos);

	ofSetColor(Settings.imgColor);
	
	ofRectangle C;
	ofPoint cen(0,0);
	C.setFromCenter(cen,Settings.width,Settings.height);

	//img.setAnchorPoint(img.getWidth()/2,img.getHeight()/2);
	img.draw(C);

	ofPopStyle();
}

void ofxImageThing::draw(float x,float y)
{
	draw();
}

void ofxImageThing::draw(float x, float y,float w,float h)
{
	Settings.width = w;
	Settings.height = h;
	draw();
}

float ofxImageThing::getWidth()
{
	return Settings.width;
}

float ofxImageThing::getHeight()
{
	return Settings.width;
}

void ofxImageThing::changAlpha(int alpha)
{
	ofColor iCol = Settings.imgColor; 
	iCol.a = alpha;
	Settings.imgColor = iCol;
}

void ofxImageThing::resetTime()
{

}

void ofxImageThing::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxImageThing::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}