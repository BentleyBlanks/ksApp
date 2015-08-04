/********************************************************************************** 
 
 Copyright (C) 2012 Syed Reza Ali (www.syedrezaali.com)
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of
 this software and associated documentation files (the "Software"), to deal in
 the Software without restriction, including without limitation the rights to
 use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 of the Software, and to permit persons to whom the Software is furnished to do
 so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
 **********************************************************************************/

#pragma once

#include "ofxUIWrapper.h"
#include "ofxUIDefines.h"

#ifndef OFX_UI_NO_XML
	#include "ofxXmlSettings.h"
#endif 
class ofxUIAnimation;

class ofxUIWidget           
{
public:
	ofxUIWidget();
	virtual ~ofxUIWidget();
	ofxUIWidget(const ofxUIWidget &other); // Mitchell Nordine 2/2/14
	virtual ofxUIWidget& operator=(const ofxUIWidget &other); // Mitchell Nordine 2/2/14
	
	virtual void initRect(float x = 0, float y = 0, float w = 0, float h = 0);
	virtual void initPaddingRect();
	virtual void calculatePaddingRect();
	
	virtual void setup(); 
	virtual void update();
	virtual void draw();
	
	// add drawing skin in the following draw*() fcns
	// 在下面的draw*()函数中增加了绘制皮肤的功能
	virtual void drawBack();
	virtual void drawOutline();
	virtual void drawOutlineHighlight();
	virtual void drawFill();
	virtual void drawFillHighlight();
	virtual void drawPadded();
	virtual void drawPaddedOutline();
	
#ifdef OFX_UI_TARGET_TOUCH
	void touchDown(float x, float y, int id);
	void touchMoved(float x, float y, int id);
	void touchUp(float x, float y, int id);
	void touchCancelled(float x, float y, int id);
	void touchDoubleTap(float x, float y, int id) {}
#endif

	virtual void mouseMoved(int x, int y ) {}
	virtual void mouseDragged(int x, int y, int button) {}
	virtual void mousePressed(int x, int y, int button) {}
	virtual void mouseReleased(int x, int y, int button) {}
	
	virtual void keyPressed(int key) {}
	virtual void keyReleased(int key) {}
	virtual void windowResized(int w, int h) {}           		
	
	void setTriggerType(ofxUITriggerType _triggerType);
	ofxUITriggerType getTriggerType();
	
	virtual void setParent(ofxUIWidget *_parent);
	virtual ofxUIWidget *getParent();
	
	virtual void setName(string _name);
	virtual string& getName();
	
	virtual void setModal(bool _modal);
	virtual bool isModal();
	
	virtual void setVisible(bool _visible);
	virtual bool isVisible();
	virtual void toggleVisible();
	
	virtual void setEmbedded(bool _embedded);
	virtual bool isEmbedded();
	
	void setID(int _id);
	int getID();
	virtual void setKind(ofxUIWidgetType _kind);
	virtual ofxUIWidgetType getKind();
	
	virtual bool isDraggable();
	virtual bool hasLabel();

	virtual void triggerEvent(ofxUIWidget *child);
	virtual void triggerSelf();
	virtual void stateChange();
	virtual bool isHit(float x, float y);
	
	virtual void addWidget(ofxUIWidget *widget);
	virtual void removeWidget(ofxUIWidget *widget);
	
	virtual void addEmbeddedWidget(ofxUIWidget *widget);
	virtual void clearEmbeddedWidgets();
	virtual int getEmbeddedWidgetsSize();
	ofxUIWidget *getEmbeddedWidget(int index);
	
	virtual void setState(int _state);
	virtual void setFont(ofxUIFont *_font);

	virtual void setPadding(float _padding);
	virtual float getPadding();
	
	virtual ofxUIRectangle* getRect();
	virtual ofxUIRectangle *getPaddingRect();
	virtual void setRectParent(ofxUIRectangle *_prect);
	
	virtual void setDrawPadding(bool _draw_padded_rect);
	virtual bool getDrawPadding();
	
	virtual void setDrawPaddingOutline(bool _draw_padded_rect_outline);
	virtual bool getDrawPaddingOutline();
	
	virtual void setDrawBack(bool _draw_back);
	virtual bool getDrawBack();
	
	virtual void setDrawOutline(bool _draw_outline);
	virtual bool getDrawOutline();
	
	virtual void setDrawFill(bool _draw_fill);
	virtual bool getDrawFill();
	
	virtual void setDrawFillHighLight(bool _draw_fill_highlight);
	virtual bool getDrawFillHighLight();
	
	virtual void setDrawOutlineHighLight(bool _draw_outline_hightlight);
	virtual bool getDrawOutlineHighLight();
	
	virtual void setColorBack(ofxUIColor _color_back);
	ofxUIColor& getColorBack();
	
	virtual void setColorOutline(ofxUIColor _color_outline);
	ofxUIColor& getColorOutline();
	
	virtual void setColorOutlineHighlight(ofxUIColor _color_outline_highlight);
	ofxUIColor& getColorOutlineHighlight();
	
	virtual void setColorFill(ofxUIColor _color_fill);
	ofxUIColor& getColorFill();
	
	virtual void setColorFillHighlight(ofxUIColor _color_fill_highlight);
	ofxUIColor& getColorFillHighlight();
	
	virtual void setColorPadded(ofxUIColor _color_padded_rect);
	ofxUIColor& getColorPadded();
	
	virtual void setColorPaddedOutline(ofxUIColor _color_padded_rect_outline);
	ofxUIColor& getColorPaddedOutline();

	virtual void addModalWidget(ofxUIWidget *widget);
	virtual void removeModalWidget(ofxUIWidget *widget);

	ofxUIWidget *getCanvasParent();
	
	virtual bool hasState();
	
	virtual bool getIsBindedToKey(int key); 
	virtual void bindToKey(int key);
	virtual void unbindToKey(int key);
	virtual void unbindAllKeys(); 

#ifndef OFX_UI_NO_XML
	virtual void saveState(ofxXmlSettings *XML);
	virtual void loadState(ofxXmlSettings *XML);
	
#endif

protected:
	void drawComponent( ofPtr<ofBaseDraws> &pDraw, ofxUIRectangle* r );
	
protected:
	ofxUIWidget *parent;
	ofxUIRectangle *rect;
	ofxUIFont *font;
	
	std::string name;                    
	ofxUIWidgetType kind; 
	bool visible;
	int ID;
	bool hit; 
	int state;
	ofxUITriggerType triggerType; 
	bool embedded;
	bool modal;
	
	bool draw_back;    
	bool draw_outline;
	bool draw_outline_highlight; 
	bool draw_fill; 
	bool draw_fill_highlight; 

	ofxUIColor color_back;
	ofxUIColor color_outline; 
	ofxUIColor color_outline_highlight;	
	ofxUIColor color_fill; 
	ofxUIColor color_fill_highlight; 

	float padding;                 
	ofxUIRectangle *paddedRect; 	

	bool draw_padded_rect; 
	bool draw_padded_rect_outline;     
	ofxUIColor color_padded_rect; 
	ofxUIColor color_padded_rect_outline;
	
	vector<ofxUIWidget *> embeddedWidgets; 

	bool bKeyHit;
	map<int, bool> keyBindings;
#ifdef OFX_UI_TARGET_TOUCH       
	int touchId;     
#endif
	// Ruimin Lyu -------------------------------------------------------------------//
	//--------- skin ---------------//
	// 增加了皮肤功能，
	// 在之前所有的draw*()函数中增加了绘制皮肤的逻辑分支
protected:
	ofPtr<ofBaseDraws> skin_padded;	
	ofPtr<ofBaseDraws> skin_padded_outline;
	ofPtr<ofBaseDraws> skin_back;	
	ofPtr<ofBaseDraws> skin_outline;	
	ofPtr<ofBaseDraws> skin_outline_highlight;
	ofPtr<ofBaseDraws> skin_fill;
	ofPtr<ofBaseDraws> skin_fill_highlight;

	ofxUIAnimation* uiAnimation;

public:
	ofPtr<ofBaseDraws> get_skin_padded() const { return skin_padded; }
	void set_skin_padded(ofPtr<ofBaseDraws> val) { skin_padded = val; }
	ofPtr<ofBaseDraws> get_skin_padded_outline() const { return skin_padded_outline; }
	void set_skin_padded_outline(ofPtr<ofBaseDraws> val) { skin_padded_outline = val; }
	ofPtr<ofBaseDraws> get_skin_back() const { return skin_back; }
	void set_skin_back(ofPtr<ofBaseDraws> val) { skin_back = val; }
	ofPtr<ofBaseDraws> get_skin_outline() const { return skin_outline; }
	void set_skin_outline(ofPtr<ofBaseDraws> val) { skin_outline = val; }
	ofPtr<ofBaseDraws> get_skin_outLine_highlight() const { return skin_outline_highlight; }
	void set_skin_outLine_highlight(ofPtr<ofBaseDraws> val) { skin_outline_highlight = val; }
	ofPtr<ofBaseDraws> get_skin_fill() const { return skin_fill; }
	void set_skin_fill(ofPtr<ofBaseDraws> val) { skin_fill = val; }
	ofPtr<ofBaseDraws> get_skin_fill_highlight() const { return skin_fill_highlight; }
	void set_skin_fill_highlight(ofPtr<ofBaseDraws> val) { skin_fill_highlight = val; }
	//---------------------------------------------------------------------- Ruimin Lyu //
	
	void setUIAnimation(ofxUIAnimation* uiAnimation);
};