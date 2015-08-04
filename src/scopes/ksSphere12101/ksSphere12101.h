/**********************************************************************************************//**
                                                                                                 * \姓名 崔灿
                                                                                                 * \学号 1030512101
                                                                                                 * \组	 （单嘉润）
                                                                                                 *
                                                                                                 * \特色	实现了一个球形状的3D万花筒，该球形万花筒上的贴图为六角星拼贴而成，可以改变球的半径、
                                                                                                 速度，可以自由旋转和改变花样。
                                                                                                 **************************************************************************************************/

#ifndef KSSPHERE12101_H
#define KSSPHERE12101_H


#include <ks/base/ksBase.h>


class ksSphere12101 : public ksBase
{
public:
    //构造和析构函数
    ksSphere12101();
    ~ksSphere12101();
    
    
    virtual void init();
    virtual void draw(int x, int y, int width, int height);
    virtual void update(float dt);
    
private:
    float X,Y,Z;	//绕X,Y,Z,轴旋转的角度
    ofMesh mesh;
    ofFbo fbo;
    ofFbo fbo2;
    ofSpherePrimitive sphere;
    
    void setupMesh();		//初始化mesh
    void initSphere();		//初始化球体
    void initComponents();	//初始化控件
    
    //GUI Parameter
    ofParameterGroup& genParamGroup();
    ofParameter<float> Radius;		//球的半径
    ofParameter<float> Speed;		//旋转速度
    ofParameter<float> WScale;		//mesh宽度的缩放
    ofParameter<float> HScale;		//mesh高度的缩放
    ofParameter<float> RotateX;		//绕X轴旋转角度
    ofParameter<float> RotateY;		//绕Y轴旋转角度
    ofParameter<float> RotateZ;		//绕Z轴旋转角度
    
    ksSlider *RadiusSlider, *SpeedSlider, *WScaleSlider, *HScaleSlider, *RotateXSlider, *RotateYSlider, *RotateZSlider;
    
    //GUI改变对应事件
    void RadiusChanged(float& radius);
    void SpeedChanged(float& speed);
    void WScaleChanged(float& WScale);
    void HScaleChanged(float& WScale);
    void RotateXchanged(float& RotateX);
    void RotateYchanged(float& RotateY);
    void RotateZchanged(float& RotateZ);
    
    //void guiEvent(ofxUIEventArgs &E);
    // gui components
    ofParameterGroup Group;
    
};

#endif
