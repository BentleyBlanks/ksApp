#pragma once
#ifndef KSINFORMATION_H
#define KSINFORMATION_H

#include "ofxDynamicInfo.h"
#include "ofMain.h"

class ksInformation:
	public  ofNode
{
public:

	ksInformation();
	~ksInformation();

	virtual void customDraw();
	void update();

	void setPos(ofPoint p);
	void setString(string s);

	void disableVisible();
	void visable();
	void changeVisible();

	void changeInfo(string info);
	void changeAuthor(string author);
	void changeDate(string date);
	void changeTag(string tag);

private:
	ofPtr<ofxTextThing> text,text_date,text_author,text_tag;
	ofPtr<ofxImageThing> image;
	ofPtr<ofxMoveShake>  shake;
	ofPtr<ofxDynamicInfo> dy_info,dy_image,dy_date,dy_author,dy_tag;
	ofPtr<ofxFadeEffect> fade;

	ofPoint pos;
	ofPoint text_pos,date_pos,author_pos,tag_pos;

	string str,str_date,str_author,str_tag;
	int info_size,date_size,tag_size;
	bool visible;

};

#endif