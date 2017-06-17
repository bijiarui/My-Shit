#pragma once
#ifndef _CLASSIC_GAME_SCENE_
#define _CLASSIC_GAME_SCENE_

#include "cocos2d.h"
#include "GameLayer.h"
#include "ControlLayer.h"
#include "SceneManager.h"
USING_NS_CC;

class ClassicGameScene :public Scene, ControlLayerDelegate, GameLayerDelegate
{
public:
	virtual bool init();
	CREATE_FUNC(ClassicGameScene);

public:
	virtual void clickUp() { m_gameLayer->rotate(); }
	virtual void clickDown() { m_gameLayer->throwDown(); }
	virtual void clickLeft() { m_gameLayer->moveLeft(); }
	virtual void clickRight() { m_gameLayer->moveRight(); }
	virtual void clickA() { m_gameLayer->moveLeft(); }
	virtual void clickS() { m_gameLayer->throwDown(); }
	virtual void clickD() { m_gameLayer->moveRight(); }
	virtual void clickW() { m_gameLayer->rotate(); }
public:
	virtual void gameOverAction();
public:
	SceneManager* tsm;

private:
	GameLayer *m_gameLayer;
	ControlLayer *m_controlLayer;
	void menuCallBackStart(Ref *pSender);
	void menuCallBackBack(Ref *pSender);
};

#endif // _CLASSIC_GAME_SCENE_
