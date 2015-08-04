/**********************************************************************************************//**
 * \姓名 郭婉茹
 * \学号 1030512220
 * \组	 盛凯
 *
 * \特色	将数据源做成八叶风车的造型，以八叶风车为基本单元，自主实现有规律的源源不断，生生不息
            的转动和缩放。同时，它支持鼠标交互。点击屏幕左半边，可使风车的数目减少，点击屏幕右边，
			风车数目增加；于此同时，点击屏幕上方，风车可随机出现，点击屏幕下方，可关闭上述随机效果。
 **************************************************************************************************/

#ifndef KS_SUPERPOSITION_H
#define KS_SUPERPOSITION_H

#include <ks/base/ksBase.h>

class ksArovane : public ksBase
{
public:
	ksArovane();
	~ksArovane();

	virtual void init();

	virtual void update(float dt);

	virtual void draw(int x, int y, int width, int height);

	virtual void mousePressed( int x, int y, int button );
private:
	ofMesh HexagonMesh;
	ofFbo F;
	float Rotation,ScalationX,ScalationY;
	float Speed;
	float TranslationX,TranslationY;
	int   number;
	bool  bRandom;
	void My8roll();
	float time;


private:



};

#endif