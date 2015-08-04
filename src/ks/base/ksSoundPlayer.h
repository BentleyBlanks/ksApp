#pragma once

#include "ofMain.h"

class EventToSound
{

public:
	// [construction]
	EventToSound(); // ����ʱ�Ͷ�ȡ��Ƶ�ļ��б�
	~EventToSound();

	// [function]
	void init();
	void init(string xmlFile);
	void play();
	void play(string eventType);

	void stop();
	void stop(string eventType);
	void setPaused();
	void setHolding();
	void stopHolding();

	void setVolume(float vol);
	void setPan(float pan);

    bool isPlaying(int index);


public:
	// [properities]
	float volume;
	float pan;
	float speed;

	bool isPaused;
	bool isHolding;


private:
	// [data]
	ofXml sfxList;	// �����Ч�ļ���xml�ļ�
	int	sfxNum;
	vector<ofSoundPlayer> SFXs; // ������Ҫ������������Ķ���
	vector<string> sfxNames;
	ofSoundPlayer tempSound;
	string myType;

	// [info]
	string message;
	ofTrueTypeFont TTF;


};