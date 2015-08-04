#ifndef KSAPP_H
#define KSAPP_H

#include <ofMain.h>
// gui
#include <ofxUI.h>

class ofxUICanvas;
class ofFbo;
class ksBase;
class ksController;
class ksScrollableCanvas;
class ksIconButton;

class ksApp
{
public:
    ksApp();
    
    // 全局内存分配 消息分派
    void init();
    
    void update();
    
    void draw();
    
    // 添加外部实例化的ks对象 底层框架不负责维护这一部分内存管理
    //void add(ksBase* object);
    
    // 设定列表中背选中的对象
    void setSelected(int index);
    
    // --!设计的不太妥当
    static int getWidth();
    
    static int getHeight();
    
    static int getContentWidth();
    
    static int getContentHeight();
    
private:
    // 初始化指定目录下所有万花筒
    void initKsLists();
    
    // 只会为当前选定的对象分发消息
    void windowResized(ofResizeEventArgs &resize);
    
    void keyPressed(ofKeyEventArgs &key);
    
    void keyReleased(ofKeyEventArgs &key);
    
    void mouseMoved(ofMouseEventArgs &mouse);
    
    void mouseDragged(ofMouseEventArgs &mouse);
    
    void mousePressed(ofMouseEventArgs &mouse);
    
    void mouseReleased(ofMouseEventArgs &mouse);
    
    void initGui();
    
    // 响应系统gui事件
    void guiEvent();
    
    ofFbo *canvas, *content;
    
    // ksApp所在范围
    static int width, height, contentWidth, contentHeight;
    
    bool bInitialized;
    
    ksController *controller;
    
    // gui所需组件
    //ofxUICanvas *gui;
    ofTrueTypeFont title;
    ofFbo icon, spacer, mask;
    ksIconButton *switchButton, *informationButton, *settingsButton;
    ksScrollableCanvas *gui;
};

#endif 
