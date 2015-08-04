#include "ofxMoveShake.h"


ofxMoveShake::settings::settings()
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

ofXml ofxMoveShake::settings::serialize()
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

bool ofxMoveShake::settings::deserialize( ofXml X )
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

ofxMoveShake::ofxMoveShake()
{	
	n_tweener.removeAllTweens();
	_count=0;

	animationType = NODEANIMATION_SHAKE;
	bShake = false;
}

ofxMoveShake::~ofxMoveShake()
{

}
void ofxMoveShake::set(ofXml X)
{
	Settings.deserialize(X);
}


void ofxMoveShake::set(float to, float time,int count,bool direction,float (ofxTransitions::*ease) (float,float,float,float)){			  
	Settings.dx = to;
	Settings.time = time;
	mode = ease;
	Settings.num = count*4;
	Settings.direction = direction;

	if (direction)
	{
		x1 = to - 5;
		x2 = to + 5;
		offSet.x=0;
	}
	else
	{

		y1 = to -10;
		y2 = to +10;
		offSet.y=0;
	}
}

void ofxMoveShake::update()
{	
	n_tweener.update();
	if (Settings.direction)
	{   
		if (!bShake)
			{
				n_tweener.update();
				if (offSet.x==0)
				{
					n_tweener.addTween(offSet.x,x1,Settings.time,&ofxTransitions::linear,0,0,false);
				}
				if (offSet.x==x1) {
					bShake=true; 
					//offSet_y = y1;
					n_tweener.removeTween(offSet.x);
				}

			}
			if (bShake)
			{
				n_tweener.update();
				if (_count<Settings.num)
				{
					if (x1==offSet.x)
					{  
						n_tweener.addTween(offSet.x,x2,0.2,mode,0,0,false);
						_count++;
					}
					if (y2==offSet.x)
					{
						n_tweener.addTween(offSet.x,x1,0.2,mode,0,0,false);
						_count++;
					}
				}
				else{
					offSet.x = Settings.dx;
				}
			}
	}
		else
		{
			if (!bShake)
			{
				n_tweener.update();
				if (offSet.y==0)
				{
					n_tweener.addTween(offSet.y,y1,Settings.time,&ofxTransitions::linear,0,0,false);
				}
				if (offSet.y==y1) {
					bShake=true; 
					//offSet_y = y1;
					n_tweener.removeTween(offSet.y);
				}

			}
			if (bShake)
			{
				n_tweener.update();
				if (_count<Settings.num)
				{
					if (y1==offSet.y)
					{  
						n_tweener.addTween(offSet.y,y2,0.2,mode,0,0,false);
						_count++;
					}
					if (y2==offSet.y)
					{
						n_tweener.addTween(offSet.y,y1,0.2,mode,0,0,false);
						_count++;
					}
				}
				else{
					offSet.y = Settings.dx;
				}
			}

	}
}


void ofxMoveShake::copy(ofPtr<ofxMoveShake> pShake)
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

void ofxMoveShake::resetTime()
{

}

void ofxMoveShake::serialize(ofXml& X)
{
	X=Settings.serialize();
}
void ofxMoveShake::deserialize(ofXml& X)
{
	Settings.deserialize(X);
}