#include "ofxShake.h"


ofxShake::settings::settings()
{
	dx.setName("dx");
	time.setName("time");
	delay.setName("delay");
	bezierPoint.setName("bezierPoint");
	useBezier.setName("useBezier");
	num.setName("num");
	direction.setName("direction");

	dx = 5.0f;
	time = 2.0f;
	//mode = &ofxTransitions::easeOutExpo;
	delay = 0;
	bezierPoint = 0;
	useBezier = false;
	num=0;
	direction = true;
}

ofXml ofxShake::settings::serialize()
{
	ofXml X;

	ofParameterGroup G;
	G.setName("fxShake_Settings");
	G.add(dx);
	G.add(time);
    //G.add(mode);
	G.add(delay);
	G.add(bezierPoint);
	G.add(useBezier);
	G.add(num);
	G.add(direction);

	X.serialize(G);
	X.reset();
	return X;
}

bool ofxShake::settings::deserialize( ofXml X )
{
	ofParameterGroup G;
	G.setName("fxShake_Settings");

	X.deserialize(G);
	bool bSuc = X.exists(G.getName());
	if(bSuc)
	{
		dx = G.getFloat("to");
		time = G.getFloat("time");
		delay = G.getFloat("delay");
		//mode = G.getFloat("mode");
		bezierPoint = G.getFloat("bezierPoint");
		useBezier = G.getFloat("useBezier");
		num = G.getInt("num");
		direction = G.getBool("direction");
	}

	return bSuc;	
}

ofxShake::ofxShake()
{	
	n_tweener.removeAllTweens();
	_count=0;

	animationType = NODEANIMATION_SHAKE;
}

ofxShake::~ofxShake()
{

}
void ofxShake::set(ofXml X)
{
	Settings.deserialize(X);
}


void ofxShake::set(float to, float time){
	set(to,time,&ofxTransitions::linear,true,0,0,false,NULL);
}

void ofxShake::set(float to, float time,float (ofxTransitions::*ease) (float,float,float,float),bool direction,int count){
	set(to,time,ease,direction,count,0,false,NULL);
}

void ofxShake::set(float dx, float time,float (ofxTransitions::*ease) (float,float,float,float),bool direction,int count, float delay, 
				   float bezierPoint, bool useBezier,void (*callback)(float * arg)){
	Settings.dx = dx;
	Settings.time = time;
	mode = ease;
	Settings.delay = delay;
	Settings.bezierPoint = bezierPoint;
	Settings.useBezier = useBezier;
	Settings.num = count*2;
	Settings.direction = direction;

	if (direction)
	{
		x1 = offSet.x - dx;
		x2 = offSet.x + dx;

		offSet.x=x1;
	}
	else
	{

		y1 = offSet.y - dx;
		y2 = offSet.y + dx;

		offSet.y=y1;
	}
}

void ofxShake::update()
{	
	n_tweener.update();
	if (Settings.direction)
	{   
		if (Settings.num<=0)
		{
			if (x1==offSet.x)
			{
				//n_tweener.removeTween(changePos.x);
				n_tweener.addTween(offSet.x,x2, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
			}
			if (x2==offSet.x)
			{
				//n_tweener.removeTween(changePos.x);
				n_tweener.addTween(offSet.x,x1, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
			}
		}
		else
		{
			if (_count<=Settings.num)
			{
				if (x1==offSet.x)
				{
					//n_tweener.removeTween(changePos.x);
					n_tweener.addTween(offSet.x,x2, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
					_count++;
				}
				if (x2==offSet.x)
				{
					//n_tweener.removeTween(changePos.x);
					n_tweener.addTween(offSet.x,x1, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
					_count++;
				}
			}
			else
				offSet.x = x1+Settings.dx;
		}

	}
		
	else
	{
		if (Settings.num<=0)
		{
			if (y1==offSet.y)
			{
				//n_tweener.removeTween(changePos.x);
				n_tweener.addTween(offSet.y,y2, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
			}
			if (y2==offSet.y)
			{
				//n_tweener.removeTween(changePos.x);
				n_tweener.addTween(offSet.y,y1, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
			}
		}
		else
		{
			if (_count<=Settings.num)
			{
				if (y1==offSet.y)
				{
					//n_tweener.removeTween(changePos.x);
					n_tweener.addTween(offSet.y,y2, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
					_count++;
				}
				if (y2==offSet.y)
				{
					//n_tweener.removeTween(changePos.x);
					n_tweener.addTween(offSet.y,y1, Settings.time,mode, Settings.delay,Settings.bezierPoint,Settings.useBezier);
					_count++;
				}
			}
			else
				offSet.y = 0;
		}
	}
	
}


void ofxShake::copy(ofPtr<ofxShake> pShake)
{
	this->Settings.dx = pShake->Settings.dx;
	this->Settings.time = pShake->Settings.time;
	this->mode = pShake->mode;
	this->Settings.delay = pShake->Settings.delay;
	this->Settings.bezierPoint = pShake->Settings.bezierPoint;
	this->Settings.useBezier = pShake->Settings.useBezier;
	this->Settings.num = pShake->Settings.num;
	this->Settings.direction = pShake->Settings.direction;

	if (this->Settings.direction)
	{
		this->x1 = pShake->x1;
		this->x2 = pShake->x2;
		offSet.x=x1;
	}
	else
	{
		this->y1 = pShake->y1;
		this->y2 = pShake->y2;
		offSet.y=y1;
	}
}

void ofxShake::resetTime()
{

}

void ofxShake::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxShake::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}