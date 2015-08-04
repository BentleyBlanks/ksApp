# ksApp
一款集结了众人力量完成的万花筒项目，可较美观的展示各型各色万花筒的样式，可较方便的后期增添全新样式的万花筒。

本程序框架为2.0版本，基于Openframworks完成。

##截图
![image](https://github.com/BentleyBlanks/ksApp/blob/master/screenshot/screenshot-1.jpg)

![image](https://github.com/BentleyBlanks/ksApp/blob/master/screenshot/screenshot-2.jpg)

##构建说明
1.```依赖项```addon已在dependency文件夹中全部给出，只需像往常一样在OF工程中包含或者生成时直接给定即可

2.支持XCode，Visual Studio 2012（受OF框架的制约，2012以上版本暂时不支持），CodeBlock等。需要注意的是，电脑中必须要装有QuickTime，摄像头可选。

3.data文件夹为200M左右，已压缩至80M打包上传到[百度云](http://pan.baidu.com/s/1kT1UALh)

##特色介绍
1.本框架使用了C++反射技术，因此任何外来万花筒只需要继承ksBase，并向框架注册自身即可
```cpp
-----------------ksXXX.h-----------------
#include <ks/base/ksBase.h>

class ksXXX : public ksBase
{
public:
    // 必须实现的纯虚函数
    virtual void init();
    virtual void update(float dt);
    virtual void draw(int x, int y, int width, int height);
  
    // 可选实现基类中部分虚函数
    virtual void keyPressed( int key );
    virtual void keyReleased( int key );
    
    virtual void mouseMoved( int x, int y );
    virtual void mouseDragged( int x, int y, int button );
    virtual void mousePressed( int x, int y, int button );
    virtual void mouseReleased(int x, int y, int button );
};

-----------------ksXXX.cpp-----------------
// 向底层ksApp框架注册自身
// 如若不注册那么框架不会包含任何相关此万花筒的运行代码，也就不会显示在最终结果上
ksRegisterClass(ksXXX);

// 万花筒实际实现代码
...
```

2.所有万花筒都有如下默认用户文件夹位于```data/ks/```
---font
---images
---ksXXX.xml
---music
---shader
---video

所有的资源文件都会被底层框架自动读取并分配内存，在万花筒只需这样获取相应资源即可
```cpp
// 推荐在初始化时就完成指针定向
void init()
{
    // 框架默认资源
    ofBaseDraws *res = ksResource::getResource();

    // 用户自定义图片资源
    ofImage* img = ksResource::getImage();

    // 用户自定义音乐资源
    ofSoundPlayer* music = ksResource::getMusic();

    // 系统关联配乐
    EventToSound* sound = ksResource::getKsMusic();

    // 用户自定义视频资源
    ofVideoPlayer* video = ksResource::getVideo();

    // 摄像头资源
    ofVideoGrabber* cam = ksResource::getCamera();

    // shader资源需要注意的是必须成对出现，且后缀需为.frag .vert
    ofShader* shader = ksResource::getShader(arguments);

    // 用户自定义字体资源
    ofTrueTypeFont* font = ksResource::getFont();
}
```

函数参数```const char *ksName, const char* resName```分别代表了当前万花筒名，资源名，可用于获取指定用户的资源，因此跨用户获取资源也是可行的。

3.需要注意的是，除非是非常必要的内存消耗需要自行分配以外，```尽量不要自行分配额外内存```，其余所有的内存都会交给ksApp保管，这样可以充分保证内存不存在泄露的问题。

4.Gui方面也不需要用户自行分配内存，可直接拿来使用。
```cpp
// gui为基类ksBase自带，会在初始化过程中直接分配完毕，这里只需add即可正常显示
gui->addButton();

gui->addSlider();
```

5.目前支持Mac, Windows, iOS。iOS设备上因为是为iPad设计的，尽管兼容iPhone但实际效果并不出众，因此还是推荐使用iPad做实际的测试。

6.支持第三方开发万花筒给ksApp（当然了，并没有什么卵报酬）方式就是需要向底层框架注册，仅此而已。

##使用说明
1.因为较为容易上手，因此可以0成本自学

##关于作者
```cpp
int 官某某 = "Bingo";

int[] 众万花筒作者 = {"SM1201", "SM1202", "SM1203", "SM1204"};
```

