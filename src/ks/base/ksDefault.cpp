#include <ks/base/ksDefault.h>
#include <ks/utility/ksLog.h>
#include <ks/base/ksResource.h>
#include <ks/utility/ksSettings.h>



ksDefault::ksDefault()
{
	//resources = ksResource::getInstance();

	init();
}

void ksDefault::init()
{
    // 这里都是硬编码 早晚有一天可能出问题……
	ksLog("--------------------------System--------------------------\n");

	ofImage *image = new ofImage();
	if(image->loadImage("default/image/default.jpg"))
	{
		ksResource::addImage(KS_DEFAULT_NAME, KS_DEFAULT_NAME, image);
		ksLog("System: 成功加载默认配置图\n");
	}
	else
	{
		ksLog("Warning: 未能找到默认图\n");
	}

	ofVideoPlayer *video = new ofVideoPlayer();
	if(video->loadMovie("default/video/default.mov"))
	{
		ksResource::addVideo(KS_DEFAULT_NAME, KS_DEFAULT_NAME, video);
		ksLog("System: 成功加载默认配置视频\n");
	}
	else
	{
		ksLog("Warning: 未能找到默认视频\n");
	}
    
    ofTrueTypeFont *font = new ofTrueTypeFont();
    if(font->loadFont("default/font/ksFont.otf", 14))
    {
        ksResource::addFont(KS_DEFAULT_NAME, KS_DEFAULT_NAME, font);
        ksLog("Sysytem: 成功加载默认配置字体 字体大小为14");
    }
    else
        ksLog("Warning: 未能找到默认字体");
    
    // music
    EventToSound *sfx = new EventToSound();
    EventToSound *music = new EventToSound();
    
    sfx->init("default/music/sfxList.xml");
    sfx->setVolume(0.0);
    
    music->init("default/music/music.xml");
    music->setVolume(0.0);
    music->play();
    ksResource::addKsMusic(KS_DEFAULT_NAME, KS_DEFAULT_NAME, sfx);
    ksLog("System: 成功加载bgm&sfx");
}

ksDefault* ksDefault::getInstance()
{
	static ksDefault temp;
	return &temp;
}
