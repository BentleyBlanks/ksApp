#ifndef KS_ICONBUTTON_H
#define KS_ICONBUTTON_H

#include <ofMain.h>

class ksIconButton
{
public:
    ksIconButton();
    
    // aabb初始化
    void init(string name, ofRectangle aabb);
    
    void setMaterial(string iconPath, string iconPressedPath, string fontPath, int fontSize);
    
    void setFontColor(ofColor normal, ofColor pressed);
    
    void update();
    
    void draw();
    
    void setVisible(bool visible);
    
    bool isVisible();
    
protected:
#ifdef KS_TARGET_TOUCH
    virtual void onTouchDown(ofTouchEventArgs &data);
    virtual void onTouchMoved(ofTouchEventArgs &data);
    virtual void onTouchUp(ofTouchEventArgs &data);
    virtual void onTouchDoubleTap(ofTouchEventArgs &data);
    virtual void onTouchCancelled(ofTouchEventArgs &data);
    
    virtual void touchDown(float x, float y, int id);
    virtual void touchMoved(float x, float y, int id);
    virtual void touchUp(float x, float y, int id);
    virtual void touchCancelled(float x, float y, int id);
#endif
    virtual void onMousePressed(ofMouseEventArgs& data);
    virtual void onMouseDragged(ofMouseEventArgs& data);
    virtual void onMouseReleased(ofMouseEventArgs& data);
    virtual void onMouseMoved(ofMouseEventArgs& data);
    
    virtual void mouseDragged(int x, int y, int button);
    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void mouseMoved(int x, int y );
    
private:
    ofEvent<ofEventArgs> newGUIEvent;
    
    ofRectangle aabb;
    
    string name;
    ofFbo namePressedFbo, nameNormalFbo;
    int fontSize;
    
    // render
    ofFbo icon, iconPressed;
    ofTrueTypeFont buttonFont;
    
    ofColor normalColor, pressedColor;
    
    bool bIsPressed, bVisible;
};

#endif
