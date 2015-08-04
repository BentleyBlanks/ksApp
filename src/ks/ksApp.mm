#include <ks/ksApp.h>
#include <ks/utility/ksLog.h>
#include <ks/base/ksBase.h>
#include <ks/base/ksController.h>
#include <ks/base/ksResource.h>
// gui
#include <ks/ui/ksScrollableCanvas.h>
#include <ks/ui/ksIconButton.h>
#include <ks/ui/ksMessageQueue.h>

#import "Social/Social.h"

#define IS_KS_INITIALIZED if(!bInitialized)\
{\
    ksLog("Error: ksApp not initalized\n");\
    return;\
}

int ksApp::width = 0;
int ksApp::height = 0;
int ksApp::contentWidth = 0;
int ksApp::contentHeight = 0;

ksApp::ksApp()
{
    canvas = NULL;
    bInitialized = false;
    gui = NULL;
    content = NULL;
}

// 全局内存分配 消息分派
void ksApp::init()
{
    //	if(!gui)
    //		// 万花筒的gui全部由ksApp完成监控和部署
    //		gui = new ofxUIScrollableCanvas();
    //	//gui->disableAppDrawCallback();
    //	gui->setVisible(true);
    
    // 预分配ks控制器内存占用
    controller = ksController::getInstance();
    
    // canvas已经分配
    if(!canvas)
        canvas = new ofFbo();
    canvas->allocate(ofGetWidth(), ofGetHeight());
    
    if(!content)
        content = new ofFbo();
    content->allocate((810 / 1024.0) * width, (740 / 768.0) * height);
    
    contentWidth = content->getWidth();
    contentHeight = content->getHeight();
    width = canvas->getWidth();
    height = canvas->getHeight();
    
    bInitialized = true;
    
    // 鼠标键盘等响应
    ofAddListener(ofEvents().keyPressed, this, &ksApp::keyPressed);
    ofAddListener(ofEvents().keyReleased, this, &ksApp::keyReleased);
    
    ofAddListener(ofEvents().mouseMoved, this, &ksApp::mouseMoved);
    ofAddListener(ofEvents().mouseDragged, this, &ksApp::mouseDragged);
    ofAddListener(ofEvents().mousePressed, this, &ksApp::mousePressed);
    ofAddListener(ofEvents().mouseReleased, this, &ksApp::mouseReleased);
    
    ofAddListener(ofEvents().windowResized, this, &ksApp::windowResized);
    
    //	ofAddListener(gui->newGUIEvent, this, &ksApp::guiEvent);
    
    // 全局内存分配
    initKsLists();
    
    std::vector<ksBase*>& ksLists = controller->getKsLists();
    
    //    gui->setGlobalButtonDimension(32);
    //    gui->addLabelButton("Change Resource", false);
    
    initGui();
    
    // 根据ks列表初始化gui
    for(int i=0; i<ksLists.size(); i++)
    {
        //        gui->addLabelButton(ksLists[i]->getName(), false);
        gui->addButton(ksLists[i]->getName());
        
        
        if(!ksLists[i]->gui)
            ksLists[i]->gui = new ksScrollableCanvas();
        
        ksLists[i]->gui->setVisible(false);
        
        ksLists[i]->gui->init(0, (110 / 768.0) * height, (198 / 1024.0) * width, height - ((180 + 110) / 768.0) * height, (30 / 1024.0) * width, (40 / 768.0) * height, (width / 1024.0) * 10);

//        if(!ksLists[i]->gui)
//            // 会在外部手工完成gui的渲染工作
//            ksLists[i]->gui = new ofxUIScrollableCanvas();
//        //ksLists[i]->gui->disableAppDrawCallback();
//        ksLists[i]->gui->setGlobalButtonDimension(32);
//        
//        ksLists[i]->gui->setVisible(false);
//        // --!最好能够在initKsLists时就完成初始化
        ksLists[i]->init();
//        
//        // 初始化所有用户gui的位置
//        ksLists[i]->gui->autoSizeToFitWidgets();
//        ksLists[i]->gui->setPosition(canvas->getWidth() - ksLists[i]->gui->getRect()->getWidth(), 0);
//        ksLists[i]->gui->setHeight(canvas->getHeight());
    }
    
    // 默认选为第一个万花筒
    if(ksLists.size() > 0)
        setSelected(0);
    
    //	gui->autoSizeToFitWidgets();
    //	gui->setHeight(canvas->getHeight());
}

void ksApp::initGui()
{
    if(!gui)
        gui = new ksScrollableCanvas();
    
    ofImage *iconTexture = new ofImage("default/image/logo.png");
    icon.allocate(iconTexture->getWidth(), iconTexture->getHeight());
    icon.begin();
    iconTexture->draw(0, 0);
    icon.end();
    
    ofImage *spacerTexture = new ofImage("default/image/spacer.png");
    spacer.allocate(spacerTexture->getWidth(), spacerTexture->getHeight());
    spacer.begin();
    spacerTexture->draw(0, 0);
    spacer.end();
    
    ofImage *maskTexture = new ofImage("default/image/mask.png"), *maskTexture1 = new ofImage("default/image/mask1.png");
    mask.allocate(maskTexture->getWidth(), maskTexture->getHeight());
    mask.begin();
    maskTexture1->draw(0, 0);
    maskTexture->draw(0, 0);
    mask.end();
    
    title.loadFont("default/font/ksFont.otf", (width / 1024.0) * 16);
    
    switchButton = new ksIconButton();
    switchButton->init("switch", ofRectangle(0, (626 / 768.0) * height, (180 / 1024.0) * width, (40 / 768.0) * height));
    switchButton->setMaterial("default/image/switchNormal.png", "default/image/switchPressed.png", "default/font/ksFont.otf", (width / 1024.0) * 10);

    informationButton = new ksIconButton();
    informationButton->init("information", ofRectangle(0, ((626 + 40 * 1) / 768.0) * height, (180 / 1024.0) * width, (40 / 768.0) * height));
    informationButton->setMaterial("default/image/informationNormal.png", "default/image/informationPressed.png", "default/font/ksFont.otf", (width / 1024.0) * 10);
    
    settingsButton = new ksIconButton();
    settingsButton->init("settings", ofRectangle(0, ((626 + 40 * 2) / 768.0) * height, (180 / 1024.0) * width, (40 / 768.0) * height));
    settingsButton->setMaterial("default/image/settingsNormal.png", "default/image/settingsPressed.png", "default/font/ksFont.otf", (width / 1024.0) * 10);
    
    gui->init(0, (110 / 768.0) * height, (198 / 1024.0) * width, height - ((180 + 110) / 768.0) * height, (30 / 1024.0) * width, (40 / 768.0) * height, (width / 1024.0) * 10);
}

void ksApp::initKsLists()
{
    controller->initKsLists();
}

void ksApp::update()
{
    IS_KS_INITIALIZED
    
    // 更新资源
    ksResource::update();
    
    static float lastTime = 0, nowTime = 0;
    
    nowTime = ofGetElapsedTimef();
    
    // 更新选中名单
    guiEvent();
    
    ksBase *selected = controller->getSelected();
    if(selected)
    {
        selected->update(nowTime - lastTime);
        selected->gui->update();
        selected->information->update();
    }
    else
        ksLog("Warning: ksApp没有选定任何对象\n");
    
    gui->update();

    lastTime = nowTime;
    
    // 消息处理完毕清空消息队列
    ksMessageQueue::messages.clear();
}

void ksApp::draw()
{
    IS_KS_INITIALIZED
    
    //canvas->begin();
    
    ofBackground(65, 65, 65, 200);
    
    // gui必要组件渲染
    // 上半部gui
    title.drawString("ksApp", 0.0798 * width, (100 / 1536.0) * height + (width / 1024.0) * 16);
    
    icon.draw(0.0295 * width, (74 / 1536.0) * height, 0.03906 * width, 0.03906 * width);
    
    spacer.draw((58 / 2048.0) * width, (200 / 1536.0) * height, (240 / 2048.0) * width, 0.002604 * height);
    
    // 用户gui
    ksBase *selected = controller->getSelected();
    if(selected)
    {
        selected->gui->draw();
    }
    // 边栏gui
    gui->draw();

    spacer.draw((58 / 2048.0) * width, (606 / 768.0) * height, (240 / 2048.0) * width, 0.002604 * height);

    // 下半部gui
    switchButton->draw();
    
    informationButton->draw();
    
    settingsButton->draw();
    
    content->begin();
    
    if(selected)
    {
        if(selected->bClear)
            ofBackgroundGradient(ofColor(255), ofColor(128));
        
        selected->draw(0, 0, width, height);
    }
    else
        ksLog("Warning: ksApp没有选定任何对象\n");
    
    content->end();
    content->draw((197 / 1024.0) * width, (14 / 768.0) * height, (810 / 1024.0) * width, (740 / 768.0) * height);
    
    mask.draw((180 / 1024.0) * width, 0, (844 / 1024.0) * width, height);
    
    if(selected)
        selected->information->draw();
    
    title.drawString(ofToString(ofGetMouseX()) + ", " + ofToString(ofGetMouseY()), ofGetMouseX(), ofGetMouseY());
    //title.drawString(ofToString(ofGetFrameRate()), ofGetMouseX(), ofGetMouseY());
    
    //canvas->end();

    // 一定与当前屏幕大小相同
    //canvas->draw(0, 0);
}

void ksApp::setSelected(int index)
{
    // 原先可见的设为不可见
    //controller->getSelected()->gui->setVisible(false);
    
    controller->setSelected(index);
    
    //controller->getSelected()->gui->setVisible(true);
}

int ksApp::getWidth()
{
    return width;
}

int ksApp::getHeight()
{
    return height;
}

int ksApp::getContentWidth()
{
    return contentWidth;
}

int ksApp::getContentHeight()
{
    return contentHeight;
}

void ksApp::windowResized(ofResizeEventArgs & resize)
{
    // 重置
    //init();
}

void ksApp::keyPressed(ofKeyEventArgs &key)
{
    if(controller->getSelected())
        controller->getSelected()->keyPressed(key.key);
    else
        ksLog("Warning: ksApp没有选定任何对象");
}

void ksApp::keyReleased(ofKeyEventArgs &key)
{
    if(controller->getSelected())
        controller->getSelected()->keyReleased(key.key);
    else
        ksLog("Warning: ksApp没有选定任何对象");
}

void ksApp::mouseMoved(ofMouseEventArgs &mouse)
{
    if(controller->getSelected())
    {
        if(controller->getSelected()->bTranslateMousePosition)
        {
            // 鼠标坐标进行特殊翻译后再传给万花筒
            int x = (mouse.x - 396.0 * width / 2048.0) * width / (1624.0 * width / 2048.0);
            int y = (mouse.y - 28.0 * width / 2048.0) * height / (1480.0 * height / 1536.0);
            
            controller->getSelected()->mouseMoved(x, y);
        }
        else
            controller->getSelected()->mouseMoved(mouse.x, mouse.y);
    }
    else
        ksLog("Warning: ksApp没有选定任何对象");
}

void ksApp::mouseDragged(ofMouseEventArgs &mouse)
{
    if(controller->getSelected())
    {
        if(controller->getSelected()->bTranslateMousePosition)
        {
            // 鼠标坐标进行特殊翻译后再传给万花筒
            int x = (mouse.x - 396.0 * width / 2048.0) * width / (1624.0 * width / 2048.0);
            int y = (mouse.y - 28.0 * width / 2048.0) * height / (1480.0 * height / 1536.0);

            controller->getSelected()->mouseDragged(x, y, mouse.button);
        }
        else
            controller->getSelected()->mouseDragged(mouse.x, mouse.y, mouse.button);
    }
    else
        ksLog("Warning: ksApp没有选定任何对象");
}

void ksApp::mousePressed(ofMouseEventArgs &mouse)
{
    if(controller->getSelected())
    {
        if(controller->getSelected()->bTranslateMousePosition)
        {
            // 鼠标坐标进行特殊翻译后再传给万花筒
            int x = (mouse.x - 396.0 * width / 2048.0) * width / (1624.0 * width / 2048.0);
            int y = (mouse.y - 28.0 * width / 2048.0) * height / (1480.0 * height / 1536.0);
            
            controller->getSelected()->mousePressed(x, y, mouse.button);
        }
        else
            controller->getSelected()->mousePressed(mouse.x, mouse.y, mouse.button);
    }
    else
        ksLog("Warning: ksApp没有选定任何对象");
}

void ksApp::mouseReleased(ofMouseEventArgs &mouse)
{
    if(controller->getSelected())
    {
        if(controller->getSelected()->bTranslateMousePosition)
        {
            // 鼠标坐标进行特殊翻译后再传给万花筒
            int x = (mouse.x - 396.0 * width / 2048.0) * width / (1624.0 * width / 2048.0);
            int y = (mouse.y - 28.0 * width / 2048.0) * height / (1480.0 * height / 1536.0);
           
            controller->getSelected()->mouseReleased(x, y, mouse.button);
        }
        else
            controller->getSelected()->mouseReleased(mouse.x, mouse.y, mouse.button);
    }
    else
        ksLog("Warning: ksApp没有选定任何对象");
}

void ksApp::guiEvent()
{
    if(ksMessageQueue::messages.size() > 0)
    {
        for(int i=0; i<ksMessageQueue::messages.size(); i++)
        {
            bool bProcessed = false;
            
            std::vector<ksBase*>& ksLists = controller->getKsLists();
            for(int j=0; j<ksLists.size(); j++)
            {
                if(!strcmp(ksLists[j]->getName(), ksMessageQueue::messages[i].c_str()))
                {
                    ksResource::getKsMusic()->play();
                    setSelected(j);
                    bProcessed = true;
                    break;
                }
            }
            
            if(!bProcessed)
            {
                if(!strcmp("switch", ksMessageQueue::messages[i].c_str()))
                {
                    ksLog("Debug: switch pressed!\n");
                    ksResource::changeResource();
                    ksResource::getKsMusic()->play();
                }
                else if(!strcmp("information", ksMessageQueue::messages[i].c_str()))
                {
                    ksLog("Debug: information pressed!\n");
                    controller->getSelected()->information->visable();
                    ksResource::getKsMusic()->play();
                }
                else if(!strcmp("settings", ksMessageQueue::messages[i].c_str()))
                {
                    ksLog("Debug: settings pressed!\n");
                    // 切换可见与不可见
                    if(gui->isVisible())
                    {
                        gui->setVisible(false);
                        controller->getSelected()->gui->setVisible(true);
                    }
                    else
                    {
                        gui->setVisible(true);
                        controller->getSelected()->gui->setVisible(false);
                    }
                    ksResource::getKsMusic()->play();
                }
            }
        }
    }
}
