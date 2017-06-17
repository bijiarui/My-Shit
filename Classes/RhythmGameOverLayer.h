#pragma once
#ifndef  _RHYTHM_GAME_OVER_LAYER_
#define  _RHYTHM_GAME_OVER_LAYER_
#include "cocos2d.h"
#include "SceneManager.h"
USING_NS_CC;

class RhythmGameOverLayer : public Layer
{
public:
	virtual bool init();
	CREATE_FUNC(RhythmGameOverLayer);
	SceneManager * tsm;
private:
	void menuCallBack(Ref *pSender);
	LabelTTF* scoreItem;
	LabelTTF* highScoreItem;
	int m_iMusicID;
};


#endif // ! _RHYTHM_GAME_OVER_LAYER_
