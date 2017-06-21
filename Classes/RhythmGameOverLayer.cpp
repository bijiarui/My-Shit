#include "RhythmGameOverLayer.h"
#include "ListDefine.h"

bool RhythmGameOverLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto * background = Sprite::create("res/BackGround.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);
	auto * menuItem_1 = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(RhythmGameOverLayer::menuCallBack, this));
	menuItem_1->setTag(101);
	menuItem_1->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height * 0.9));
	auto * menuItem_2 = MenuItemLabel::create
	(Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(RhythmGameOverLayer::menuCallBack, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(visibleSize.width * 0.4, visibleSize.height * 0.1));
	auto * menuItem_3 = MenuItemLabel::create
	(Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(RhythmGameOverLayer::menuCallBack, this));
	menuItem_3->setTag(103);
	menuItem_3->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.1));
	auto menu = Menu::create(menuItem_1, menuItem_2, menuItem_3, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);

	auto * labelMyScore = Label::createWithTTF("Your score is", "fonts/Marker Felt.ttf", 23);
	labelMyScore->setPosition(visibleSize.width *0.4, visibleSize.height * 2/5);
	this->addChild(labelMyScore);
	auto * labelHigtScore = Label::createWithTTF("High score is", "fonts/Marker Felt.ttf", 23);
	labelHigtScore->setPosition(visibleSize.width *0.4, visibleSize.height * 3/5);
	this->addChild(labelHigtScore);
	m_iMusicID = UD_getInt("musicID");
	int myScore = UD_getInt(StringUtils::format("rhythmScore%d", m_iMusicID).c_str());
	int highScore = UD_getInt(StringUtils::format("highScore%d", m_iMusicID).c_str());
	CCString* strMyScore = CCString::createWithFormat("%d", myScore);
	scoreItem = LabelTTF::create("0", "fonts/Marker Felt.ttf", 40);
	scoreItem->setString(strMyScore->_string.c_str());
	scoreItem->setPosition(visibleSize.width*0.65, visibleSize.height*0.4);
	this->addChild(scoreItem);
	CCString* strHighScore = CCString::createWithFormat("%d", highScore);
	highScoreItem = LabelTTF::create("0", "fonts/Marker Felt.ttf", 40);
	highScoreItem->setString(strHighScore->_string.c_str());
	highScoreItem->setPosition(visibleSize.width*0.65, visibleSize.height*0.6);
	this->addChild(highScoreItem);

	return true;
}

void RhythmGameOverLayer::menuCallBack(Ref * pSender)
{
	switch ((static_cast<MenuItem*>(pSender))->getTag()) {
	case 101: {
		tsm->goRhythmGameScene();
	}
			  break;
	case 102: {
		tsm->goRhythmGameScene();
	}
			  break;
	case 103: {
		tsm->goOpenScene();
	}
			  break;
	}
}