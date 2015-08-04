#include "ksLiudaoda.h"

#include <ks/base/ksResource.h>

ksRegisterClass(ksLiudaoda);

ksLiudaoda::ksLiudaoda()
{
}

ksLiudaoda::~ksLiudaoda()
{

}

void ksLiudaoda::init()
{
    ofDisableArbTex();
	
    box.set(200);
}

void ksLiudaoda::update( float dt )
{

}

void ksLiudaoda::draw( int x, int y, int width, int height )
{
	ofBaseDraws *pDraw = ksResource::getResource();

    if(!F1.isAllocated())
        F1.allocate(pDraw->getWidth(), pDraw->getHeight(), GL_RGBA);
	
    F1.begin();
	ofClear(0,0,0,0);
	pDraw->draw(0,0,F1.getWidth(),F1.getHeight());
	F1.end();

	cam.begin();
	ofTexture T1 = F1.getTextureReference(); 
	cam.end();
    
    ofPushStyle();
	T1.bind();
	for (int i=-2;i<3;i++){
		for(int j=-2;j<3;j++){
			for(int k=-2;k<3;k++){
				box.setPosition(width/2+i*(mouseX-width/2),j*(mouseY-height/2)+height/2, (mouseY-height/2)*(mouseX-width/2)/200*k);
				box.draw();
				ofSetColor(255,255,255);
			}
		}
	}
    
    
    T1.unbind();
    ofPopStyle();
}

void ksLiudaoda::mouseDragged( int x, int y, int button )
{
	mouseX = x;
	mouseY = y;
}


