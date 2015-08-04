/**********************************************************************************************//**
 * \姓名 黄斌艳
 * \学号 1030512222
 * \组	 单嘉润
 *
 * \特色	实现了一个螺旋状的万花筒，该万花筒的基本实现就是1、贴一个长方形的图，对其进行旋转贴图，旋转一周后，
            缩小成一半再重复旋转。2、实现静态贴图后的整体旋转。3、通过鼠标的点击交互实现增大/减小旋转形成的多边形
			的边数number。则其每次旋转的角度为360/number。设置其初始值为6，最小值为3，最大值为20。
			这个螺旋状的万花筒的效果比较美观，就像在旋转的花朵，我们可以自由的改变花瓣的数量，所以我将其命名为
			Rflower+学号后五位。R是旋转rotate是首字母，flower是万花筒的整体感觉。
 * 			
 **************************************************************************************************/
#ifndef KS_SUPERPOSITION_H
#define KS_SUPERPOSITION_H

#include <ks/base/ksBase.h>

class ksRflower : public ksBase
{
public:
	ksRflower();
	~ksRflower();	

	virtual void init();

	virtual void update(float dt);

	virtual void draw(int x, int y, int width, int height);

	virtual void mousePressed(int x, int y, int button );

private:
	void draw4Leaves(ofBaseDraws *pDraws );
	void draw1Leaf(ofBaseDraws *pDraws );
	int number;
	void press( float s,float w );

private:
	float ScaleX, ScaleY, Rotation;
	float Speed;
	float time;


};

#endif