#ifndef KS_SCROLLABLE_CANVAS
#define KS_SCROLLABLE_CANVAS

#include <ofMain.h>
#include <ks/ui/ksSlider.h>

struct ksList
{
    ofFbo nameFbo;
    string name;
    ofRectangle *aabb;
};

class ksScrollableCanvas
{
public:
    ksScrollableCanvas();
    ~ksScrollableCanvas();
    
    void init(int x, int y, int width, int height, int elementX, int elementHeight, int fontSize);
    
    void addButton(string name);
    
    ksSlider* addSlider(string _name, float _min, float _max, float _value);
    
    ksSlider* addSlider(string _name, float _min, float _max, float *_value);
    
    void update();
    
    void draw();
    
    // 抑制y方向上的走向
    void dampenY();
    
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
    ofTrueTypeFont scopes;
    
    ofEvent<ofEventArgs> newGUIEvent;
    
    vector<ksList*> ksLists;
    vector<ksSlider_<float>*> ksSliderLists;
    
    ofRectangle rect, stickRect;
    
    ofFbo button, canvas, listCanvas;
    int buttonY;
    
    int elementHeight;
    int elementX;
    int fontSize;
    int windowWidth, windowHeight;
    bool bInited, bVisible;
    
    // scrolling
    bool bHit, bIsScrolling;
    bool nearTop, nearBot, nearRight, nearLeft;
    float stickyDistance;
    // 阻尼
    float damping;
    
    // 滑动
    ofVec2f position;
    ofVec2f previousPosition;
    ofVec2f velocity, acc;
};

#endif
