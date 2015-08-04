#include <ks/base/ksController.h>
#include <ks/base/ksBase.h>
#include <ks/utility/ksLog.h>
#include <ks/utility/ksFileLoader.h>

// kaleidoscopes
//#include <scopes/ksScopes.h>

// resource
#include <ks/base/ksResource.h>
#include <ks/base/ksDefault.h>

// standard
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// ksApp
#include <ks/ksApp.h>

ksController::ksController()
{
    selected = NULL;
    
    // 提前找到
    defaults = ksDefault::getInstance();
    //resources = ksResource::getInstance();
}

ksController* ksController::getInstance()
{
    static ksController temp;
    return &temp;
}

void ksController::initKsLists()
{
    ksFileLoader loader;
    loader.loadFile("ks");
    if(loader.countFiles() == 0)
    {
        ksLog("Warning: 当前没有任何万花筒可供渲染\n");
        return;
    }
    
    for(int i=0; i<loader.countFiles(); i++)
    {
        if(loader.getFile(i).isDirectory())
        {
            ksBase *base;
            
            ksLog("--------------------------%s--------------------------\n", loader.getName(i).c_str());
            
            // 万花筒文件夹名需与脚本文件同名
            string path = "ks/" + loader.getName(i) + "/" + loader.getName(i) + ".xml";
            static char className[32];
            strcpy(className, loader.getName(i).c_str());
            // C++反射机制 使用类名生成对象
            // 此处是类型安全的 因为map中找不到这个cType就会自动返回NULL
            base = ksBase::create(className);
            if(!base)
            {
                ksLog("Error: 并没有找到合适的对应类型\"%s\"\n", className);
                continue;
            }
            
            // 方便后期调用
            string temp = "ks/" + loader.getName(i) + "/";
            strcpy(base->path, temp.c_str());
            
            // 资源自动配置初始化
            // --!实质为自动读取整个资源文件夹(images, music, font, video等)
            initKsResources(className, base);
            
            // 此处base已经被初始化完毕
            add(base);
            
            // 如若没能生成对应类型万花筒 脚本信息会直接跳过
            if(xml.load(path.c_str()))
            {
                Poco::XML::Element* element = xml.getPocoElement();
                
                if(element->tagName() == "ks")
                {
                    // 只有脚本格式化正确才会为对话框分配内存
                    base->information = new ksInformation();
                    base->information->disableVisible();
                    
                    // name
                    if(element->hasAttribute("name"))
                    {
                        const char* name = element->getAttribute("name").c_str();
                        ksLog("name: %s\n", name);
                        base->setName(name);
                        base->information->changeTag(name);
                    }
                    else
                    {
                        ksLog("Warning: 必须在万花筒文件中指定在gui上显示的名称, 已设为与类名相同的\"%s\"默认值\n", loader.getName(i).c_str());
                        base->setName(loader.getName(i).c_str());
                    }
                    
                    // 可选属性
                    if(element->hasAttribute("author"))
                    {
                        const char* author = element->getAttribute("author").c_str();
                        ksLog("author: %s\n", author);
                        strcpy(base->author, author);
                        base->information->changeAuthor(author);
                    }
                    
                    if(element->hasAttribute("date"))
                    {
                        const char* date = element->getAttribute("date").c_str();
                        ksLog("date: %s\n", date);
                        strcpy(base->date, date);
                        base->information->changeDate(date);
                    }
                    
                    string intro = element->innerText();
                    const char* cIntro = intro.c_str();
                    if(cIntro)
                    {
                        ksLog("intro: %s\n", cIntro);
                        strcpy(base->intro, cIntro);
                        base->information->changeInfo(cIntro);
                    }
                }
                else
                    ksLog("Warning: 文件\"%s\"格式有误 根节点需为<ks>\n", path.c_str());
            }
            else
                ksLog("Warning: 脚本文件\"%s\"读取出错 可能是文件名有误所致\n", path.c_str());
        }
    }
}

void ksController::initKsResources(const char* ksName, ksBase* base)
{
    // images
    ksFileLoader loader;
    // 快速地址
    string imagePath = base->path;
    imagePath += "images/";
    
    // user-defined image initialize
    loader.loadFile(imagePath);
    for(int i=0; i<loader.countFiles(); i++)
    {
        ofImage *imageTemp = new ofImage();
        
        // 路径名/图片名
        string imageName = imagePath + loader.getName(i);
        ksLog("image[%d]: %s\n", i, imageName.c_str());
        
        imageTemp->loadImage(imageName);
        
        // 完成特定类型图片系初始化
        ksResource::addImage(ksName, loader.getName(i).c_str(), imageTemp);
    }
    
    // shader
    // 快速地址
    string shaderPath = base->path;
    shaderPath += "shader/";
    
    loader.loadFile(shaderPath);
    for(int i=0; i<loader.countFiles(); i++)
    {
        ofShader* tempShader = new ofShader();
        
        bool bLoadSucceed = false;
        
        // 路径名/Shader基础名
        string shaderName = shaderPath + loader.getBaseName(i);
        
        ksLog("shader[%d]: %s\n", i, (shaderPath + loader.getName(i)).c_str());
        
        ksLog("-----------------%s Shader-----------------\n", loader.getBaseName(i).c_str());
        
        string fragName = shaderName + ".frag";
        string vertName = shaderName + ".vert";
        bLoadSucceed = tempShader->load(vertName, fragName);
        
        if(bLoadSucceed)
            // 不会添加重复名的shader
            // 不带后缀的名字键值
            ksResource::addShader(ksName, loader.getBaseName(i).c_str(), tempShader);
        else
        {
            ksLog("\nError: 添加Shader错误, 或因Shader语法错误, 或Shader(vert frag)未成对出现, 或后缀名并不符合.vert .frag的要求\n");
            delete tempShader;
            
            tempShader = NULL;
        }
    }
    
    // music
    string musicPath = base->path;
    musicPath += "music/";
    
    loader.loadFile(musicPath);
    for(int i=0; i<loader.countFiles(); i++)
    {
        ofSoundPlayer* tempMusic = new ofSoundPlayer();
        
        string musicName = musicPath + loader.getName(i);
        ksLog("music[%d]: %s\n", i, musicName.c_str());
        
        tempMusic->loadSound(musicName);
        tempMusic->setVolume(1.0);
        ksResource::addMusic(ksName, loader.getName(i).c_str(), tempMusic);
    }
    
    // camera
    static ofVideoGrabber *camera = new ofVideoGrabber();
    if(!camera->isInitialized())
    {
        //camera->setDeviceID(1);
        if(camera->initGrabber(ksApp::getWidth(), ksApp::getHeight()))
        {
            ksResource::addCamera(camera);
        }
        else
            ksLog("Error: 摄像头资源添加失败\n");
    }

	// videos
	// 快速地址
	string videoPath = base->path;
	videoPath += "video/";

	// user-defined image initialize
	loader.loadFile(videoPath);
	for(int i=0; i<loader.countFiles(); i++)
	{
		ofVideoPlayer *tempVideo = new ofVideoPlayer();

		// 路径名/图片名
		string videoName = videoPath + loader.getName(i);
		ksLog("video[%d]: %s\n", i, videoName.c_str());

		tempVideo->loadMovie(videoName);

		// 完成特定类型图片系初始化
		ksResource::addVideo(ksName, loader.getName(i).c_str(), tempVideo);
	}
}

std::vector<ksBase*>& ksController::getKsLists()
{
    return ksLists;
}

void ksController::add( ksBase* object )
{
    if(object)
    {
        // 当前万花筒所在序号
        object->setID(ksLists.size());
        ksLists.push_back(object);
        
        // 若为第一个万花筒对象 设定为默认选中对象
        if(ksLists.size() == 1)
            selected = ksLists[0];
    }
    else
        ksLog("Warning: 不能在ksApp中添加一个空指针\n");
}

void ksController::setSelected( int index )
{
    if(index <= ksLists.size() || index >= 0)
    {
        // 巧妙的使用了id提高寻找速度 免去了名称字符串比较的过程
        selected = ksLists[index];
    }
    else
        ksLog("Error: 设置选中对象时 序号%d有误", index);
}

ksBase * ksController::getSelected()
{
    return selected;
}
