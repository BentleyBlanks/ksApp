#ifndef KS_RESOURCE_H
#define KS_RESOURCE_H

#include <ofMain.h>
#include <ks/base/ksSoundPlayer.h>
// 简单的数据捆绑
//class ksImage
//{
//public:
//	ofImage *image;
//	char name[32];
//};
//
//class ksShader
//{
//public:
//    ofShader *shader;
//    char name[32];
//};
//
//class ksImageList
//{
//public:
//    vector<ksImage*> images;
//};
//
//class ksShaderList
//{
//public:
//    vector<ksShader*> shaders;
//};

class ksResource
{
public:
    enum ksResourceType
    {
        KS_RESOURCE_IMAGE = 0,
        KS_RESOURCE_CAMERA,
        KS_RESOURCE_VIDEO,
        
        KS_RESOURCE_MAX_COUNT
    };
    //static ksResource* getInstance();
    //ksResource();
    
    // 返回公共资源(可切换为视频 图片 摄像头的资源)
    static ofBaseDraws* getResource();
    
    static ofShader* getShader(const char *ksName, const char *shaderName);
    
    // 获取系统默认图
    static ofImage* getImage();
    // 获取指定万花筒类型下的图片系
    static ofImage* getImage(const char *ksName, const char* imageName);
    
    // 获取指定万花筒类型下的音乐资源
    static ofSoundPlayer* getMusic();
    
    static ofSoundPlayer* getMusic(const char *ksName, const char *musicName);
    
    // 系统关联的配乐
    static EventToSound* getKsMusic();
    
    static EventToSound* getKsMusic(const char *ksName, const char *musicName);
    
    static ofVideoPlayer* getVideo();
    
    static ofVideoPlayer* getVideo(const char *ksName, const char *videoName);
    
    // 获取摄像头资源
    static ofVideoGrabber* getCamera();
    
    static ofTrueTypeFont* getFont();
    
    static ofTrueTypeFont* getFont(const char *ksName, const char* fontName);
    
    friend class ksController;
    friend class ksDefault;
    friend class ksApp;
    
    static ksResourceType resourceType;
private:
    static void update();
    
    // --!返回何种l类型是由资源中心确定
    static void setResource(ksResourceType resourceType);
    
    // 自动切换资源
    static void changeResource();
    
    // --!向资源中心添加资源由系统调用
    // 指定一个万花筒类型添加资源
    static bool addShader(const char *ksName, const char *fileName, ofShader *shader);
    
    static bool addImage(const char *ksName, const char *fileName, ofImage *image);
    
    static bool addKsMusic(const char *ksName, const char *fileName, EventToSound *music);
    
    static bool addMusic(const char *ksName, const char *fileName, ofSoundPlayer *music);
    
    static bool addVideo(const char *ksName, const char *fileName, ofVideoPlayer *video);
    
    static bool addCamera(ofVideoGrabber *camera);
    
    static bool addFont(const char *ksName, const char *fileName, ofTrueTypeFont *font);
    
    // 不可删除 不可复制 不可自己创建实例
    //ksResource();
    //ksResource(const ksResource&){}
    //~ksResource(){}
    //ksResource& operator=(const ksResource& event) const{}
    
    // --!无需自行初始化的各项数据源
    // --!友元ksApp完成初始化工作
    // ksName -> 单独的资源空间map
    // fileName -> 单独的资源ofXXX
    static std::map<const char*, std::map<const char*, ofImage*> > imageList;
    static std::map<const char*, std::map<const char*, ofShader*> > shaderList;
    static std::map<const char*, std::map<const char*, EventToSound*> > ksMusicList;
    static std::map<const char*, std::map<const char*, ofSoundPlayer*> > musicList;
    static std::map<const char*, std::map<const char*, ofVideoPlayer*> > videoList;
    static std::map<const char*, std::map<const char*, ofTrueTypeFont*> > fontList;
    //static std::map<const char*, std::map<const char*, ofVideoGrabber*> > cameraList;
    static ofVideoGrabber *camera;
};


#endif
