#include <ks/ui/ksScrollableCanvas.h>
#include <ks/ksApp.h>
#include <ks/ui/ksMessageQueue.h>

ksScrollableCanvas::ksScrollableCanvas()
{
    bInited = false;
    bHit = false;
    bIsScrolling = false;
    bVisible = true;
}

ksScrollableCanvas::~ksScrollableCanvas()
{
    
}

void ksScrollableCanvas::init(int x, int y, int width, int height, int elementX, int elementHeight, int fontSize)
{
    bInited = true;
    
#ifdef KS_TOUCH
    // 事件监听
    //ofAddListener(ofEvents().touchCancelled, this, &ksScrollableCanvas::onTouchCancelled);
    //ofAddListener(ofEvents().touchDoubleTap, this, &ksScrollableCanvas::onTouchDoubleTap);
    ofAddListener(ofEvents().touchDown, this, &ksScrollableCanvas::onTouchDown);
    ofAddListener(ofEvents().touchMoved, this, &ksScrollableCanvas::onTouchMoved);
    ofAddListener(ofEvents().touchUp, this, &ksScrollableCanvas::onTouchUp);
#endif
    // 事件监听
    ofAddListener(ofEvents().mouseReleased, this, &ksScrollableCanvas::onMouseReleased);
    ofAddListener(ofEvents().mousePressed, this, &ksScrollableCanvas::onMousePressed);
    ofAddListener(ofEvents().mouseMoved, this, &ksScrollableCanvas::onMouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &ksScrollableCanvas::onMouseDragged);
    //#endif
    
    scopes.loadFont("default/font/ksFont.otf", fontSize);
    
    // 按钮素材
    ofImage *buttonTexture = new ofImage("default/image/button.png");
    if(!button.isAllocated())
        button.allocate(buttonTexture->getWidth(), buttonTexture->getHeight());
    button.begin();
    buttonTexture->draw(0, 0);
    button.end();
    
    rect.set(x, y, width, height);
    stickRect.set(x, y, width, height);
    
    if(!canvas.isAllocated())
        canvas.allocate(stickRect.width, stickRect.height);
    
    windowHeight = ofGetHeight();
    windowWidth = ofGetWidth();
    
    this->elementHeight = elementHeight;
    this->elementX = elementX;
    this->fontSize = fontSize;
    this->stickyDistance = 32;
    this->damping = 0.75;
    this->acc.set(0, 0);
    
    ksLists.clear();
    ksSliderLists.clear();
}

void ksScrollableCanvas::addButton(string name)
{
    ofRectangle *temp = new ofRectangle();
    temp->set(rect.x, (ksLists.size() + ksSliderLists.size()) * elementHeight, rect.width, elementHeight);
    
    ksList *list = new ksList();
    list->aabb = temp;
    list->name = name;
    
    ksLists.push_back(list);
    
    if(ksLists.size() == 1)
        buttonY = ksLists[0]->aabb->y;
    
    // 向缓存中渲染
    //    list->nameFbo.allocate((ksApp::getWidth() / 1024.0) * 198, fontSize * 3);
    //    list->nameFbo.begin();
    //    scopes.drawString(name, 0, fontSize / 2.0 + list->aabb->height / 2.0 );
    //    list->nameFbo.end();
}

ksSlider* ksScrollableCanvas::addSlider(string _name, float _min, float _max, float _value)
{
    ksSlider *slider = new ksSlider(_name, _min, _max, _value,
                                    stickRect.x, (ksLists.size() + ksSliderLists.size()) * elementHeight,
                                    stickRect.width, elementHeight);
    
    slider->setMaterial("default/image/sliderDown.png", "default/image/sliderUp.png", "default/font/ksFont.otf", fontSize);
    ksSliderLists.push_back(slider);
    // --!无奈之举…………………………
    slider->__T_T___stickRectY = stickRect.y;
    
    return slider;
}

ksSlider* ksScrollableCanvas::addSlider(string _name, float _min, float _max, float *_value)
{
    ksSlider *slider = new ksSlider(_name, _min, _max, _value,
                                    stickRect.x, (ksLists.size() + ksSliderLists.size()) * elementHeight,
                                    stickRect.width, elementHeight);
    
    slider->setMaterial("default/image/sliderDown.png", "default/image/sliderUp.png", "default/font/ksFont.otf", fontSize);
    ksSliderLists.push_back(slider);
    // --!无奈之举…………………………
    slider->__T_T___stickRectY = stickRect.y;
    
    return slider;
}

void ksScrollableCanvas::update()
{
    if(!bVisible)
        return;
    
    if(bIsScrolling)
    {
        // 两rect互相错位的顶端和底端在y轴上的offset
        float distanceTop = rect.y - stickRect.y;
        float distanceBottom = (stickRect.y+stickRect.height) - (rect.y+rect.height);
        
        // 判断近那个端
        if(abs(distanceBottom) < stickyDistance)
        {
            nearTop = false;
            nearBot = true;
        }
        if(abs(distanceTop) < stickyDistance)
        {
            nearTop = true;
            nearBot = false;
        }
        
        if(distanceTop > 0)
        {
            acc.y += (-distanceTop)/10.0;
            dampenY();
        }
        else if(nearTop)
        {
            acc.y += (-distanceTop)/10.0;
            dampenY();
        }
        
        if(distanceBottom > 0)
        {
            acc.y += (distanceBottom)/10.0;
            dampenY();
        }
        else if(nearBot)
        {
            acc.y += (distanceBottom)/10.0;
            dampenY();
        }
        
        nearTop = false;
        nearBot = false;
    }
    
    acc.limit(50);
    velocity += acc;
    velocity.limit(100);
    
    if(abs(velocity.y) > 1.0)
        rect.y += floor(velocity.y);
    
    velocity *= damping;
    acc.set(0);
}

void ksScrollableCanvas::draw()
{
    if(!bVisible)
        return;
    
    canvas.begin();
    ofBackground(65);
    if(ksLists.size() > 0)
        button.draw(rect.x + (40 / 2048.0) * windowWidth, rect.y + buttonY - stickRect.y, (button.getWidth() / 2048.0) * windowWidth, (button.getHeight() / 1536.0) * windowHeight);
    
    
    for(int i=0; i<ksLists.size(); i++)
    {
        scopes.drawString(ksLists[i]->name, ksLists[i]->aabb->x + elementX, rect.y + ksLists[i]->aabb->y + fontSize / 2.0 + ksLists[i]->aabb->height / 2.0 - stickRect.y);
        
        //        ofPushStyle();
        //        ofNoFill();
        //        ofSetColor(200, 20, 20);
        //        ofRect(ksLists[i]->aabb->x, ksLists[i]->aabb->y + rect.y - stickRect.y, ksLists[i]->aabb->width, ksLists[i]->aabb->height);
        //        ofPopStyle();
    }
    
    for(int i=0; i<ksSliderLists.size(); i++)
    {
        ksSliderLists[i]->draw(rect.x, rect.y - stickRect.y);
        // --!我无奈的笑了笑 转身走进了雨堆中享受寂寞
        ksSliderLists[i]->__T_T___offsetY = rect.y - stickRect.y;
    }
    
    canvas.end();
    canvas.draw(stickRect.x, stickRect.y, stickRect.width, stickRect.height);
    
    //    ofPushStyle();
    //    ofNoFill();
    //    ofRect(stickRect);
    //    ofPopStyle();
}

void ksScrollableCanvas::dampenY()
{
    if(nearTop || nearBot)
    {
        acc.y -= velocity.y * 0.5;
    }
    else
    {
        acc.y -= velocity.y * (1.0-damping);
    }
}

void ksScrollableCanvas::setVisible(bool visible)
{
    bVisible = visible;
}

bool ksScrollableCanvas::isVisible()
{
    return bVisible;
}

#ifdef KS_TARGET_TOUCH

void ksScrollableCanvas::onTouchDown(ofTouchEventArgs &data)
{
    touchDown(data.x, data.y, data.id);
}

void ksScrollableCanvas::onTouchMoved(ofTouchEventArgs &data)
{
    touchMoved(data.x, data.y, data.id);
}

void ksScrollableCanvas::onTouchUp(ofTouchEventArgs &data)
{
    touchUp(data.x, data.y, data.id);
}

void ksScrollableCanvas::onTouchDoubleTap(ofTouchEventArgs &data)
{
    touchDoubleTap(data.x, data.y, data.id);
}

void ksScrollableCanvas::onTouchCancelled(ofTouchEventArgs &data)
{
    touchCancelled(data.x, data.y, data.id);
}

void ksScrollableCanvas::touchDown(float x, float y, int id)
{
    if(stickRect.inside(x, y))
    {
        bHit = true;
        
        for(int i=0; i<ksLists.size(); i++)
        {
            if(ksLists[i]->aabb->inside(x, y - rect.y))
            {
                buttonY = rect.y + ksLists[i]->aabb->y;
                ksMessageQueue::messages.push_back(ksLists[i]->name);
                break;
            }
        }
    }
    else
        bHit = false;
    
    // 保证鼠标拖拽时第一次按下的位置能够捕获
    bIsScrolling = false;
    velocity.set(0,0);
}

void ksScrollableCanvas::touchMoved(float x, float y, int id)
{
    if(bHit)
    {
        if(!bIsScrolling)
        {
            bIsScrolling = true;
            previousPosition = ofPoint(x,y);
            velocity.set(0,0);
        }
        else
        {
            position = ofPoint(x, y);
            velocity = position - previousPosition;
            rect.y += velocity.y;
            previousPosition = position;
        }
    }
}

void ksScrollableCanvas::touchUp(float x, float y, int id)
{
    bHit = false;
    if(bIsScrolling)
    {
        bIsScrolling = false;
        position = ofPoint(x,y);
    }
}

void ksScrollableCanvas::touchCancelled(float x, float y, int id)
{
    
}

void ksScrollableCanvas::touchDoubleTap(float x, float y, int id)
{
    
}

#endif

void ksScrollableCanvas::mouseDragged(int x, int y, int button)
{
    if(bHit && bVisible)
    {
        if(!bIsScrolling)
        {
            bIsScrolling = true;
            previousPosition = ofPoint(x,y);
            velocity.set(0,0);
        }
        else
        {
            position = ofPoint(x, y);
            velocity = position - previousPosition;
            rect.y += velocity.y;
            previousPosition = position;
        }
    }
}

void ksScrollableCanvas::mousePressed(int x, int y, int button)
{
    if(!bVisible)
        return;
    
    if(stickRect.inside(x, y))
        bHit = true;
    else
        bHit = false;
    
    // 保证鼠标拖拽时第一次按下的位置能够捕获
    bIsScrolling = false;
    velocity.set(0,0);
    
    
}

void ksScrollableCanvas::mouseReleased(int x, int y, int button)
{
    if(!bVisible)
        return;
    
    bHit = false;
    if(bIsScrolling)
    {
        bIsScrolling = false;
        position = ofPoint(x,y);
    }
    
    if(velocity.x == 0.0f && velocity.y == 0.0f)
    {
        for(int i=0; i<ksLists.size(); i++)
        {
            if(ksLists[i]->aabb->inside(x, y - rect.y))
            {
                buttonY = ksLists[i]->aabb->y;
                ksMessageQueue::messages.push_back(ksLists[i]->name);
                break;
            }
        }
    }
}

void ksScrollableCanvas::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
void ksScrollableCanvas::onMousePressed(ofMouseEventArgs& data)
{
    mousePressed(data.x, data.y, data.button);
}

void ksScrollableCanvas::onMouseDragged(ofMouseEventArgs& data)
{
    mouseDragged(data.x, data.y, data.button);
}

void ksScrollableCanvas::onMouseReleased(ofMouseEventArgs& data)
{
    mouseReleased(data.x, data.y, data.button);
}

void ksScrollableCanvas::onMouseMoved(ofMouseEventArgs& data)
{
    mouseMoved(data.x, data.y);
}

//#endif