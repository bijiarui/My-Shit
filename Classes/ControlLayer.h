#pragma once
#ifndef _CONTROL_LAYER_
#define _CONTROL_LAYER_
#include "cocos2d.h"
USING_NS_CC;

class ControlLayerDelegate
{
public:

	virtual void clickUp() = 0;
	virtual void clickDown() = 0;
	virtual void clickLeft() = 0;
	virtual void clickRight() = 0;
	virtual void clickA() =0;
	virtual void clickS() = 0;
	virtual void clickD() = 0;
	virtual void clickW() = 0;

};

class ControlLayer : public Layer
{
public:
	CREATE_FUNC(ControlLayer);
	virtual bool init();
	void setDelegate(ControlLayerDelegate *delegate) { m_delegate = delegate; }

private:
	ControlLayerDelegate *m_delegate;
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event);
};





#endif // !_CONTROL_LAYER_
