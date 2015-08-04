/**********************************************************************************************//**
 * \姓名 贾翔宇
 * \学号 1030512321
 * \组	 贾翔宇
 *
 * \特色 通过递归不断生成二叉树并且随时间旋转，
 每个子叶结点为父节点的一半大小，形成向中心坍缩的效果。
 也支持鼠标交互，在点到的位置绘图。
 **************************************************************************************************/
#pragma once
#ifndef KSBITREE_H
#define KSBITREE_H

#include <ks/base/ksBase.h>

class ksBitree:public ksBase
{
public:
	ksBitree();

	~ksBitree();	

	virtual void init();

	virtual void update(float dt);

	virtual void draw(int x, int y, int width, int height);

	virtual void mouseDragged( int x, int y, int button );

	virtual void mousePressed( int x, int y, int button );

	int nowx,nowy;//鼠标坐标
private:
	void PlantingTree(ofBaseDraws *pDraws,int a,int b);//绘制二叉树
};

#endif