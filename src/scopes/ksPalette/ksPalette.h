#pragma once

#ifndef KS_PALETTE_H
#define KS_PALETTE_H

#include <ks/base/ksBase.h>
#include <ks/ui/ksSlider.h>

class ksPalette:public ksBase
{
public:
    ksPalette();
    ~ksPalette();
    
    virtual void init();
    
    virtual void update(float dt);
    
    virtual void draw(int x, int y, int width, int height);
    
    void initGUIValues();
    void initSettings();
    void initGui();
    void CreatFace(int i);
    void initMesh(int i);
    void initPolygon(int i);
    void initLine(int i);
    void initFace(int i);
    void clear();
    
    void copySrcToFbo(float w, float h);
    
    virtual void mouseDragged( int x, int y, int button );
    virtual void mousePressed( int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button );

    void guiEvent();
private:
    
    ksSlider* NPolygonSlider;
    
    vector<ofMesh> mesh;
    vector<ofPoint> PressPoint;
    vector<int> ChooseIndex;
    vector<ofPoint> centerPoints;
    vector<float> RotateDeg;
    vector<float> r;
    vector<float> n;
    int GUIChooseIndex;
    float GUIN;
    
    int Index;
    ofPoint tempPoint;
    ofVec2f NowPos;
    float halfW, halfH;
    bool bpressed;
    bool bdrag;
    ofFbo fbo;
    ofSoundPlayer *sound;
    float spectrum;
};

#endif

