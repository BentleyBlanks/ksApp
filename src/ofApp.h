#pragma once

#include "ofMain.h"
#include <ks/ks.h>

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    virtual void mouseMoved( int x, int y );
    virtual void mouseDragged( int x, int y, int button );
    virtual void mousePressed( int x, int y, int button );
    virtual void mouseReleased(int x, int y, int button );
//    void touchDown(ofTouchEventArgs & touch);
//    void touchMoved(ofTouchEventArgs & touch);
//    void touchUp(ofTouchEventArgs & touch);
//    void touchDoubleTap(ofTouchEventArgs & touch);
//    void touchCancelled(ofTouchEventArgs & touch);

//    void lostFocus();
//    void gotFocus();
//    void gotMemoryWarning();
//    void deviceOrientationChanged(int newOrientation);
//    
//    void windowResized(int w, int h);
//    
//    void rotateToPortrait();
//    void rotateToPortraitUpSideDown();
//    void rotateToLandscapeLeft();
//    void rotateToLandscapeRight();
//    void toggleAutoRotation();
    
    ksApp ks;
    ofTrueTypeFont title;
    bool bAuto;
};
