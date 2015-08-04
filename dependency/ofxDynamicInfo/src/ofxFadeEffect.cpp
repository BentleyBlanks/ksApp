#include "ofxFadeEffect.h"


ofxFadeEffect::settings::settings()
{
    alphaFrom.setName("alphaFrom");
	alphaTo.setName("alphaTo");
	time.setName("time");
	delay.setName("delay");

	alphaFrom = 255;
	alphaTo = 0;
	time = 100.0f;
	delay = 0;
}

ofXml ofxFadeEffect::settings::serialize()
{
	ofXml X;

	ofParameterGroup G;
	G.setName("ofxFadeEffect_Settings");
	G.add(alphaFrom);
	G.add(alphaTo);
	G.add(time);
	G.add(delay);

	X.serialize(G);
	X.reset();
	return X;
}

bool ofxFadeEffect::settings::deserialize( ofXml X )
{
	ofParameterGroup G;
	G.setName("fxShake_Settings");

	X.deserialize(G);
	bool bSuc = X.exists(G.getName());
	if(bSuc)
	{
		alphaFrom = G.getInt("alphaFrom");
		alphaTo = G.getInt("alphaTo");
		time = G.getFloat("time");
		delay = G.getFloat("delay");
	}

	return bSuc;	
}

ofxFadeEffect::ofxFadeEffect()
{	
	creatTime = ofGetElapsedTimef();
}

ofxFadeEffect::~ofxFadeEffect()
{

}

void ofxFadeEffect::set(ofXml X)
{
	Settings.deserialize(X);
}


void ofxFadeEffect::set(float time,int alphaFrom/* =255 */,int alphaTo/* =0 */,float delay /* = 0 */)
{
	Settings.time = time;
	Settings.alphaFrom = alphaFrom;
	Settings.alphaTo = alphaTo;
	Settings.delay = delay;

}

void ofxFadeEffect::update()
{
	float t = ofGetElapsedTimef()-creatTime;
	if ((t>=Settings.delay)&&(t<=(Settings.delay+Settings.time)))
	{
		alpha = (Settings.alphaTo-Settings.alphaFrom)*(t-Settings.delay)/Settings.time + Settings.alphaFrom;
	}

}


void ofxFadeEffect::copy(ofPtr<ofxFadeEffect> pfade)
{
	this->Settings.time = pfade->Settings.time;
	this->Settings.alphaFrom = pfade->Settings.alphaFrom;
	this->Settings.alphaTo = pfade->Settings.alphaTo;
	this->Settings.delay = pfade->Settings.delay;
}

int ofxFadeEffect::getAlpha()
{
	update();
	return alpha;
}

void ofxFadeEffect::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxFadeEffect::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}

