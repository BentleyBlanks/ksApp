#include <ks/ui/ksSlider.h>
#include <ks/utility/ksLog.h>
#include <ks/ksApp.h>
#include <ks/ui/ksMessageQueue.h>

template<typename T>
ksSlider_<T>::ksSlider_(string _name, T _min, T _max, T _value, float x, float y, float width, float height)
{
#ifdef KS_TARGET_TOUCH
    // 事件监听
    ofAddListener(ofEvents().touchCancelled, this, &ksSlider_::onTouchCancelled);
    ofAddListener(ofEvents().touchDoubleTap, this, &ksSlider_::onTouchDoubleTap);
    ofAddListener(ofEvents().touchDown, this, &ksSlider_::onTouchDown);
    ofAddListener(ofEvents().touchMoved, this, &ksSlider_::onTouchMoved);
    ofAddListener(ofEvents().touchUp, this, &ksSlider_::onTouchUp);
#endif
    // 事件监听
    ofAddListener(ofEvents().mouseReleased, this, &ksSlider_::onMouseReleased);
    ofAddListener(ofEvents().mousePressed, this, &ksSlider_::onMousePressed);
    ofAddListener(ofEvents().mouseMoved, this, &ksSlider_::onMouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &ksSlider_::onMouseDragged);
    //#endif
    
    init(_name, _min, _max, &_value, x, y, width, height);
}

template<typename T>
ksSlider_<T>::ksSlider_(string _name, T _min, T _max, T *_value, float x, float y, float width, float height)
{
#ifdef KS_TARGET_TOUCH
    // 事件监听
    ofAddListener(ofEvents().touchCancelled, this, &ksSlider_::onTouchCancelled);
    ofAddListener(ofEvents().touchDoubleTap, this, &ksSlider_::onTouchDoubleTap);
    ofAddListener(ofEvents().touchDown, this, &ksSlider_::onTouchDown);
    ofAddListener(ofEvents().touchMoved, this, &ksSlider_::onTouchMoved);
    ofAddListener(ofEvents().touchUp, this, &ksSlider_::onTouchUp);
#endif
    // 事件监听
    ofAddListener(ofEvents().mouseReleased, this, &ksSlider_::onMouseReleased);
    ofAddListener(ofEvents().mousePressed, this, &ksSlider_::onMousePressed);
    ofAddListener(ofEvents().mouseMoved, this, &ksSlider_::onMouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &ksSlider_::onMouseDragged);
    //#endif
    
    init(_name, _min, _max, _value, x, y, width, height);
}

template<typename T>
void ksSlider_<T>::init(string _name, T _min, T _max, T *_value, float x, float y, float width, float height)
{
    bHit = false;
    bVisible = true;
    
    this->name = _name;
    this->min = _min;
    this->max = _max;
    this->value = *_value;
    this->__T_T___offsetY = 0;
    
    aabb.set(x, y, width, height);
}

template<typename T>
void ksSlider_<T>::setMaterial(string sliderDownPath, string sliderUpPath, string fontPath, int fontSize)
{
    //    ofImage sliderDownTexture(sliderDownPath);
    //    sliderDown.allocate(sliderDownTexture.getWidth(), sliderDownTexture.getHeight());
    //    sliderDown.begin();
    //    sliderDownTexture.draw(0, 0);
    //    sliderDown.end();
    //
    //    ofImage sliderUpTexture(sliderUpPath);
    //    sliderUp.allocate(sliderUpTexture.getWidth(), sliderUpTexture.getHeight());
    //    sliderUp.begin();
    //    sliderUpTexture.draw(0, 0);
    //    sliderUp.end();
    
    sliderDown.loadImage(sliderDownPath);
    sliderUp.loadImage(sliderUpPath);
    
    sliderFont.loadFont(fontPath, fontSize);
    
    aabbDown.set(aabb.x + aabb.width * (58 / 395.0),
                 aabb.y + aabb.height * (20 / 40.0),
                 sliderDown.getWidth(),
                 sliderDown.getHeight());
    
    aabbUp.set(aabb.x + aabb.width * (58 / 395.0),
               aabb.y + aabb.height * (20 / 40.0),
               sliderUp.getWidth(),
               sliderUp.getHeight());
}

template<typename T>
void ksSlider_<T>::setValue(T _value)
{
    value = _value;
}

template<typename T>
T ksSlider_<T>::getValue()
{
    return value;
}

template<typename T>
T* ksSlider_<T>::getValuePtr()
{
    return &value;
}

template<typename T>
T ksSlider_<T>::getIncrement()
{
    return increment;
}

template<typename T>
void ksSlider_<T>::setIncrement(T _increment)
{
    increment = _increment;
}

template<typename T>
void ksSlider_<T>::update()
{
    
}

template<typename T>
void ksSlider_<T>::draw(int x, int y)
{
    if(!bVisible)
        return;
    
    //__T_T___offsetY = y;
    
    sliderFont.drawString(name + ": " + ofToString(value),
                          aabb.x + aabb.width * (58 / 395.0),
                          aabb.y + y + aabb.height * (36 / 80.0));
    
    sliderDown.draw(aabbDown.x, aabb.y + y + aabb.height * (50 / 80.0), (ksApp::getWidth() / 2048.0) * aabbDown.width, aabbDown.height);
    sliderUp.drawSubsection(aabbUp.x, aabb.y + y + aabb.height * (50 / 80.0), (ksApp::getWidth() / 2048.0) * ((value - min) / (max - min)) * aabbUp.width, aabbUp.height, 0, 0);
    
    //ofPushStyle();
    //ofNoFill();
    //ofSetColor(200);
    //ofRect(aabb.x, aabb.y + y, aabb.width, aabb.height);
    //ofRect(aabbUp);
    //ofRect(aabbDown);
    //ofPopStyle();
}

template<typename T>
void ksSlider_<T>::input(float x, float y)
{
    float percent = ofClamp((x - aabbUp.x) / aabbUp.width, 0.0, 1.0);
    
    value = min + (max - min) * percent;
}

template<typename T>
ofRectangle& ksSlider_<T>::getAABB()
{
    return aabb;
}

#ifdef KS_TARGET_TOUCH
template<typename T>
void ksSlider_<T>::onTouchDown(ofTouchEventArgs &data)
{
    
}

template<typename T>
void ksSlider_<T>::onTouchMoved(ofTouchEventArgs &data)
{
    
}

template<typename T>
void ksSlider_<T>::onTouchUp(ofTouchEventArgs &data)
{
    
}

template<typename T>
void ksSlider_<T>::onTouchDoubleTap(ofTouchEventArgs &data)
{
    
}

template<typename T>
void ksSlider_<T>::onTouchCancelled(ofTouchEventArgs &data)
{
    
}

template<typename T>
void ksSlider_<T>::touchDown(float x, float y, int id)
{
    
}

template<typename T>
void ksSlider_<T>::touchMoved(float x, float y, int id)
{
    
}

template<typename T>
void ksSlider_<T>::touchUp(float x, float y, int id)
{
    
}

template<typename T>
void ksSlider_<T>::touchCancelled(float x, float y, int id)
{
    
}

template<typename T>
void ksSlider_<T>::touchDoubleTap(float x, float y, int id)
{
    
}

#endif

template<typename T>
void ksSlider_<T>::mouseDragged(int x, int y, int button)
{
    if(bHit)
    {
        // --!不要问我为什么要减去两个T_T我也不知道 反正一定要减去stickRect就对了
        if(aabb.inside(x, y - __T_T___offsetY - __T_T___stickRectY))
        {
            input(x, y);
            
            bHit = true;
            
            ksMessageQueue::messages.push_back(name);
        }
    }
}

template<typename T>
void ksSlider_<T>::mousePressed(int x, int y, int button)
{
    if(aabb.inside(x, y - __T_T___offsetY - __T_T___stickRectY))
    {
        input(x, y);
        
        bHit = true;
        
        ksLog("press\n");
    }
}

template<typename T>
void ksSlider_<T>::mouseReleased(int x, int y, int button)
{
    if(bHit)
    {
        if(aabb.inside(x, y - __T_T___offsetY - __T_T___stickRectY))
        {
            bHit = false;
            ksLog("release\n");
        }
    }
}

template<typename T>
void ksSlider_<T>::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
template<typename T>
void ksSlider_<T>::onMousePressed(ofMouseEventArgs& data)
{
    mousePressed(data.x, data.y, data.button);
}

template<typename T>
void ksSlider_<T>::onMouseDragged(ofMouseEventArgs& data)
{
    mouseDragged(data.x, data.y, data.button);
}

template<typename T>
void ksSlider_<T>::onMouseReleased(ofMouseEventArgs& data)
{
    mouseReleased(data.x, data.y, data.button);
}

template<typename T>
void ksSlider_<T>::onMouseMoved(ofMouseEventArgs& data)
{
    mouseMoved(data.x, data.y);
}

//#endif

template class ksSlider_<int>;
template class ksSlider_<float>;
template class ksSlider_<double>;