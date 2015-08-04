#ifndef KSBASE_H
#define KSBASE_H

#include <ofMain.h>

// macro
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string>
#include <ks/utility/ksSettings.h>

// ui
//#include <ofxUI.h>
#include <ks/ui/ksScrollableCanvas.h>
#include <ks/ui/ksInformation.h>

// typedef重命名一个返回值为xx的 参数为空的函数指针
// _register()中添加 名字/回调函数键值对
// create()中根据名称调用了回调函数指针

// 保证静态变量在使用期间一定已经被初始化过
// <0, std::map<const char*, classGenerationCallBack> > -> classSet
// <0, std::vector<std::string> > -> className
#define DECLEAR_DYNAMIC_BASE(base)\
public:\
	typedef base* (*classGenerationCallBack)();\
	static void _register(const char* className, classGenerationCallBack class_gen)\
	{\
        base::var<0, std::map<const char*, classGenerationCallBack> >().insert(std::map<const char*, classGenerationCallBack>::value_type(className, class_gen));\
	}\
	\
	static base* create(const char* className)\
	{\
        std::map<const char*, classGenerationCallBack> classSet = base::var<0, std::map<const char*, classGenerationCallBack> >();\
		for(std::map<const char*, classGenerationCallBack>::iterator it = classSet.begin(); it!=classSet.end(); ++it)\
		{\
			if(!strcmp(it->first, className))\
				return (it->second)();\
		}\
		return NULL;\
	}\
    template <int N, class T>\
    static T& var()\
    {\
        static T instance;\
        return instance;\
    }
//protected:\
//static std::vector<std::string> classNames;
//	static std::map<const char*, classGenerationCallBack> classSet;

// 类外定义
//#define IMPLEMENT_DYNCRT_BASE(base) \
//	std::map<const char*, base::classGenerationCallBack> base::classSet;\
//	std::vector<std::string> base::classNames;

//#define IMPLEMENT_DYNCRT_BASE(base) \
//    base::var<0, std::map<const char*, classGenerationCallBack> >();\
//    base::var<0, vector<std::string> >();

// 创建一个隐匿的结构体 他的构造函数会在子类构造函数被调用时自动调用
// 通过创建一个编译期间的模板函数_createObjectByName()来分配子类内存
#define ksRegisterClass(derived) \
	static ksBase* _CreateObjectByName() \
	{ \
		return new derived; \
	}\
	struct derived##register \
	{ \
		derived##register() \
		{ \
			static bool bRegister = false; \
			if (!bRegister) \
			{ \
				ksBase::_register(#derived, _CreateObjectByName); \
                \
                std::vector<std::string> classNames = ksBase::var<0, vector<std::string> >();\
				classNames.push_back(#derived); \
				bRegister = true; \
			} \
		} \
	}; \
	static derived##register _##derived##global_object;

class ksResource;
class ksImage;

class ksBase
{
	// --!基类中完成C++反射部署
	DECLEAR_DYNAMIC_BASE(ksBase)
public:
    ksBase();
    // 强制new实例化
    virtual ~ksBase();
    
    virtual void init() = 0;
    
    virtual void update(float dt) = 0;

	// 绘制起始位置 / 可绘制区域大小
    virtual void draw(int x, int y, int width, int height) = 0;
    
    void setName(const char *name);

	const char* getName();
    
    friend class ksController;
	friend class ksApp;

protected:
    virtual void keyPressed( int key );
    virtual void keyReleased( int key );
    
    virtual void mouseMoved( int x, int y );
    virtual void mouseDragged( int x, int y, int button );
    virtual void mousePressed( int x, int y, int button );
    virtual void mouseReleased(int x, int y, int button );

	// 无需手工设定
	void setID(int id);

	// 特殊的快速寻找对象的办法
	int id;

	// 当前万花筒名称 简介等信息
	char name[64], intro[256], author[32], date[32];

	// 当前万花筒所在根目录
	char path[256];

    // 资源管理中心
    //ksResource *resources;
    
	// ui渲染中心
	//ofxUICanvas* gui;
    ksScrollableCanvas* gui;
    ksInformation *information;
    
    bool bTranslateMousePosition;
    bool bClear;
private:
	// 不需要用户来管理的渲染操作
	void drawGui();
};

#endif
