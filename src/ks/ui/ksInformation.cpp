#include "ksInformation.h"


ksInformation::ksInformation()
{
	str =string("your daddy?!?!\nyour daddy?!?!");
	str_date = string("Date:\nGGG");
	str_author = string("Auther:\nGGG");
	str_tag = string("AXXXXXX");

	ofTrueTypeFont textFont;
	textFont.loadFont("default/font/ksFont.otf",1);
	float len=textFont.stringWidth("a");

//	info_size = (len/1024.0)*ofGetWidth()*14;
//	date_size = (len/1024.0)*ofGetWidth()*10;
//	tag_size = (len/1024.0)*ofGetWidth()*14;
    info_size = (ofGetWidth()/1024.0)*12;
    date_size = (ofGetWidth()/1024.0)*8;
    tag_size = (ofGetWidth()/1024.0)*12;
    
	text_pos = ofPoint((300/1024.0)*ofGetWidth(),((-236/768.0)*ofGetHeight()));
	date_pos = ofPoint((750/1024.0)*ofGetWidth(),((-130/768.0)*ofGetHeight()));
	author_pos = ofPoint((850/1024.0)*ofGetWidth(),((-130/768.0)*ofGetHeight()));
	tag_pos =  ofPoint(((282.0/1024.0)*ofGetWidth()+(680.0/1024.0)*ofGetWidth()*0.5),((-78.0/768.0)*ofGetHeight()));

	ofColor textColor(208, 2, 27, 100);
	ofColor dateColor(0, 0, 0, 100);
	text.reset(new ofxTextThing);
	text->set(str,"default/font/ksFont.otf",info_size,textColor,false);	

	text_date.reset(new ofxTextThing);
	text_date->set(str_date,"default/font/ksFont.otf",date_size,dateColor,false);

	text_author.reset(new ofxTextThing);
	text_author->set(str_author,"default/font/ksFont.otf",date_size,dateColor,false);

	text_tag.reset(new ofxTextThing);
	text_tag->set(str_tag,"default/font/ksFont.otf",tag_size,ofColor::white,true);	

	pos = ofPoint(((272.0/1024.0)*ofGetWidth()+(680.0/1024.0)*ofGetWidth()*0.5),((-266.0/768.0)*ofGetHeight()+(168.0/768.0)*ofGetHeight()*0.5));

	image.reset(new ofxImageThing);
	shake.reset(new ofxMoveShake);

	image->set("default/image/information.png",(680.0/1024.0)*ofGetWidth(),(268.0/768.0)*ofGetHeight());
	shake->set((266.0/768.0)*ofGetHeight(),1,3,false);
	fade.reset(new ofxFadeEffect);
	fade->set(1,255,0,3);

	dy_image.reset(new ofxDynamicInfo(pos,image,shake,fade));
	dy_info.reset(new ofxDynamicInfo(text_pos,text,shake,fade));
	dy_date.reset(new ofxDynamicInfo(date_pos,text_date,shake,fade));
	dy_author.reset(new ofxDynamicInfo(author_pos,text_author,shake,fade));
	dy_tag.reset(new ofxDynamicInfo(tag_pos,text_tag,shake,fade));

	visible = false;
}


ksInformation::~ksInformation()
{

}

void ksInformation::customDraw()
{

	if (visible)
	{
		dy_image->draw();
		dy_info->draw();
		dy_author->draw();
		dy_date->draw();
		dy_tag->draw();
	}


}

void ksInformation::update()
{
	if (visible)
	{
		dy_image->update();
		dy_info->update();
		dy_author->update();
		dy_date->update();
		dy_tag->update();
	}
}

void ksInformation::setString(string s){
	str = s;

}

void ksInformation::setPos(ofPoint p){
	pos = p;

}

void ksInformation::disableVisible()
{
	visible=false;
}
void ksInformation::visable()
{
	shake.reset(new ofxMoveShake);

	shake->set((266.0/768.0)*ofGetHeight(),1,3,false);
	fade.reset(new ofxFadeEffect);
	fade->set(1,255,0,3);

	dy_image.reset(new ofxDynamicInfo(pos,image,shake,fade));
	dy_info.reset(new ofxDynamicInfo(text_pos,text,shake,fade));
	dy_date.reset(new ofxDynamicInfo(date_pos,text_date,shake,fade));
	dy_author.reset(new ofxDynamicInfo(author_pos,text_author,shake,fade));
	dy_tag.reset(new ofxDynamicInfo(tag_pos,text_tag,shake,fade));

	visible=true;
}
void ksInformation::changeVisible()
{
	visible=!visible;
}

void ksInformation::changeInfo(string info)
{
	str = string(info);

	ofColor textColor(208, 2, 27, 100);
	text.reset(new ofxTextThing);
	text->set(str,"default/font/ksFont.otf",info_size,textColor,false);	

	dy_info.reset(new ofxDynamicInfo(text_pos,text,shake,fade));
}

void ksInformation::changeAuthor(string author)
{
	str_author = string("Auther:\n"+author);

	ofColor dateColor(0, 0, 0, 100);

	text_author.reset(new ofxTextThing);
	text_author->set(str_author,"default/font/ksFont.otf",date_size,dateColor,false);

	dy_author.reset(new ofxDynamicInfo(author_pos,text_author,shake,fade));
}

void ksInformation::changeDate(string date)
{
	str_date = string("Date:\n"+date);

	ofColor dateColor(0, 0, 0, 100);

	text_date.reset(new ofxTextThing);
	text_date->set(str_date,"default/font/ksFont.otf",date_size,dateColor,false);

	dy_date.reset(new ofxDynamicInfo(date_pos,text_date,shake,fade));

}

void ksInformation::changeTag(string tag)
{
	str_tag = string(tag);

	ofColor dateColor(0, 0, 0, 100);

	text_tag.reset(new ofxTextThing);
	text_tag->set(str_tag,"default/font/ksFont.otf",tag_size,ofColor::white,true);	

	dy_tag.reset(new ofxDynamicInfo(tag_pos,text_tag,shake,fade));
}