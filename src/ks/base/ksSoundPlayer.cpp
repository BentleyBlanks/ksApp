#pragma once

#include "ksSoundPlayer.h"

EventToSound::EventToSound(){
	// init();
};


EventToSound::~EventToSound(){

};



void EventToSound::init(){
	
	/* ======================================================================================== */
	// ��Ϣ����
	/* ======================================================================================== */
	TTF.loadFont("mono.ttf", 7);
	sfxList.load("sfxList.xml");
	
	if( sfxList.load("sfxList.xml") ){
		message = "sfxList.xml loaded!";
	} else {
		message = "unable to load sfxList.xml , check data/sfx folder";
	}
	cout<<message<<endl;


	/* ======================================================================================== */
	// ���ݲ���
	/* ======================================================================================== */

	isHolding = false;

	sfxList.setTo("LIST");
	cout<<"getNumChildren: "<<sfxList.getNumChildren()<<endl;
	sfxNum = sfxList.getNumChildren();

	vector<string> tempString;

	for (int i = 0; i < sfxNum; i++){
		string valueName = "SOUND[" + ofToString(i) + "]";
		string tempValue;
		tempValue = sfxList.getValue(valueName);
		cout<<"Num "<< i+1 << ": "<<tempValue<<endl;
		tempString.push_back(tempValue);
	}

	for (int i = 0; i < tempString.size(); i++)
	{
		// cout<<tempString[i]<<endl;
		ofSoundPlayer tempSP;
		SFXs.push_back(tempSP);
		SFXs[i].loadSound(tempString[i]);
	}

	if(tempSound.isLoaded()) tempSound.unloadSound();

	cout << "  " << endl<<endl;

};


void EventToSound::init(string xmlFile){

	/* ======================================================================================== */
	// ��Ϣ����
	/* ======================================================================================== */
	// TTF.loadFont("mono.ttf", 7);
	sfxList.load(xmlFile);

	if( sfxList.load(xmlFile) ){
		message = "sfxList.xml loaded!";
	} else {
		message = "unable to load sfxList.xml , check the xml file please.";
	}
	cout<<message<<endl;


	/* ======================================================================================== */
	// ���ݲ���
	/* ======================================================================================== */

	isHolding = false;

	sfxList.setTo("LIST");
	cout<<"getNumChildren: "<<sfxList.getNumChildren()<<endl;
	sfxNum = sfxList.getNumChildren();

	vector<string> tempString;

	for (int i = 0; i < sfxNum; i++){
		string valueName = "SOUND[" + ofToString(i) + "]";
		string tempValue;
		tempValue = sfxList.getValue(valueName);
		cout<<"Num "<< i+1 << ": "<<tempValue<<endl;
		tempString.push_back(tempValue);
	}

	for (int i = 0; i < tempString.size(); i++)
	{
		// cout<<tempString[i]<<endl;
		ofSoundPlayer tempSP;
		SFXs.push_back(tempSP);
		SFXs[i].loadSound(tempString[i]);
	}

	if(tempSound.isLoaded()) tempSound.unloadSound();

	cout << "  " << endl<<endl;
};


/* ======================================================================================== */
// ������Ƶ
/* ======================================================================================== */

void EventToSound::play(){

	int i;
	i = ofRandom(0, 100);
	i = i % sfxNum;	// < �滻����Ƶ������
	cout<<"Random Num: "<<i<<endl<<endl;
	SFXs[i].play();

};


void EventToSound::play(string eventType){

	int i;
	i = ofRandom(0, 100);
	i = i % sfxNum;	// < �滻����Ƶ������

	cout<<"Random Num: "<<i<<endl<<endl;

	if (eventType == "hold"){
		if (isHolding)
		{
			SFXs[i].setLoop(true);
			SFXs[i].play();
		} else
		{
			SFXs[i].stop();
			SFXs[i].setLoop(false);
		}
	} else if (eventType == "music")
	{
		SFXs[i].setMultiPlay(false);
		SFXs[i].setLoop(true);
		SFXs[i].setVolume(0.5);
		SFXs[i].play();
	} else if (eventType == "click")
	{
		SFXs[i].setLoop(false);
		SFXs[i].play();
	} 

};


/* ======================================================================================== */
// �طŲ���
/* ======================================================================================== */

void EventToSound::stop(){

	for (int i = 0; i < sfxNum; i++)
	{
		// cout<<tempString[i]<<endl;
		SFXs[i].stop();
	}

}

void EventToSound::stop(string eventType){
}

void EventToSound::setPaused(){
}


void EventToSound::setHolding(){
	isHolding = true;
}


void EventToSound::stopHolding(){
	isHolding = false;
}


void EventToSound::setVolume(float vol)
{
	for (int i = 0; i < SFXs.size(); i++)
	{
		SFXs[i].setVolume(vol);
		cout<<"vol "<<i<<" : "<<vol<<endl;
	}
}

void EventToSound::setPan(float pan)
{
	for (int i = 0; i < SFXs.size(); i++)
	{
		SFXs[i].setPan(pan);
		cout<<"pan: "<<pan<<endl;
	}
}

bool EventToSound::isPlaying(int index)
{
    if(index < sfxNum)
        return SFXs[index].getIsPlaying();
    else
        return false;
}


