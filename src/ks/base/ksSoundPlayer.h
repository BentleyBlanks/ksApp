#pragma once

#include "ofMain.h"

class EventToSound
{

public:
	// [construction]
	EventToSound(); // 构造时就读取音频文件列表
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
	ofXml sfxList;	// 存放音效文件的xml文件
	int	sfxNum;
	vector<ofSoundPlayer> SFXs; // 可能需要多个播放声音的对象
	vector<string> sfxNames;
	ofSoundPlayer tempSound;
	string myType;

	// [info]
	string message;
	ofTrueTypeFont TTF;


};