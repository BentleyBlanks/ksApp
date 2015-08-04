#pragma once
#ifndef KSTZHROLL_H
#define KSTZHROLL_H

#include <ks/base/ksBase.h>

class kstzhroll:public ksBase
{
	public:
		kstzhroll();
		~kstzhroll();

		virtual void init();

		virtual void update(float dt);

		virtual void draw(int x, int y, int width, int height);


	private:
	
		void popMSV();
		void pushMSV();

	private:
		
		ofFbo F;
		float s;
		ofVec2f Ctr;
		ofMesh Hexagon;
		double Roloate;


	};



#endif