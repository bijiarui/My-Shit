#pragma once
#ifndef _OPTION_LAYER_H_
#define _OPTION_LAYER_H_
#include "SceneManager.h"
#include "cocos2d.h"
USING_NS_CC;
class OptionLayer :public Layer {
public:
	SceneManager * tsm;
public:
	CREATE_FUNC(OptionLayer);
	virtual bool init();
	void menuCallBack(Ref *pSender);
};


#endif // _OPTION_LAYER_H_