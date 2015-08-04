/**********************************************************************************************//**
 * \姓名 刘道达
 * \学号 1030512305
 * \组	 李燊
 *
 * \特色 
 **************************************************************************************************/
#pragma  once
#ifndef KSLIUDAODA12305_H
#define KSLIUDAODA12305_H

#include <ks/base/ksBase.h>

class ksLiudaoda:public ksBase
{
public:
	ksLiudaoda();

	~ksLiudaoda();

	virtual void init();

	virtual void update(float dt);

	virtual void draw(int x, int y, int width, int height);

	virtual void mouseDragged( int x, int y, int button );

private:	
	ofEasyCam cam;
			
	ofFbo F1;
			
	ofBoxPrimitive box;

	float mouseX;

	float mouseY;
};
#endif
