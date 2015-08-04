/**********************************************************************************************//**
 * \姓名 杨苏
 * \学号 1030512211
 * \组B	 （杨苏）
 *
 * \特色 
    运用了贴图和GUI控件，实现了一个多个矩形螺旋状旋转的万花筒。可以显示图片，摄像头或者视频。
    当调节滚动条的时候，可以改变旋转的速度，矩形的个数，位置和尺寸，可以停止旋转和改变方向。
	作为装饰，在屏幕中央的四周加入了数个三角面片环绕着转动

 **************************************************************************************************/


#pragma once
#ifndef KSYANGSU_H
#define KSYANGSU_H

#include <ks/base/ksBase.h>

class ksYangsu:public ksBase{
	public:
		ksYangsu();
		~ksYangsu();

		virtual void init();

		virtual void update(float dt);

		virtual void draw(int x, int y, int width, int height);

	private:
		void huanrao(ofBaseDraws *pDraws);
		void kuosan(ofBaseDraws *pDraws );

		ofMesh ysMesh;
		ofFbo F;
		float T;
		float m;

		ofBaseDraws* resources;
		// gui
		// spirals
		ksSlider *speed, *posx, *posy, *numArmsSlider, *length, *width, *number, *direction;
		ksSlider *mode1, *mode2;
};



#endif

