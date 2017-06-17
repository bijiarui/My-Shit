#pragma once
#ifndef  _CLASSIC_GAME_OVER_LAYER_
#define  _CLASSIC_GAME_OVER_LAYER_

#include <array> 
#include "cocos2d.h"
#include "ListDefine.h"
#include "SceneManager.h"

using std::array;
USING_NS_CC;


class ClassicGameOverLayer : public Layer
{
public:
	CREATE_FUNC(ClassicGameOverLayer);
	virtual bool init();
	bool onTouchBegan(Touch  *touch, Event  *event);
	void menuCallBack(Ref* pSender);

public:
	SceneManager *tsm;

private:
	TextFieldTTF* textEdit;
	LabelTTF* scoreItem;
	array<Player, max_range + 1> m_Player;
	int m_iScore;
};
#endif // ! _CLASSIC_GAME_OVER_LAYER_
