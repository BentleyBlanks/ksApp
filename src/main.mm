#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
    
    //ofAppiOSWindow * iOSWindow = new ofAppiOSWindow();
    
    //iOSWindow->enableRendererES2();
    //iOSWindow->enableAntiAliasing(4);
    //iOSWindow->enableRetina();
    // of与iOS 8的硬件朝向似乎有兼容问题
    //iOSWindow->enableHardwareOrientation();
    //iOSWindow->enableOrientationAnimation();
    
    ofSetupOpenGL(2048, 1536, OF_WINDOW);		// <-------- setup the GL context

    //cout << iOSWindow->getWindowPosition();

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
