/**********************************************************************************************//**
 * \姓名 杨雨辰
 * \学号 1030512427
 * \组	 杨雨辰
 *
 * \特色	本程序是根据源程序进行改进，实现了一个以六角星为元素的万花筒，六角星自带渐变色，
 *          有透明度，并且可以自行伸缩。
 * 			
 **************************************************************************************************/

#pragma once
#ifndef KS_YYC12427_H
#define KS_YYC12427_H

#include <ks/base/ksBase.h>

class ksYyc:public ksBase
{
public:
	ksYyc();
	~ksYyc();

	virtual void init();

	virtual void update(float dt);

	virtual void draw(int x, int y, int width, int height);

private:
	ofMesh Mesh;
	ofFbo F;
	float T;
	float ScaleX, ScaleY, Rotation;
	float Speed;
	float a;

	int Mode;

};
#endif

