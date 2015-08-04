#include "ksShake.h"

ksShake::ksShake()
{	
	n_tweener.removeAllTweens();
	_count=0;
	offSet_y = 0;
	able = false;
	bShake = false;
	creatTime = 0;
}

ksShake::~ksShake()
{

}

void ksShake::set(float to, float time,int count, float (ofxTransitions::*ease) (float,float,float,float)){
	this->dy = to;
	this->time = time;
	mode = ease;
	this->num = count*2;

	y1 = dy-5;
	y2 = dy+5;

	offSet_y = 0;
}

void ksShake::update()
{
	
	if (able)
	{ 
		if (!bShake)
		{
			n_tweener.update();
			if (offSet_y==0)
			{
				n_tweener.addTween(offSet_y,y1,time,&ofxTransitions::linear,0,0,false);
			}
			if (offSet_y==y1) {
				bShake=true; 
				//offSet_y = y1;
				n_tweener.removeTween(offSet_y);
			}
			
		}
		if (bShake)
		{
			n_tweener.update();
			if (_count<num)
			{
				if (y1==offSet_y)
				{  
					n_tweener.addTween(offSet_y,y2,0.2,mode,0,0,false);
					_count++;
				}
				if (y2==offSet_y)
				{
					n_tweener.addTween(offSet_y,y1,0.2,mode,0,0,false);
					_count++;
				}
			}
			else{
				offSet_y = dy;
			}
		}
	}
}


void ksShake::resetTime()
{

}

float ksShake::getOffset()
{
	if (able)
	{   
		update();
		return this->offSet_y;
	}
	else
	{
		return 0;
	}
	
}

void ksShake::enable()
{
	this->able = true;
}
void ksShake::disable()
{
	this->able = false;
}