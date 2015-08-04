#include <scopes/ksArovane/ksArovane.h>

#include <ks/utility/ksSettings.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksArovane);

ksArovane::ksArovane()
{
	
}

ksArovane::~ksArovane()
{

}

void ksArovane::init()
{
    ofDisableArbTex();
    
    HexagonMesh.addVertex(ofPoint(-1.0f,0));
    HexagonMesh.addVertex(ofPoint(-1.0f,1.0f));
    HexagonMesh.addVertex(ofPoint(0.0f,0));
    
    
    HexagonMesh.addTexCoord(ofVec2f(0,1));
    HexagonMesh.addTexCoord(ofVec2f(1,1));
    HexagonMesh.addTexCoord(ofVec2f(1,0));
    
    
    ofIndexType ids[3] =
    {
        0,1,2
        
    };
    HexagonMesh.addIndices(ids,3);
    
    Speed=5.0f;
    Rotation=0;
    
    ScalationX=0;
    ScalationY=0;
    number=4;
    bRandom=false;
    time = ofGetElapsedTimef();
}

void ksArovane::draw(int x, int y, int width, int height)
{
	ofBaseDraws *pDraw = ksResource::getResource();

	if(pDraw==NULL)
		return;

	if(!F.isAllocated())
		F.allocate(pDraw->getWidth(), pDraw->getHeight(), GL_RGBA);

	F.begin();
	ofClear(0,0,0,0);
	pDraw->draw(0,0,F.getWidth(),F.getHeight());
	F.end();

	/******随机******/
	if (bRandom)
	{
		TranslationX=ofRandom(0.0f,width);	
		TranslationY=ofRandom(0.0f,height);	
		My8roll();
	}
	/**/

	/******规律******/
	for (int m = 1; m < number; m++)
	{
		for (int n = 1; n < number; n++)
		{
			TranslationX=width*m/number;			
			TranslationY=height*n/number;			
			My8roll();
		}
	}	
}

void ksArovane::mousePressed( int x, int y, int button )
{
	/*******控制风车数的增减******/
	if (x<ofGetWidth()/2)
	{
		number--;
	}else
	{
		number++;
	}
	if (number<=2)
	{
		number =2;
	}

	/*******控制随机风车的出现与否******/
	if (y<ofGetHeight()/2)
	{
		bRandom=true;
	}else
	{
		bRandom=false;
	}
}

void ksArovane::update(float dt) 
{
	dt *= Speed;
	
	Rotation +=5* dt;

	if (ScalationX>=100&&ScalationY>=100)
	{
		ScalationX=0;
		ScalationY=0;
	}
	ScalationX += 5*dt;
	ScalationY += 5*dt;
}



void ksArovane::My8roll()
{
    ofPushStyle();
	ofPushMatrix();

	ofTranslate(TranslationX,TranslationY);
	ofScale(ScalationX,ScalationY,1.0f);
	ofRotate(Rotation);

	ofTexture T = F.getTextureReference();

	T.bind();//使用该纹理
	HexagonMesh.draw();

	float rot=45;
	for (int i = 0; i < 8; i++)
	{
		ofRotate(rot);
		HexagonMesh.draw();
		rot+=45;
	}
	T.unbind();//取消使用该纹理

	//ofSetColor(ofColor::black);

	ofPopMatrix();
	ofPopStyle();	
}