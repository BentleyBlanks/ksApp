#include "ofxNodeAnimation.h"
#include "ofxStyleAnimation.h"

class ofxUIWidget;
class ofxUIAnimation
{
public:
	ofxUIAnimation();

	// 设定宿主Widget
	void setWidget(ofxUIWidget* widget);

	// 这里是深拷贝 并非简单的浅拷贝 因此动画对象可以重用
	void setNodeAnimation(ofxNodeAnimation* nodeAnimation);

	void setStyleAnimation(ofxStyleAnimation* styleAnimation);

	// 根据当前动画类型来更新宿主对象状态
	void update();

private:
	// 保留一宿主widget指针
	ofxUIWidget* widget;
	
	ofxNodeAnimation* animation;

	ofxStyleAnimation* styleAnimation;
};