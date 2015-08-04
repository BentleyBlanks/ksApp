#include "ofxDynamicInfoSample.h"

ofxDynamicInfoSample::ofxDynamicInfoSample()
{

}


ofxDynamicInfoSample::~ofxDynamicInfoSample()
{

}

void ofxDynamicInfoSample::draw()
{
	dynGroup->draw();
}
void ofxDynamicInfoSample::update()
{
	dynGroup->update();
}

void ofxDynamicInfoSample::staticText(string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pText));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::staticImage(string imgPath,ofPoint pos,float width,float height,int imgAlpha,ofColor imgColor)
{
	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height,imgAlpha,imgColor);
	this->width = width;
	this->height = height;

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::sraticImageInfo(string info,string imgPath,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*2.0;
	this->height = (pText->getHeight())*2.3;
	this->info = info;

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}


void ofxDynamicInfoSample::staticRectInfo(string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicBalloon> pBal;
	pBal.reset(new ofxDynamicBalloon);
	pBal->set(width,height);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pBal));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::staticDialogInfo(string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.30;
	this->info = info;
	float arrowWidth = width*0.1;
	float arrowHeight = height*0.3;

	ofPtr<ofxDialogBox> pDlg;
	pDlg.reset(new ofxDialogBox);
	pDlg->set(width,height,0.5f,arrowWidth,arrowHeight);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pDlg));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeInText(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pText,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeInImage(float time,string imgPath,ofPoint pos,float width,float height,int imgAlpha,ofColor imgColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height,imgAlpha,imgColor);
	this->width = width;
	this->height = height;

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeInImageInfo(float time,string info,string imgPath,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*2.0;
	this->height = (pText->getHeight())*2.3;
	this->info = info;

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}


void ofxDynamicInfoSample::fadeInRectInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicBalloon> pBal;
	pBal.reset(new ofxDynamicBalloon);
	pBal->set(width,height);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pBal,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeInDialogInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.30;
	this->info = info;
	float arrowWidth = width*0.1;
	float arrowHeight = height*0.3;

	ofPtr<ofxDialogBox> pDlg;
	pDlg.reset(new ofxDialogBox);
	pDlg->set(width,height,0.5f,arrowWidth,arrowHeight);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pDlg,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeOutText(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pText,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeOutImage(float time,string imgPath,ofPoint pos,float width,float height,int imgAlpha,ofColor imgColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height,imgAlpha,imgColor);
	this->width = width;
	this->height = height;

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeOutImageInfo(float time,string info,string imgPath,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*2.0;
	this->height = (pText->getHeight())*2.3;
	this->info = info;

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}


void ofxDynamicInfoSample::fadeOutRectInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicBalloon> pBal;
	pBal.reset(new ofxDynamicBalloon);
	pBal->set(width,height);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pBal,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}


void ofxDynamicInfoSample::fadeOutDialogInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.30;
	this->info = info;
	float arrowWidth = width*0.1;
	float arrowHeight = height*0.3;

	ofPtr<ofxDialogBox> pDlg;
	pDlg.reset(new ofxDialogBox);
	pDlg->set(width,height,0.5f,arrowWidth,arrowHeight);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pDlg,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,ofPtr<ofxNodeAnimation>(),pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rotateText(float ang,float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor,bool repeat)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxRotate> pRotate;
	pRotate.reset(new ofxRotate);
	pRotate->set(ang,time,repeat);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pText,pRotate));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rotateImage(float ang,float time,string imgPath,ofPoint pos,float width,float height,int imgAlpha,ofColor imgColor,bool repeat)
{
	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height,imgAlpha,imgColor);
	this->width = width;
	this->height = height;

	ofPtr<ofxRotate> pRotate;
	pRotate.reset(new ofxRotate);
	pRotate->set(ang,time,repeat);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pRotate));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rotateImageInfo(float ang,float time,string info,string imgPath,ofPoint pos, string fontPath,int infoSize,ofColor textColor,bool repeat)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*2.0;
	this->height = (pText->getHeight())*2.3;
	this->info = info;

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height);
	ofPtr<ofxRotate> pRotate;
	pRotate.reset(new ofxRotate);
	pRotate->set(ang,time,repeat);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pRotate));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pRotate));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rotateRectInfo(float ang,float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor,bool repeat)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicBalloon> pBal;
	pBal.reset(new ofxDynamicBalloon);
	pBal->set(width,height);
	ofPtr<ofxRotate> pRotate;
	pRotate.reset(new ofxRotate);
	pRotate->set(ang,time,repeat);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pBal,pRotate));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pRotate));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}
void ofxDynamicInfoSample::rotateDialogInfo(float ang,float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor,bool repeat)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.30;
	this->info = info;
	float arrowWidth = width*0.1;
	float arrowHeight = height*0.3;

	ofPtr<ofxDialogBox> pDlg;
	pDlg.reset(new ofxDialogBox);
	pDlg->set(width,height,0.5f,arrowWidth,arrowHeight);
	ofPtr<ofxRotate> pRotate;
	pRotate.reset(new ofxRotate);
	pRotate->set(ang,time,repeat);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pDlg,pRotate));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pRotate));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeScaleInText(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(0,1,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pText,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeScaleInImage(float time,string imgPath,ofPoint pos,float width,float height,int imgAlpha,ofColor imgColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height,imgAlpha,imgColor);
	this->width = width;
	this->height = height;

	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(0,1,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeScaleInImageInfo(float time,string info,string imgPath,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*2.0;
	this->height = (pText->getHeight())*2.3;
	this->info = info;

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height);
	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(0,1,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pScale,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}


void ofxDynamicInfoSample::fadeScaleInRectInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicBalloon> pBal;
	pBal.reset(new ofxDynamicBalloon);
	pBal->set(width,height);
	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(0,1,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pBal,pScale,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeScaleInDialogInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,0,255);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.30;
	this->info = info;
	float arrowWidth = width*0.1;
	float arrowHeight = height*0.3;

	ofPtr<ofxDialogBox> pDlg;
	pDlg.reset(new ofxDialogBox);
	pDlg->set(width,height,0.5f,arrowWidth,arrowHeight);
	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(0,1,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pDlg,pScale,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeScaleOutText(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(1,0,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pText,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeScaleOutImage(float time,string imgPath,ofPoint pos,float width,float height,int imgAlpha,ofColor imgColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height,imgAlpha,imgColor);
	this->width = width;
	this->height = height;

	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(1,0,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeScaleOutImageInfo(float time,string info,string imgPath,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*2.0;
	this->height = (pText->getHeight())*2.3;
	this->info = info;

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height);
	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(1,0,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pScale,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}


void ofxDynamicInfoSample::fadeScaleOutRectInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicBalloon> pBal;
	pBal.reset(new ofxDynamicBalloon);
	pBal->set(width,height);
	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(1,0,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pBal,pScale,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeScaleOutDialogInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.30;
	this->info = info;
	float arrowWidth = width*0.1;
	float arrowHeight = height*0.3;

	ofPtr<ofxDialogBox> pDlg;
	pDlg.reset(new ofxDialogBox);
	pDlg->set(width,height,0.5f,arrowWidth,arrowHeight);
	ofPtr<ofxScale> pScale;
	pScale.reset(new ofxScale);
	pScale->set(1,0,time,false);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pDlg,pScale,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pScale,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}


void ofxDynamicInfoSample::fadeShakeText(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(10,0.1,&ofxTransitions::easeInCirc,false,20);
	
	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pText,pShake,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeShakeImage(float time,string imgPath,ofPoint pos,float width,float height,int imgAlpha,ofColor imgColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height,imgAlpha,imgColor);
	this->width = width;
	this->height = height;
	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(10,0.1,&ofxTransitions::easeInCirc,false,20);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pShake,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeShakeImageInfo(float time,string info,string imgPath,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*2.0;
	this->height = (pText->getHeight())*2.3;
	this->info = info;

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height);
	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(10,0.1,&ofxTransitions::easeInCirc,false,20);


	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pShake,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pShake,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}


void ofxDynamicInfoSample::fadeShakeRectInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicBalloon> pBal;
	pBal.reset(new ofxDynamicBalloon);
	pBal->set(width,height);
	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(10,0.1,&ofxTransitions::easeInCirc,false,20);


	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pBal,pShake,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pShake,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::fadeShakeDialogInfo(float time,string info,ofPoint pos,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxFadeEffect> pFade;
	pFade.reset(new ofxFadeEffect);
	pFade->set(time,255,0);

	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.30;
	this->info = info;
	float arrowWidth = width*0.1;
	float arrowHeight = height*0.3;

	ofPtr<ofxDialogBox> pDlg;
	pDlg.reset(new ofxDialogBox);
	pDlg->set(width,height,0.5f,arrowWidth,arrowHeight);
	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(10,0.1,&ofxTransitions::easeInCirc,false,20);


	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pDlg,pShake,pFade));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pShake,pFade));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rollText(float distance,float time,string info,ofPoint pos,bool horizon,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
    pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(distance,time,&ofxTransitions::linear,horizon,0);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pText,pShake));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rollImage(float distance,float time,string imgPath,ofPoint pos,bool horizon,float width,float height,int imgAlpha,ofColor imgColor)
{
	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height,imgAlpha,imgColor);
	this->width = width;
	this->height = height;
	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(distance,time,&ofxTransitions::linear,horizon,0);

	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pShake));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rollImageInfo(float distance,float time,string info,string imgPath,ofPoint pos,bool horizon,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*2.0;
	this->height = (pText->getHeight())*2.3;
	this->info = info;

	ofPtr<ofxImageThing> pImage;
	pImage.reset(new ofxImageThing);
	pImage->set(imgPath,width,height);
	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(distance,time,&ofxTransitions::linear,horizon,0);


	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pImage,pShake));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pShake));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rollRectInfo(float distance,float time,string info,ofPoint pos,bool horizon, string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
    pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.40;
	this->info = info;

	ofPtr<ofxDynamicBalloon> pBal;
	pBal.reset(new ofxDynamicBalloon);
	pBal->set(width,height);
	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(distance,time,&ofxTransitions::linear,horizon,0);


	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pBal,pShake));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pShake));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}

void ofxDynamicInfoSample::rollDialogInfo(float distance,float time,string info,ofPoint pos,bool horizon,string fontPath,int infoSize,ofColor textColor)
{
	ofPtr<ofxTextThing> pText;
	pText.reset(new ofxTextThing);
	pText->set(info,fontPath,infoSize,textColor);
	this->width = (pText->getWidth())*1.30;
	this->height = (pText->getHeight())*1.30;
	this->info = info;
	float arrowWidth = width*0.1;
	float arrowHeight = height*0.3;

	ofPtr<ofxDialogBox> pDlg;
	pDlg.reset(new ofxDialogBox);
	pDlg->set(width,height,0.5f,arrowWidth,arrowHeight);
	ofPtr<ofxShake> pShake;
	pShake.reset(new ofxShake);
	pShake->set(distance,time,&ofxTransitions::linear,horizon,0);


	ofPtr<ofxDynamicInfo> pDyn;
	pDyn.reset(new ofxDynamicInfo(pos,pDlg,pShake));
	Dyns.push_back(pDyn);
	pDyn.reset(new ofxDynamicInfo(pos,pText,pShake));
	Dyns.push_back(pDyn);

	dynGroup.reset(new ofxDynamicInfoGroup(Dyns));
}
