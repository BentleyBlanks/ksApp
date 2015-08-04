/**********************************************************************************************//**
* \姓名 许垚
* \学号 1030512129
* \组长	 单嘉润
*
* \特色  用纹理贴图的方式，将输入的数据源以贴图方式显示出来，由五个交叉的十字拼出图形，
然后设计了GUI界面，显示两个速度，通过拉进度条，可以控制图形的旋转速度。
**************************************************************************************************/

#ifndef KSDRAW12129_H
#define KSDRAW12129_H

#include <ks/base/ksBase.h>


class ksdraw12129 : public ksBase
{
public:
    ksdraw12129();
    
    virtual void init();
    
    virtual void update(float dt);
    
    virtual void draw(int x, int y, int width, int height);
    
private:
    void initSetting(); 
    void Speed1Changed(float& Speed1);
    void Speed2Changed(float& Speed2);
    //void guiEvent(ofxUIEventArgs &E);
    ofParameterGroup& genParamGroup();
    
private:
    // setting
    // 关于显示效果的一系列参数ofParameter
    ofParameter<float> Speed1;
    ofParameter<float> Speed2;
    
    ofParameterGroup Group; 
    
    ksSlider *speed1Slider, *speed2Slider;
private:
    ofMesh mesh;
    ofFbo F;
    float ctime;
    
    void drawcross();
    void draw5cross();
};

#endif

