#include <ks/base/ksBase.h>
#include <ks/utility/ksLog.h>
#include <iostream>

// resource
#include <ks/base/ksResource.h>

// --!基类中完成C++反射部署
//IMPLEMENT_DYNCRT_BASE(ksBase)

ksBase::ksBase()
{
    //resources = ksResource::getInstance();
	gui = NULL;
    bClear = true;
    bTranslateMousePosition = false;
}

// 强制new实例化
ksBase::~ksBase()
{
    id = -1;
}

//void ksBase::init()
//{
//    
//}
//
//void ksBase::update()
//{
//}
//
//void ksBase::draw()
//{
//    
//}

void ksBase::setName(const char *name)
{
    strcpy(this->name, name);
}

const char* ksBase::getName()
{
	return name;
}

void ksBase::setID(int id)
{
    this->id = id;
}

void ksBase::keyPressed(int key)
{
    //ksLog("ksBase: %d\n", key);
}

void ksBase::keyReleased(int key)
{
    //ksLog("ksBase: %d\n", key);
}

void ksBase::mouseMoved(int x, int y)
{
    //ksLog("ksBase: %d %d\n", x, y);
}

void ksBase::mouseDragged(int x, int y, int button)
{
    //ksLog("ksBase: %d %d %d\n", x, y, button);
}

void ksBase::mousePressed(int x, int y, int button)
{
    //ksLog("ksBase: %d %d %d\n", x, y, button);
}

void ksBase::mouseReleased(int x, int y, int button)
{
    //ksLog("ksBase: %d %d %d\n", x, y, button);
}

void ksBase::drawGui()
{
	gui->draw();
}
