#include "ofxUIAnimation.h"
#include "ofxUI.h"
#include "ofxRotate.h"
#include "ofxShake.h"
#include "ofxScale.h"

ofxUIAnimation::ofxUIAnimation()
{
	widget = NULL;
	animation = NULL;
	styleAnimation = NULL;
}

void ofxUIAnimation::update()
{
	if(!widget)
		return;

	if(animation)
	{
		static float initalX = widget->getRect()->x, initalY = widget->getRect()->y;
		static float initalWidth = widget->getRect()->width, initalHeight = widget->getRect()->height;

		animation->update();

		float angle = 0.0f;
		switch (animation->getType())
		{
		case ofxNodeAnimation::NODEANIMATION_ROTATE:
			//x = widget->getRect()->x;
			//y = widget->getRect()->y;
			angle = animation->getAng();

			widget->getRect()->x = initalX*cosf(angle) - initalY*sinf(angle);
			widget->getRect()->y = initalY*cosf(angle) + initalX*sinf(angle);

			break;
		case ofxNodeAnimation::NODEANIMATION_SCALE:
			widget->getRect()->width = initalWidth*animation->getScl();
			widget->getRect()->height = initalHeight*animation->getScl();
			cout << "(s:" << animation->getScl() << ")" << endl;
			break;
		case ofxNodeAnimation::NODEANIMATION_SHAKE:
			widget->getRect()->x = initalX + animation->getOffset().x;
			widget->getRect()->y = initalY + animation->getOffset().y;		
			//cout << "(x:" << widget->getRect()->x << ", y:" << widget->getRect()->y << ")" << endl;
			//cout << "(x:" << animation->getOffset().x << ", y:" << animation->getOffset().y << ")" << endl;

			break;
		default:
			break;
		}
	}

	if(styleAnimation)
	{
		styleAnimation->update();

		//static ofColor 
		//	inital_color_back = widget->getColorBack(), 
		//	inital_color_outline = widget->getColorOutline(), 
		//	inital_color_outline_highlight = widget->getColorOutlineHighlight(), 
		//	inital_color_fill = widget->getColorFill(), 
		//	inital_color_fill_highlight = widget->getColorFillHighlight(); 

		widget->getColorBack().a = styleAnimation->getAlpha();
		widget->getColorOutline().a = styleAnimation->getAlpha();
		widget->getColorOutlineHighlight().a = styleAnimation->getAlpha();
		widget->getColorFill().a = styleAnimation->getAlpha();
		widget->getColorFillHighlight().a = styleAnimation->getAlpha();
		widget->getColorPadded().a = styleAnimation->getAlpha();
		widget->getColorPaddedOutline().a = styleAnimation->getAlpha();
	}
}

void ofxUIAnimation::setNodeAnimation( ofxNodeAnimation* nodeAnimation )
{
	// 临时代码
	if(!nodeAnimation)
		return;

	//// 注意!这里是深拷贝
	//switch (nodeAnimation->getType())
	//{
	//case ofxNodeAnimation::NODEANIMATION_ROTATE:
	//	animation = new ofxRotate();
	//	break;
	//case ofxNodeAnimation::NODEANIMATION_SCALE:
	//	animation = new ofxScale();
	//	break;
	//case ofxNodeAnimation::NODEANIMATION_SHAKE:
	//	animation = new ofxShake();
	//	break;
	//default:
	//	break;
	//}

	//// 没有拷贝函数会出问题
	//(*animation) = (*nodeAnimation);

	animation = nodeAnimation;
}

void ofxUIAnimation::setWidget( ofxUIWidget* widget )
{
	this->widget = widget;
}

void ofxUIAnimation::setStyleAnimation( ofxStyleAnimation* styleAnimation )
{
	if(!styleAnimation)
		return;

	this->styleAnimation = styleAnimation;
}
