#include <ks/ui/ksIconButton.h>
#include <ks/ui/ksMessageQueue.h>
#include <ks/ksApp.h>

ksIconButton::ksIconButton()
{
#ifdef KS_TARGET_TOUCH
    // 事件监听
    ofAddListener(ofEvents().touchCancelled, this, &ksIconButton::onTouchCancelled);
    ofAddListener(ofEvents().touchDoubleTap, this, &ksIconButton::onTouchDoubleTap);
    ofAddListener(ofEvents().touchDown, this, &ksIconButton::onTouchDown);
    ofAddListener(ofEvents().touchMoved, this, &ksIconButton::onTouchMoved);
    ofAddListener(ofEvents().touchUp, this, &ksIconButton::onTouchUp);
#endif
    // 事件监听
    ofAddListener(ofEvents().mouseReleased, this, &ksIconButton::onMouseReleased);
    ofAddListener(ofEvents().mousePressed, this, &ksIconButton::onMousePressed);
    ofAddListener(ofEvents().mouseMoved, this, &ksIconButton::onMouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &ksIconButton::onMouseDragged);
//#endif
    
    bIsPressed = false;
    bVisible = true;
    
    normalColor.set(240, 240, 240);
    pressedColor.set(209, 59, 59);
}

// aabb初始化
void ksIconButton::init(string name, ofRectangle aabb)
{
    this->name = name;
    this->aabb.set(aabb.x, aabb.y, aabb.width, aabb.height);
}

void ksIconButton::setMaterial(string iconPath, string iconPressedPath, string fontPath, int fontSize)
{
    ofImage *iconTexture = new ofImage(iconPath);
    icon.allocate(iconTexture->getWidth(), iconTexture->getHeight());
    icon.begin();
    iconTexture->draw(0, 0);
    icon.end();
    
    ofImage *iconPressedTexture = new ofImage(iconPressedPath);
    iconPressed.allocate(iconPressedTexture->getWidth(), iconPressedTexture->getHeight());
    iconPressed.begin();
    iconPressedTexture->draw(0, 0);
    iconPressed.end();
    
    buttonFont.loadFont(fontPath, fontSize);
    
    // 缓存文字以优化性能
//    nameNormalFbo.allocate((ksApp::getWidth() / 1024.0) * 198, fontSize * 3);
//    nameNormalFbo.begin();
//    ofPushStyle();
//    ofSetColor(normalColor);
//    buttonFont.drawString(name, 0, aabb.height * 0.5 + fontSize * 0.5);
//    ofPopStyle();
//    nameNormalFbo.end();
//    
//    namePressedFbo.allocate((ksApp::getWidth() / 1024.0) * 198, fontSize * 3);
//    namePressedFbo.begin();
//    ofPushStyle();
//    ofSetColor(pressedColor);
//    buttonFont.drawString(name, 0, aabb.height * 0.5 + fontSize * 0.5);
//    ofPopStyle();
//    namePressedFbo.end();
    
    this->fontSize = fontSize;
}

void ksIconButton::setFontColor(ofColor normal, ofColor pressed)
{
    normalColor.set(normal.r, normal.g, normal.b, normal.a);
    pressedColor.set(pressed.r, pressed.g, pressed.b, pressed.a);
}

void ksIconButton::update()
{
    
}

void ksIconButton::draw()
{
    if(!bVisible)
        return;
    
    if(bIsPressed)
    {
        iconPressed.draw(aabb.x + aabb.width * (59 / 308.0),
                         aabb.y + aabb.height * 0.5 - iconPressed.getHeight() * 0.5 * (ksApp::getHeight() / 1536.0),
                         (iconPressed.getWidth() / 2048.0) * ksApp::getWidth(),
                         (iconPressed.getHeight() / 1536.0) * ksApp::getHeight());
        
        
        ofPushStyle();
        ofSetColor(pressedColor);
        buttonFont.drawString(name,
                              aabb.x + aabb.width * (125 / 308.0),
                              aabb.y + aabb.height * 0.5 + fontSize * 0.5);
        ofPopStyle();
        //namePressedFbo.draw(aabb.x + aabb.width * (125 / 308.0), aabb.y);
    }
    else
    {
        icon.draw(aabb.x + aabb.width * (59 / 308.0),
                  aabb.y + aabb.height * 0.5 - icon.getHeight() * 0.5 * (ksApp::getHeight() / 1536.0),
                  (icon.getWidth() / 2048.0) * ksApp::getWidth(),
                  (icon.getHeight() / 1536.0) * ksApp::getHeight());
        
        
        ofPushStyle();
        ofSetColor(normalColor);
        buttonFont.drawString(name,
                              aabb.x + aabb.width * (125 / 308.0),
                              aabb.y + aabb.height * 0.5 + fontSize * 0.5);
        ofPopStyle();
        //nameNormalFbo.draw(aabb.x + aabb.width * (125 / 308.0), aabb.y);

    }
    
//    ofPushStyle();
//    ofNoFill();
//    ofRect(aabb);
//    ofPopStyle();
}

void ksIconButton::setVisible(bool visible)
{
    bVisible = visible;
}

bool ksIconButton::isVisible()
{
    return bVisible;
}

#ifdef KS_TARGET_TOUCH

void ksIconButton::onTouchDown(ofTouchEventArgs &data)
{
    
}

void ksIconButton::onTouchMoved(ofTouchEventArgs &data)
{
    
}

void ksIconButton::onTouchUp(ofTouchEventArgs &data)
{
    
}

void ksIconButton::onTouchDoubleTap(ofTouchEventArgs &data)
{
    
}

void ksIconButton::onTouchCancelled(ofTouchEventArgs &data)
{
    
}

void ksIconButton::touchDown(float x, float y, int id)
{
    
}

void ksIconButton::touchMoved(float x, float y, int id)
{
    
}

void ksIconButton::touchUp(float x, float y, int id)
{
    
}

void ksIconButton::touchCancelled(float x, float y, int id)
{
    
}

void ksIconButton::touchDoubleTap(float x, float y, int id)
{
    
}

#endif

void ksIconButton::mouseDragged(int x, int y, int button)
{
    
}

void ksIconButton::mousePressed(int x, int y, int button)
{
    if(aabb.inside(x, y))
    {
        bIsPressed = true;
    }
}

void ksIconButton::mouseReleased(int x, int y, int button)
{
    if(bIsPressed)
    {
        bIsPressed = false;
        ksMessageQueue::messages.push_back(name);
    }
}

void ksIconButton::mouseMoved(int x, int y )
{
    
}

//--------------------------------------------------------------
void ksIconButton::onMousePressed(ofMouseEventArgs& data)
{
    mousePressed(data.x, data.y, data.button);
}

void ksIconButton::onMouseDragged(ofMouseEventArgs& data)
{
    mouseDragged(data.x, data.y, data.button);
}

void ksIconButton::onMouseReleased(ofMouseEventArgs& data)
{
    mouseReleased(data.x, data.y, data.button);
}

void ksIconButton::onMouseMoved(ofMouseEventArgs& data)
{
    mouseMoved(data.x, data.y);
}

//#endif