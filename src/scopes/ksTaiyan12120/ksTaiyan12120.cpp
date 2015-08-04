
/**********************************************************************************************//**
* \姓名 柯珺
* \学号 1030512120
* \组	 盛凯
*
* \特色 示范具有3个输入源的万花筒
初始图像为螺旋式阵列，可以根据鼠标拖拽实现图像位置的变换，而且位置变换的基准点可以通过“a”和“z”进行选择
**************************************************************************************************/


#include <scopes/ksTaiyan12120/ksTaiyan12120.h>

#include <ks/utility/ksSettings.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksTaiyan12120);



int ind = 0;


ksTaiyan12120::ksTaiyan12120(){

}


ksTaiyan12120::~ksTaiyan12120(){

}



void ksTaiyan12120::init(){
    
    p[0].x = 100; p[0].y = 100;
    p[1].x = 300; p[1].y = 100;
    p[2].x = 300; p[2].y = 300;
    p[3].x = 100; p[3].y = 300;
    
    
    //setupI();
    //setupVideoGrabber();
    //setupVideoPlayer();
    
    Mode = 0;
}

//update
void ksTaiyan12120::update( float dt ){

	p[ ind ].x -=100*dt;
	p[ ind ].y +=100*dt;

	//updateVideoGrabber();
}


void ksTaiyan12120::draw(int x, int y, int w, int h){

	//ofClear(ofColor::white);
    
	ofBaseDraws *pDrawSrc = ksResource::getResource();
	
	
	if(0==Mode)
	{
		//drawKaleido4Leaves(&texture);
		//ofTranslate( ofGetWidth() / 10, ofGetHeight() / 2 );
		drawKaleido4Leaves(pDrawSrc);
	}

}
void ksTaiyan12120::drag( float x,float y ){
	p[0].x=x-500;
	p[3].y=y-500;
}
//
//void ksTaiyan12120::keyPressed(int key){
//	if('1'==key)
//	{
//		Mode = 0;
//	}
//	else if('2' == key)
//	{
//		Mode = 1;
//	}
//	else if('3' == key)
//	{
//		Mode = 2;
//	}
//	else if('4' == key)
//	{
//		Mode = 3;
//	}
//	else if('p' == key)
//	{
//		Mode = 4;
//	}
//	else if('a'==key){ ind = 0; }
//	else if('d'==key){ ind = 1; }
//	else if('w'==key){ ind = 2; }
//	else if('z'==key){ ind = 3; }
//	else if ( key == OF_KEY_LEFT ) { p[ ind ].x -= 10; }
//	else if ( key == OF_KEY_RIGHT ) { p[ ind ].x += 10; }
//	else if ( key == OF_KEY_UP ) { p[ ind ].y -= 10; }
//	else if ( key == OF_KEY_DOWN ) { p[ ind ].y += 10; }
//
//}
void ksTaiyan12120::release( float x, float y ){

}
void ksTaiyan12120::setupI(){
	ofLoadImage( texture, "Test.jpg" );
}
void ksTaiyan12120::setupI_byFor(){

}
void ksTaiyan12120::setupI_byLoadImage(){

}
void ksTaiyan12120::setupVideoGrabber(){
	camWidth 		= 320;	// try to grab at this size. 
	camHeight 		= 240;

	//we can now get back a list of devices. 
	vector<ofVideoDevice> devices = vidGrabber.listDevices();

	for(int i = 0; i < devices.size(); i++){
		cout << devices[i].id << ": " << devices[i].deviceName; 
		if( devices[i].bAvailable ){
			cout << endl;
		}else{
			cout << " - unavailable " << endl; 
		}
	}
	vidGrabber.setDeviceID(0);
	vidGrabber.setDesiredFrameRate(60);
	vidGrabber.initGrabber(camWidth,camHeight);

	videoInverted 	= new unsigned char[camWidth*camHeight*3];
	videoTexture.allocate(camWidth,camHeight, GL_RGB);	
	ofSetVerticalSync(true);
}
void ksTaiyan12120:: setupVideoPlayer(){
	frameByframe = false;
    fingerMovie = ksResource::getVideo();
}
void ksTaiyan12120::updateVideoGrabber(){
	vidGrabber.update();

	if (vidGrabber.isFrameNew()){
		int totalPixels = camWidth*camHeight*3;
		unsigned char * pixels = vidGrabber.getPixels();
		for (int i = 0; i < totalPixels; i++){
			videoInverted[i] = 255 - pixels[i];
		}
		videoTexture.loadData(videoInverted, camWidth,camHeight, GL_RGB);
	}
}

void ksTaiyan12120::drawKaleido4Leaves(ofBaseDraws* pDraws){
	for (int i=0; i<100; i++) {
		ofPushMatrix();
		//Translate system coordinates to screen center
		ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2 );
		//Rotate coordinate system on i * 15 degrees
		ofRotate( i * 15 );
		//Go right on 50 * i * 10 pixels
		//in rotated coordinate system
		ofTranslate( 50 + i * 10, 0 );
		//Scale coordinate system for decreasing drawing
		//image size
		float scl = 1.0 - i * 0.8 / 20.0;
		ofScale( scl, scl );
		//texture.draw( p[0], p[1], p[2], p[3] );

		pDraws->draw(p[0].x,p[1].y,p[2].x,p[3].y);
		//ofTranslate(ofGetWidth(), ofGetHeight());
		ofPopMatrix();
	}
}

void ksTaiyan12120::mouseDragged( int x, int y, int button )
{
    drag(x, y);
}

void ksTaiyan12120::mouseReleased(int x, int y, int button )
{
    release(x, y);
}