#pragma once
#ifndef _RHYTHM_GAME_SCENE_
#define _RHYTHM_GAME_SCENE_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameLayer.h"
#include "ControlLayer.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;

class RhythmGameScene :public Scene, ControlLayerDelegate, GameLayerDelegate, TableViewDataSource, TableViewDelegate
{
public:
	virtual bool init();
	CREATE_FUNC(RhythmGameScene);

public:
	virtual void clickUp();
	virtual void clickDown();
	virtual void clickLeft();
	virtual void clickRight();
	virtual void clickA();
	virtual void clickS();
	virtual void clickD();
	virtual void clickW();
public:
	virtual void gameOverAction();
public:
	SceneManager* tsm;

private:
	void menuCallBackBack(Ref *pSender);

	GameLayer *m_gameLayer;
	ControlLayer *m_controlLayer;
	bool m_bCanClick = false;
	bool m_bCanSee = false;
	int m_iMusicID = -1;
	Sprite* rhythm;
	Sprite* see;
	std::vector<std::string> music;
	std::vector<float> myRhythm;
	void undateRhytnm(float dt);
	void canSeeTrue(float dt);
	void canSeeFalse(float dt);
	void canClickTrue(float dt);
	void canClickFalse(float dt);

	virtual void scrollViewDidScroll(ScrollView* view) {}
	virtual void scrollViewDidZoom(ScrollView* view) {}
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);
	virtual Size tableCellSizeForIndex(TableView *table, ssize_t idx);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);

};
#endif // ! _RHYTHM_GAME_SCENE_
