#include "ksBitree.h"
#include <ks/base/ksResource.h>

ksRegisterClass(ksBitree);

ksBitree::ksBitree()
{

}

//构造函数
ksBitree::~ksBitree()
{

}
//析构函数

void ksBitree::init()
{

}

void ksBitree::update( float dt )
{

}

void ksBitree::draw(int x, int y, int width, int height)
{
	ofBaseDraws* pDrawSrc = ksResource::getResource();

	ofPushMatrix();
	ofTranslate(width/2,height/2);
	ofScale(1.5f,-1.5f,1.0f);
	float scaleX,scaleY,scaleZ;
	scaleX = width/3;
	scaleY = height/3;
	scaleZ = 1.0f;
	ofScale(scaleX,scaleY,scaleZ);	
	int mx=2;int my=-2;//父结点位置
	for(int i=0;i<10;i++)//
	{		
		ofScale(0.5f,0.5f,1.0f);//每片子叶为父结点大小一半
		PlantingTree(pDrawSrc,mx,my);//自动画二叉树
		mx-=2;
		my-=2;//子叶（新的父结点）位置
		PlantingTree(pDrawSrc,nowx,nowy);//鼠标点击画二叉树
		nowx-=2;
		nowy-=2;
	}	

	ofPopMatrix();
}


void ksBitree::PlantingTree(ofBaseDraws *pDraws,int a,int b ) 
{   
	ofRotate(ofGetElapsedTimef()*10000);//随时间旋转
	
	pDraws->draw(a,b,10,-10);//画父结点
	pDraws->draw(a-20,b-20,10,-10);//左子树左结点
	pDraws->draw(a+20,b-20,10,-10);//左子树右结点
	int c=a+20;int d=b-20;//右子树
	pDraws->draw(c-20,d-20,10,-10);//右子树左节点
	pDraws->draw(c+20,d-20,10,-10);//右子树右结点
	
}

//实现鼠标交互
void ksBitree::mouseDragged( int x, int y, int button )
{

}

void ksBitree::mousePressed( int x, int y, int button )
{
	nowx=x;
	nowy=y;
}
