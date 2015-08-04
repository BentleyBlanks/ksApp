#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
    ofSetWindowShape(2048, 1536);
    //ofSetWindowShape(1024, 768);
    
    // --!能写出下面这种惊天地泣鬼神的天才代码世界上仅存的神童已经不多了
    // --!而我恰恰就是其中一位
    //rotateToPortrait();

    bAuto = true;
    ks.init();

    
    //rotateToLandscapeRight();
}

//--------------------------------------------------------------
void ofApp::update(){
    //rotateToPortrait();
    //rotateToLandscapeRight();
    
    ks.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ks.draw();
}

//--------------------------------------------------------------
void ofApp::exit(){

}

void ofApp::mouseMoved( int x, int y )
{
    
}

void ofApp::mouseDragged( int x, int y, int button )
{
    
}

void ofApp::mousePressed( int x, int y, int button )
{
    
}


void ofApp::mouseReleased(int x, int y, int button )
{
    
}

////--------------------------------------------------------------
//void ofApp::touchDown(ofTouchEventArgs & touch){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::touchMoved(ofTouchEventArgs & touch){
//
//}
//
////--------------------------------------------------------------
//void ofApp::touchUp(ofTouchEventArgs & touch){
//
//}
//
////--------------------------------------------------------------
//void ofApp::touchDoubleTap(ofTouchEventArgs & touch){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::touchCancelled(ofTouchEventArgs & touch){
//    
//}

////--------------------------------------------------------------
//void ofApp::windowResized(int w, int h){
//
//}

////--------------------------------------------------------------
//void ofApp::lostFocus(){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::gotFocus(){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::gotMemoryWarning(){
//    
//}
//
////--------------------------------------------------------------
//void ofApp::rotateToPortrait() {
//    ofSetOrientation(OF_ORIENTATION_DEFAULT);
//}
//
//void ofApp::rotateToPortraitUpSideDown() {
//    ofSetOrientation(OF_ORIENTATION_180);
//}
//
//void ofApp::rotateToLandscapeLeft() {
//    ofSetOrientation(OF_ORIENTATION_90_LEFT);
//}
//
//void ofApp::rotateToLandscapeRight() {
//    ofSetOrientation(OF_ORIENTATION_90_RIGHT);
//}
//
//void ofApp::toggleAutoRotation() {
//    bAuto = !bAuto;
//}
//
////--------------------------------------------------------------
//void ofApp::deviceOrientationChanged(int newOrientation){
//    if( bAuto && ((newOrientation == OF_ORIENTATION_90_LEFT) || (newOrientation == OF_ORIENTATION_90_RIGHT))) {
//        ofSetOrientation((ofOrientation)newOrientation);
//    }
//}