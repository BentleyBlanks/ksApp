#include <scopes/ksYangsu/ksYangsu.h>

#include <ks/utility/ksSettings.h>
#include <ks/base/ksResource.h>

ksRegisterClass(ksYangsu);

ksYangsu::ksYangsu()
{

	ofDisableArbTex(); 

	ysMesh.addVertex(
		ofPoint(-1.0f,0.5f*sin(PI/3.0f)));
	ysMesh.addVertex(
		ofPoint(1.0f,1.5f*sin(PI/3.0f)));

	ysMesh.addTexCoord(ofVec2f(0,1));
	ysMesh.addTexCoord(ofVec2f(1,1));

	ofIndexType ids[6] =
	{
		6,0,1,
		6,1,2
	};
	ysMesh.addIndices(ids,6);


	T =0;
}

ksYangsu::~ksYangsu()
{

}

void ksYangsu::init()
{
	//gui->addLabel("HelixLbl");

	speed= gui->addSlider("speed", -180.0, 180.0, 30.0);
	posx = gui->addSlider("posx", -300.0, 300.0, 250.0);
	posy = gui->addSlider("posy", -300.0, 300.0, 300.0);
	length = gui->addSlider("length", -800.0, 800.0, 300.0);
	width = gui->addSlider("width", -800.0, 800.0, 600.0);
	number = gui->addSlider("number", 1.0, 18.0, 10.0);
	direction = gui->addSlider("direction", -1.0, 1.0, 0.6);

	mode1 = gui->addSlider("mode1", -5.0, 5.0, 3.0);
	mode2 = gui->addSlider("mode2", 1.0, 18.0, 12.0);
}

void ksYangsu::draw(int x, int y, int width, int height)
{
    resources = ksResource::getResource();

    ofImage *back = ksResource::getImage();
    ofImage *user = ksResource::getImage("ksYAngsu", "logo.png");
    ofShader *shader = ksResource::getShader("ksYangSu", "A");
    
	m = ofGetElapsedTimef();
    //ofPushMatrix();
	//ofBackground(200,200,200);
	ofTranslate(width/2,height/2);

	if(resources==NULL)
		return;

	if(!F.isAllocated())
	{
		F.allocate(resources->getWidth(),
			resources->getHeight(),
			GL_RGBA);
	}	

	F.begin();
	ofClear(0,0,0,0);
	resources->draw(0,0,
		F.getWidth(),F.getHeight());
	F.end();

	ofPushMatrix();
	ofPushStyle();
	ofScale(width/10,height/10,1.0f);

	ofTexture T = F.getTextureReference();

	T.bind();

	float R = mode1->getValue()*sin(PI/6);
	float Theta = m;	
	for(int i=0;i<mode2->getValue();i++)
	{
		ofPoint P(R*cos(Theta), R*sin(Theta));
		ofTranslate(P);
		ysMesh.draw();
		ofTranslate(-P);

		Theta += PI/6;
	}
	T.unbind();

	ofSetColor(ofColor::black);

	ofPopMatrix();
	ofPopStyle();

	for(int i=0;i<8;i++)
		kuosan(resources);

    //ofPopMatrix();
}

void ksYangsu::kuosan(ofBaseDraws *pDraws )
{
	huanrao(pDraws);
	ofScale(0.5,0.5,1.0f);
}

void ksYangsu::huanrao(ofBaseDraws *pDraws)
{

	for(int i=0;i<number->getValue();i++)
	{
		pDraws->draw(posx->getValue(),posy->getValue(),length->getValue(),width->getValue());
		ofRotate(speed->getValue()*m*direction->getValue());
	}

}

void ksYangsu::update(float dt)
{
	T=ofGetElapsedTimef();

	vector<ofVec2f> TC = 
		ysMesh.getTexCoords();

	int NumTC = TC.size();

}