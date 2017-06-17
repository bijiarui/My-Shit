#pragma once
#ifndef _SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_
#include <iostream>
# include"cocos2d.h"


USING_NS_CC;
class SceneManager {
public:
	Scene* loadScene;
	Scene* openScene;
	Scene* startScene;
	Scene* optionScene;
	Scene* classicGameOverScene;
	Scene* rankListScene;
	Scene* MuitiPlayerGameOverScene;
	Scene* RhythmGameOverScene;

	void creatLoadScene();
	void goOpenScene();
	void goStartScene();
	void goOptionScene();
	void goClassicGameScene();
	void goClassicGameOverScene();
	void goRankListLayer();
	void goMuitiPlayerScene();
	void goMuitiPlayerGameOverScene();
	void goRhythmGameScene();
	void goRhythmGameOverScene();
};

#endif