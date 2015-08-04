//#pragma once
#ifndef KS_QUNIMA_H
#define KS_QUNIMA_H

#include <ks/base/ksBase.h>
#include <ks/ui/ksSlider.h>

class EventToSound;
class ksShaderPalette : public ksBase
{
public:
    ksShaderPalette();
    ~ksShaderPalette();
    
    virtual void init();
    
    virtual void update(float dt);
    
    virtual void draw(int x, int y, int width, int height);
    
    void initGUIValues();
    void initSettings();
    void updateGUIValues();
    void setMesh(int i);
    
    void initMesh(int i);
    void initTriangleMesh(int i);
    void initSquareMesh(int i);
    void initCircleMesh(int i);
    void initOriginMesh(int i);
    void clear();
    
    void copySrcToFbo(float w, float h);
    void addIndicesToMesh(int i, int triangleNum);
    void ofxPushMSV();
    void ofxPopMSV();
    
    virtual void mouseDragged( int x, int y, int button );
    virtual void mousePressed( int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button );
    
    void guiEvent();
    
    //#ifdef KS_DEBUG
    //    virtual ofPtr<ofxPanel> gui( float x, float y, float w, float h );
    //#else
    //    virtual ofPtr<ofxUICanvas> gui( float x, float y, float w, float h );
    //#endif
    //    virtual void guiDel();
    
    //private:
    //    void guiEvent(ofxUIEventArgs &E);
    
private:
    
    //#ifdef KS_DEBUG
    //    ofPtr<ofxPanel> G;
    //#else
    //    ofPtr<ofxUICanvas> G;
    //#endif
    //
    //settings
    vector<float> Radius;
    vector<float> RotateDeg;
    vector<int> SegmentNum;
    vector<int> ShapeOfMesh;
    vector<int> shaderIndex;
    vector<float> parameterA;
    vector<float> parameterB;
    
    
    //guiValue
    ksSlider *radiusSlider;
    ksSlider *rotateDegSlider;
    ksSlider *segmentNumSlider;
    ksSlider *parameterASlider;
    ksSlider *parameterBSlider;
    ksSlider *speedSlider;
    
    float GUIRadius;
    float GUIRotateDeg;
    int GUISegmentNum;
    int GUIShapeOfMesh;
    int GUIshaderIndex;
    float GUIparameterA;
    float GUIparameterB;
    
    vector<ofMesh> mesh;
    vector<ofPoint> centerPoints;
    
    ofShader *shader;
    // fboAlpha专用于渐隐
    ofFbo fbo, fboAlpha;
    int index;
    
    bool useTime, doRotate,isDrawing;
    bool isBrush, isClick;
    float speed, deltaDeg;
    
    ofSoundPlayer *sound;
    //EventToSound *sound;
    
    bool isPlaySound;
    float spectrum;
    
    ofPoint tempPoint;
    
    
};


#endif

