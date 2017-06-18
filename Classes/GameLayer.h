#pragma once
#ifndef _GAME_LAYER_
#define _GAME_LAYER_
#include <iostream>
#include <string>
#include "cocos2d.h"
#include "Tetris\Tetris.h"
#include "SceneManager.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

class GameLayerDelegate
{

public:
	virtual void gameOverAction() = 0;

};

class GameLayer : public Layer
{
public:
	CREATE_FUNC(GameLayer);
	virtual bool init();
	void moveLeft();
	void moveRight();
	void rotate();
	void fall();
	void throwDown();
	void startGame();
	void setDelegate(GameLayerDelegate *delegate) { m_delegate = delegate; }
	int getScore() { return m_iScore; }
	bool getGameCondition() { return m_bGameRun; }

private:
	float level();
	void updateScore(int score);
	void updateBrickMatrix();
	void updateNextBrick();
	void initPartical(int r);
	void deletePartical(float dt);
	void initCombo(char * s);
	void deleteCombo(float dt);
	
	GameLayerDelegate *m_delegate;
	Tetris *m_tetris;
	bool m_bGameRun;
	const int m_iRowTetris = 18;
	const int m_iColumnTetris = 10;
	Sprite* *m_spriteBrickMatrix;
	Sprite* *m_spriteNextBrick;
	int m_iScore = 0;
	bool m_bCan = true;
	LabelTTF* scoreItem;
	ParticleSystem *m_Particle;
	ParticleSystem *m_Combo;
	ParticleSystem *m_Throw;
};

#endif // !_CLASSIC_GAME_LAYER_
