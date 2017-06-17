#pragma once
#ifndef _MULTI_PLAYER_GAME_OVER_LAYER_
#define _MULTI_PLAYER_GAME_OVER_LAYER_
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;

class MutiPlayersGameOverLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(MutiPlayersGameOverLayer);
	SceneManager * tsm;
private:
	void menuCallBack(Ref *pSender);
};



#endif // !_MULTI_PLAYER_GAME_OVER_LAYER_
