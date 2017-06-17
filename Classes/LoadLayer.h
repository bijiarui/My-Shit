#pragma once
#ifndef _LOAD_LAYER_H_
#define _LOAD_LAYER_H_
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;
class LoadLayer :public Layer {
public:
	SceneManager * tsm;
public:
	CREATE_FUNC(LoadLayer);
	virtual bool init();
	void onScheduleOnce(float dt);
};

#endif 
