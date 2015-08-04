/**********************************************************************************************//**
* \姓名 柯珺
* \学号 1030512120
* \组	 盛凯
*
* \特色 示范具有3个输入源的万花筒
初始图像为螺旋式阵列，可以根据鼠标拖拽实现图像位置的变换，而且位置变换的基准点可以通过“a”和“z”进行选择
**************************************************************************************************/
#ifndef ksTaiyan12120_H
#define ksTaiyan12120_H


#include <ks/base/ksBase.h>


class ksTaiyan12120 : public ksBase {

public:
    
    ksTaiyan12120();
    ~ksTaiyan12120();
    
    virtual void init();
    virtual void draw(int x, int y, int w, int h );
    
    virtual void drag( float x,float y );
    
    //virtual void keyPressed(int key);
    virtual void release( float x, float y );
    
    virtual void update( float dt );
    
    virtual void mouseDragged( int x, int y, int button );
    virtual void mouseReleased(int x, int y, int button );
    
    ofTexture texture;
    ofPoint p[4]; //Corners
    
    
private:
    void drawKaleido4Leaves( ofBaseDraws* pDraws );
    //void draw1Leaf( ofPtr<ofBaseDraws> pDraws );
    
private:
    void setupI();
    void setupI_byFor();
    void setupI_byLoadImage();
    void setupVideoGrabber();
    void setupVideoPlayer();
    
    void updateVideoGrabber();
    //void drawKaleido4Leaves(ofBaseDraws* Src);
    
private:
    // ---------- setting -------------//
    int Mode;
    
    
    // --------- Video Grabber ----------//
    ofVideoGrabber 		vidGrabber; // grab video
    unsigned char * 	videoInverted; // store inverted video
    ofTexture			videoTexture; // store inverted video
    int 				camWidth;  // width of video
    int 				camHeight; // height of video
    
    // -------- Video Player ---------------//
    ofVideoPlayer 		*fingerMovie;
    bool                frameByframe;
    
    // ----------- ofFbo -------------------//
    ofFbo F;
    
};
    
#endif

