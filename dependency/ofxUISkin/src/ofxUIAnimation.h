#include "ofxNodeAnimation.h"
#include "ofxStyleAnimation.h"

class ofxUIWidget;
class ofxUIAnimation
{
public:
	ofxUIAnimation();

	// �趨����Widget
	void setWidget(ofxUIWidget* widget);

	// ��������� ���Ǽ򵥵�ǳ���� ��˶��������������
	void setNodeAnimation(ofxNodeAnimation* nodeAnimation);

	void setStyleAnimation(ofxStyleAnimation* styleAnimation);

	// ���ݵ�ǰ����������������������״̬
	void update();

private:
	// ����һ����widgetָ��
	ofxUIWidget* widget;
	
	ofxNodeAnimation* animation;

	ofxStyleAnimation* styleAnimation;
};