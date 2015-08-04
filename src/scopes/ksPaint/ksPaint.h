#pragma once

#ifndef KS_PAINT_H
#define KS_PAINT_H

#include <ks/base/ksBase.h>
#include <ks/ui/ksSlider.h>

class ksPaint:public ksBase
{
public:
    ksPaint();
    ~ksPaint();
    
    virtual void init();
    
    virtual void update(float dt);
    
    virtual void draw(int x, int y, int width, int height);
    
    virtual void mouseDragged( int x, int y, int button );
    virtual void mousePressed( int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button );
    
    void initPaint1();
    void drawPaint1(float dY);
    void initMesh(ofPoint p1,ofPoint p2,ofPoint p3);
    void copySrcToFbo(float w, float h);
    
private:
    float med_mouseX;
    float med_mouseY;
    float old_mouseX;
    float old_mouseY;
    float red;
    Boolean is_pressed;
    int mouseX,mouseY;
    int pmouseX,pmouseY;
    ofMesh _myMesh[10000];
    ofFbo fbo;
    ofTexture T ;
    int cout;
    
    float ppmouseX, ppmouseY;

    void guiEvent();
    
    void initSetting();
    
    ofPoint getCenterOfScreen();
    
    ofParameterGroup Group;
    
    bool paint1;
    bool paint2;
    bool clear;
    int GUIShapeOfMesh;
};

#endif

