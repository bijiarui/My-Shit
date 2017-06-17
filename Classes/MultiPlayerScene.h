#pragma once
#ifndef _MULTIPLAYER_SCENE_
#define _MULTIPLAYER_SCENE_
#include "cocos2d.h"
#include "GameLayer.h"
#include "ControlLayer.h"
#include "SceneManager.h"
USING_NS_CC;

class MultiPlayerScene :public Scene, ControlLayerDelegate, GameLayerDelegate
{
public:
	virtual bool init();
	CREATE_FUNC(MultiPlayerScene);
public:

	virtual void clickUp() { m_gameLayer2->rotate(); }
	virtual void clickDown() { m_gameLayer2->throwDown(); }
	virtual void clickLeft() { m_gameLayer2->moveLeft(); }
	virtual void clickRight() { m_gameLayer2->moveRight(); }
	virtual void clickA() { m_gameLayer1->moveLeft(); }
	virtual void clickS() { m_gameLayer1->throwDown(); }
	virtual void clickD() { m_gameLayer1->moveRight(); }
	virtual void clickW() { m_gameLayer1->rotate(); }
public:
	virtual void gameOverAction();
public:
	SceneManager* tsm;
private:
	GameLayer *m_gameLayer1;
	GameLayer *m_gameLayer2;
	ControlLayer *m_controlLayer;
	void menuCallBackStart(Ref *pSender);
	void menuCallBackBack(Ref *pSender);
	int m_iPlayer;
};



#endif // !_MULTIPLAYER_SCENE_
