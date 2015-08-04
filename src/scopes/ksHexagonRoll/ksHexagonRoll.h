#pragma once
#ifndef KSksHexagonRoll_H
#define KSksHexagonRoll_H

#include <ks/base/ksBase.h>

class ksHexagonRoll:public ksBase
{
public:
	ksHexagonRoll();
    
	~ksHexagonRoll();

	virtual void init();

	virtual void update(float dt);

	virtual void draw(int x, int y, int width, int height);

private:

	void popMSV();
	void pushMSV();
	void updateIrolat();
	float Roloat;
	ofImage Irolats;
	void setupIrolat();
private:

	ofFbo F;
	float s;
	ofVec2f Ctr;
	ofMesh Hexagon;
	float ScaleX, ScaleY, Rotation;
	float Speed;
	ofVec2f c01;
	ofVec2f c11;
	ofVec2f c10;
	ofVec2f c050;
	ofPoint certain;
	ofFbo Frolat;
	ofImage Irolat;


};

#endif