

#include "StartLayer.h"

bool StartLayer::init() {
	auto winsize = Director::getInstance()->getWinSize();
	auto * background = Sprite::create("res/BackGround.jpg");
	background->setPosition(winsize.width / 2, winsize.height / 2);
	addChild(background, 0);
	auto * menuitem_1 = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(StartLayer::menuCallBack, this));
	menuitem_1->setTag(101);
	menuitem_1->setPosition(Vec2(winsize.width *0.1, winsize.height*0.9));
	auto * menuitem_2 = MenuItemLabel::create
	(Label::createWithTTF("Classic Tetris", "fonts/Marker Felt.ttf", 24), CC_CALLBACK_1(StartLayer::menuCallBack, this));
	menuitem_2->setTag(102);
	menuitem_2->setPosition(Vec2(winsize.width *0.5, winsize.height*0.7));
	auto * menuitem_3 = MenuItemLabel::create
	(Label::createWithTTF("Multi Player", "fonts/Marker Felt.ttf", 24), CC_CALLBACK_1(StartLayer::menuCallBack, this));
	menuitem_3->setTag(103);
	menuitem_3->setPosition(Vec2(winsize.width *0.5, winsize.height*0.5));
	auto * menuitem_4 = MenuItemLabel::create
	(Label::createWithTTF("Rhythm Tetris", "fonts/Marker Felt.ttf", 24), CC_CALLBACK_1(StartLayer::menuCallBack, this));
	menuitem_4->setTag(104);
	menuitem_4->setPosition(Vec2(winsize.width *0.5, winsize.height*0.3));

	auto menu = Menu::create(menuitem_1, menuitem_2, menuitem_3, menuitem_4, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);

	return true;
}
void StartLayer::menuCallBack(Ref * pSender) {
	switch ((static_cast<MenuItem*>(pSender))->getTag()) {
	case 101: {
		tsm->goOpenScene();
	}
			  break;
	case 102: {
		tsm->goClassicGameScene();
	}
			  break;
	case 103: {
		tsm->goMuitiPlayerScene();
	}
			  break;
	case 104: {
		tsm->goRhythmGameScene();
	}
			  break;
	}
}