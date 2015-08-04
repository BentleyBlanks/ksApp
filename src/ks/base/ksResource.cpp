#include <ks/base/ksResource.h>
#include <ks/utility/ksLog.h>
#include <ks/utility/ksSettings.h>

// 保证构造函数一定会被调用
//ksResource g_ksResource;	

// 类外定义
std::map<const char*, std::map<const char*, ofImage*> > ksResource::imageList;
std::map<const char*, std::map<const char*, ofShader*> > ksResource::shaderList;
std::map<const char*, std::map<const char*, ofSoundPlayer*> > ksResource::musicList;
std::map<const char*, std::map<const char*, EventToSound*> > ksResource::ksMusicList;
std::map<const char*, std::map<const char*, ofVideoPlayer*> > ksResource::videoList;
std::map<const char*, std::map<const char*, ofTrueTypeFont*> > ksResource::fontList;

ofVideoGrabber *ksResource::camera = NULL;

ksResource::ksResourceType ksResource::resourceType = KS_RESOURCE_CAMERA;

const char* newChar(const char* c, int size = 32)
{
	char* temp = new char[size];
	strcpy(temp, c);
	return temp;
}

// 不可删除 不可复制 不可自己创建实例
//ksResource::ksResource()
//{
	// imageList最多不超过maxCounts
	//imageList.resize(KS_TYPE_MAXCOUNTS);
	//shaderList.resize(KS_TYPE_MAXCOUNTS);
//}

//ksResource* ksResource::getInstance()
//{
//    static ksResource temp;
//    return &temp;
//}


void ksResource::update()
{
	switch (resourceType)
	{
	case KS_RESOURCE_CAMERA:
		return getCamera()->update();

	case KS_RESOURCE_VIDEO:
    {
        ofVideoPlayer *video = getVideo();
        if(!video->isPlaying())
            video->play();
            
		return video->update();
    }
	case KS_RESOURCE_IMAGE:
	default:
		break;
	}
}

void ksResource::setResource(ksResourceType type)
{
    ksResource::resourceType = type;
}

void ksResource::changeResource()
{
    switch (resourceType)
    {
        case KS_RESOURCE_CAMERA:
            resourceType = KS_RESOURCE_VIDEO;
            break;
            
        case KS_RESOURCE_VIDEO:
            getVideo()->stop();
            resourceType = KS_RESOURCE_IMAGE;
            break;
            
        case KS_RESOURCE_IMAGE:
            resourceType = KS_RESOURCE_CAMERA;
            break;
            
        default:
            break;
    }
}

ofBaseDraws* ksResource::getResource()
{
    switch (resourceType)
    {
        case KS_RESOURCE_IMAGE:
            return (ofBaseDraws*)getImage();
            
        case KS_RESOURCE_CAMERA:
            return (ofBaseDraws*)getCamera();
            
        case KS_RESOURCE_VIDEO:
            return (ofBaseDraws*)getVideo();
            
        default:
            ksLog("Error: 灾难性错误, 系统当前资源类型有误, 请寻找框架作者上官宾宾解决此问题\n");
            return NULL;
    }
}

bool ksResource::addShader(const char* ksName, const char* fileName, ofShader *shader)
{
	// 找到当前万花筒的资源空间
	for(std::map<const char*, std::map<const char*, ofShader*> >::iterator it = shaderList.begin(); it != shaderList.end(); ++it)
	{
		// 指定万花筒类型已找到
		// 在指定的资源空间中寻找
		if(!strcmp(it->first, ksName))
		{
			for(std::map<const char*, ofShader*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				if(!strcmp(it2->first, fileName))
				{
					// 已添加过该资源
					ksLog("Warning: 万花筒\"%s\"中Shader\"%s\"已存在\n", ksName, fileName);
					return false;
				}
			}

			// 这里若是直接向map中插入fileName会出现指针重定向 也就是map中存放的指针会重新指向下一次循环中的字符常量
			it->second.insert(std::map<const char*, ofShader*>::value_type(newChar(fileName), shader));
			ksLog("Success: 添加Shader\"%s\"成功\n", fileName);
			return true;
		}
	}

	// 资源空间还没有被添加
	std::map<const char*, ofShader*>* shaderNameList = new std::map<const char*, ofShader*>;

	shaderNameList->insert(std::map<const char*, ofShader*>::value_type(newChar(fileName), shader));

	shaderList.insert(std::map<const char*, std::map<const char*, ofShader*> >::value_type(newChar(ksName), *shaderNameList));

	ksLog("Success: 向系统中添加万花筒\"%s\"的资源空间成功, 并添加了Shader\"%s\"\n", ksName, fileName);

	return true;
}

bool ksResource::addImage(const char* ksName, const char* fileName, ofImage *image)
{
	// 找到当前万花筒的资源空间
	for(std::map<const char*, std::map<const char*, ofImage*> >::iterator it = imageList.begin(); it != imageList.end(); ++it)
	{
		if(!strcmp(it->first, ksName))
		{
			// 指定万花筒类型已找到
			// 在指定的资源空间中寻找
			for(std::map<const char*, ofImage*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				if(!strcmp(it2->first, fileName))
				{
					// 已添加过该资源
					ksLog("Warning: 万花筒\"%s\"中Image\"%s\"已存在\n", ksName, fileName);
					return false;
				}
			}

			// 这里若是直接向map中插入fileName会出现指针重定向 也就是map中存放的指针会重新指向下一次循环中的字符常量
			it->second.insert(std::map<const char*, ofImage*>::value_type(newChar(fileName), image));
			ksLog("Success: 添加Image\"%s\"成功\n", fileName);
			return true;
		}
	}

	// 资源空间还没有被添加
	std::map<const char*, ofImage*>* imageNameList = new std::map<const char*, ofImage*>;

	imageNameList->insert(std::map<const char*, ofImage*>::value_type(newChar(fileName), image));

	imageList.insert(std::map<const char*, std::map<const char*, ofImage*> >::value_type(newChar(ksName), *imageNameList));

	ksLog("Success: 向系统中添加万花筒\"%s\"的资源空间成功, 并添加了Image\"%s\"\n", ksName, fileName);

	return true;
}

bool ksResource::addMusic(const char *ksName, const char *fileName, ofSoundPlayer *music)
{
    // 找到当前万花筒的资源空间
    for(std::map<const char*, std::map<const char*, ofSoundPlayer*> >::iterator it = musicList.begin(); it != musicList.end(); ++it)
    {
        if(!strcmp(it->first, ksName))
        {
            // 指定万花筒类型已找到
            // 在指定的资源空间中寻找
            for(std::map<const char*, ofSoundPlayer*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if(!strcmp(it2->first, fileName))
                {
                    // 已添加过该资源
                    ksLog("Warning: 万花筒\"%s\"中Music\"%s\"已存在\n", ksName, fileName);
                    return false;
                }
            }
            
            // 这里若是直接向map中插入fileName会出现指针重定向 也就是map中存放的指针会重新指向下一次循环中的字符常量
            it->second.insert(std::map<const char*, ofSoundPlayer*>::value_type(newChar(fileName), music));
            ksLog("Success: 添加Music\"%s\"成功\n", fileName);
            return true;
        }
    }
    
    // 资源空间还没有被添加
    std::map<const char*, ofSoundPlayer*>* musicNameList = new std::map<const char*, ofSoundPlayer*>;
    
    musicNameList->insert(std::map<const char*, ofSoundPlayer*>::value_type(newChar(fileName), music));
    
    musicList.insert(std::map<const char*, std::map<const char*, ofSoundPlayer*> >::value_type(newChar(ksName), *musicNameList));
    
    ksLog("Success: 向系统中添加万花筒\"%s\"的资源空间成功, 并添加了Music\"%s\"\n", ksName, fileName);
    
    return true;
}

bool ksResource::addKsMusic(const char *ksName, const char *fileName, EventToSound *music)
{
    // 找到当前万花筒的资源空间
    for(std::map<const char*, std::map<const char*, EventToSound*> >::iterator it = ksMusicList.begin(); it != ksMusicList.end(); ++it)
    {
        if(!strcmp(it->first, ksName))
        {
            // 指定万花筒类型已找到
            // 在指定的资源空间中寻找
            for(std::map<const char*, EventToSound*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if(!strcmp(it2->first, fileName))
                {
                    // 已添加过该资源
                    ksLog("Warning: 万花筒\"%s\"中Music\"%s\"已存在\n", ksName, fileName);
                    return false;
                }
            }
            
            // 这里若是直接向map中插入fileName会出现指针重定向 也就是map中存放的指针会重新指向下一次循环中的字符常量
            it->second.insert(std::map<const char*, EventToSound*>::value_type(newChar(fileName), music));
            ksLog("Success: 添加Music\"%s\"成功\n", fileName);
            return true;
        }
    }
    
    // 资源空间还没有被添加
    std::map<const char*, EventToSound*>* musicNameList = new std::map<const char*, EventToSound*>;
    
    musicNameList->insert(std::map<const char*, EventToSound*>::value_type(newChar(fileName), music));
    
    ksMusicList.insert(std::map<const char*, std::map<const char*, EventToSound*> >::value_type(newChar(ksName), *musicNameList));
    
    ksLog("Success: 向系统中添加万花筒\"%s\"的资源空间成功, 并添加了Music\"%s\"\n", ksName, fileName);
    
    return true;
}

bool ksResource::addFont(const char *ksName, const char *fileName, ofTrueTypeFont *font)
{
    // 找到当前万花筒的资源空间
    for(std::map<const char*, std::map<const char*, ofTrueTypeFont*> >::iterator it = fontList.begin(); it != fontList.end(); ++it)
    {
        if(!strcmp(it->first, ksName))
        {
            // 指定万花筒类型已找到
            // 在指定的资源空间中寻找
            for(std::map<const char*, ofTrueTypeFont*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if(!strcmp(it2->first, fileName))
                {
                    // 已添加过该资源
                    ksLog("Warning: 万花筒\"%s\"中Font\"%s\"已存在\n", ksName, fileName);
                    return false;
                }
            }
            
            // 这里若是直接向map中插入fileName会出现指针重定向 也就是map中存放的指针会重新指向下一次循环中的字符常量
            it->second.insert(std::map<const char*, ofTrueTypeFont*>::value_type(newChar(fileName), font));
            ksLog("Success: 添加Font\"%s\"成功\n", fileName);
            return true;
        }
    }
    
    // 资源空间还没有被添加
    std::map<const char*, ofTrueTypeFont*>* fontNameList = new std::map<const char*, ofTrueTypeFont*>;
    
    fontNameList->insert(std::map<const char*, ofTrueTypeFont*>::value_type(newChar(fileName), font));
    
    fontList.insert(std::map<const char*, std::map<const char*, ofTrueTypeFont*> >::value_type(newChar(ksName), *fontNameList));
    
    ksLog("Success: 向系统中添加万花筒\"%s\"的资源空间成功, 并添加了Font\"%s\"\n", ksName, fileName);
    
    return true;
}

bool ksResource::addVideo(const char *ksName, const char *fileName, ofVideoPlayer *video)
{
    // 找到当前万花筒的资源空间
    for(std::map<const char*, std::map<const char*, ofVideoPlayer*> >::iterator it = videoList.begin(); it != videoList.end(); ++it)
    {
        if(!strcmp(it->first, ksName))
        {
            // 指定万花筒类型已找到
            // 在指定的资源空间中寻找
            for(std::map<const char*, ofVideoPlayer*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if(!strcmp(it2->first, fileName))
                {
                    // 已添加过该资源
                    ksLog("Warning: 万花筒\"%s\"中Video\"%s\"已存在\n", ksName, fileName);
                    return false;
                }
            }
            
            // 这里若是直接向map中插入fileName会出现指针重定向 也就是map中存放的指针会重新指向下一次循环中的字符常量
            it->second.insert(std::map<const char*, ofVideoPlayer*>::value_type(newChar(fileName), video));
            ksLog("Success: 添加Video\"%s\"成功\n", fileName);
            return true;
        }
    }
    
    // 资源空间还没有被添加
    std::map<const char*, ofVideoPlayer*>* videoNameList = new std::map<const char*, ofVideoPlayer*>;
    
    videoNameList->insert(std::map<const char*, ofVideoPlayer*>::value_type(newChar(fileName), video));
    
    videoList.insert(std::map<const char*, std::map<const char*, ofVideoPlayer*> >::value_type(newChar(ksName), *videoNameList));
    
    ksLog("Success: 向系统中添加万花筒\"%s\"的资源空间成功, 并添加了Video\"%s\"\n", ksName, fileName);
    
    return true;
}

bool ksResource::addCamera(ofVideoGrabber *camera)
{
    if(camera)
    {
        ksResource::camera = camera;
        ksLog("Success: 摄像头已成功添加\n");
        return true;
    }
    else
        return false;
}

ofShader* ksResource::getShader(const char* ksName, const char* shaderName)
{
	// 找到当前万花筒的资源空间
	for(std::map<const char*, std::map<const char*, ofShader*> >::iterator it = shaderList.begin(); it != shaderList.end(); ++it)
	{
		if(!strcmp(it->first, ksName))
		{
			// 指定万花筒类型已找到
			// 在指定的资源空间中寻找
			for(std::map<const char*, ofShader*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				if(!strcmp(it2->first, shaderName))
				{
					return it2->second;
				}
			}

			ksLog("Warning: 在资源空间\"%s\"中寻找Shader\"%s\"失败\n", ksName, shaderName);
			return NULL;
		}
	}

	ksLog("Warning: 搜索Shader\"%s\"时, 未能找到类型%s万花筒\n", shaderName, ksName);
	return NULL;
}

ofImage* ksResource::getImage()
{
	// 特殊对待
	return getImage(KS_DEFAULT_NAME, KS_DEFAULT_NAME);
}

ofImage* ksResource::getImage(const char* ksName, const char* imageName)
{
	// 找到当前万花筒的资源空间
	for(std::map<const char*, std::map<const char*, ofImage*> >::iterator it = imageList.begin(); it != imageList.end(); ++it)
	{
		if(!strcmp(it->first, ksName))
		{
			// 指定万花筒类型已找到
			// 在指定的资源空间中寻找
			for(std::map<const char*, ofImage*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
			{
				if(!strcmp(it2->first, imageName))
				{
					return it2->second;
				}
			}

			ksLog("Warning: 在资源空间\"%s\"中寻找Image\"%s\"失败\n", ksName, imageName);
			return NULL;
		}
	}

	ksLog("Warning: 搜索Image\"%s\"时, 未能找到类型%s万花筒\n", imageName, ksName);
	return NULL;
}

ofSoundPlayer* ksResource::getMusic()
{
    // 特殊对待
    return getMusic(KS_DEFAULT_NAME, KS_DEFAULT_NAME);
}

ofSoundPlayer* ksResource::getMusic(const char *ksName, const char *musicName)
{
    // 找到当前万花筒的资源空间
    for(std::map<const char*, std::map<const char*, ofSoundPlayer*> >::iterator it = musicList.begin(); it != musicList.end(); ++it)
    {
        if(!strcmp(it->first, ksName))
        {
            // 指定万花筒类型已找到
            // 在指定的资源空间中寻找
            for(std::map<const char*, ofSoundPlayer*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if(!strcmp(it2->first, musicName))
                {
                    return it2->second;
                }
            }
            
            ksLog("Warning: 在资源空间\"%s\"中寻找Music\"%s\"失败\n", ksName, musicName);
            return NULL;
        }
    }
    
    ksLog("Warning: 搜索Music\"%s\"时, 未能找到类型%s万花筒\n", musicName, ksName);
    return NULL;
}

EventToSound* ksResource::getKsMusic()
{
    // 特殊对待
    return getKsMusic(KS_DEFAULT_NAME, KS_DEFAULT_NAME);
}

EventToSound* ksResource::getKsMusic(const char *ksName, const char *musicName)
{
    // 找到当前万花筒的资源空间
    for(std::map<const char*, std::map<const char*, EventToSound*> >::iterator it = ksMusicList.begin(); it != ksMusicList.end(); ++it)
    {
        if(!strcmp(it->first, ksName))
        {
            // 指定万花筒类型已找到
            // 在指定的资源空间中寻找
            for(std::map<const char*, EventToSound*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if(!strcmp(it2->first, musicName))
                {
                    return it2->second;
                }
            }
            
            ksLog("Warning: 在资源空间\"%s\"中寻找Music\"%s\"失败\n", ksName, musicName);
            return NULL;
        }
    }
    
    ksLog("Warning: 搜索Music\"%s\"时, 未能找到类型%s万花筒\n", musicName, ksName);
    return NULL;
}

ofVideoPlayer* ksResource::getVideo()
{
    return getVideo(KS_DEFAULT_NAME, KS_DEFAULT_NAME);
}

ofVideoPlayer* ksResource::getVideo(const char *ksName, const char *videoName)
{
    // 找到当前万花筒的资源空间
    for(std::map<const char*, std::map<const char*, ofVideoPlayer*> >::iterator it = videoList.begin(); it != videoList.end(); ++it)
    {
        if(!strcmp(it->first, ksName))
        {
            // 指定万花筒类型已找到
            // 在指定的资源空间中寻找
            for(std::map<const char*, ofVideoPlayer*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if(!strcmp(it2->first, videoName))
                {
                    return it2->second;
                }
            }
            
            ksLog("Warning: 在资源空间\"%s\"中寻找Video\"%s\"失败\n", ksName, videoName);
            return NULL;
        }
    }
    
    ksLog("Warning: 搜索Video\"%s\"时, 未能找到类型%s万花筒\n", videoName, ksName);
    return NULL;
}

ofVideoGrabber* ksResource::getCamera()
{
    return camera;
}

ofTrueTypeFont* ksResource::getFont()
{
    return getFont(KS_DEFAULT_NAME, KS_DEFAULT_NAME);
}

ofTrueTypeFont* ksResource::getFont(const char *ksName, const char* fontName)
{
    // 找到当前万花筒的资源空间
    for(std::map<const char*, std::map<const char*, ofTrueTypeFont*> >::iterator it = fontList.begin(); it != fontList.end(); ++it)
    {
        if(!strcmp(it->first, ksName))
        {
            // 指定万花筒类型已找到
            // 在指定的资源空间中寻找
            for(std::map<const char*, ofTrueTypeFont*>::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
            {
                if(!strcmp(it2->first, fontName))
                {
                    return it2->second;
                }
            }
            
            ksLog("Warning: 在资源空间\"%s\"中寻找Video\"%s\"失败\n", ksName, fontName);
            return NULL;
        }
    }
    
    ksLog("Warning: 搜索Video\"%s\"时, 未能找到类型%s万花筒\n", fontName, ksName);
    return NULL;
}

