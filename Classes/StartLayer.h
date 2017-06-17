#pragma once
#ifndef _START_LAYER_H_
#define _START_LAYER_H_
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class StartLayer :public Layer {
public:
	SceneManager *tsm;
public:
	CREATE_FUNC(StartLayer);
	virtual bool init();
	void menuCallBack(Ref *pSender);
};

#endif 