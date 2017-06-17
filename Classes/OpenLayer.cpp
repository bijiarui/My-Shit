#include "OpenLayer.h"

bool OpenLayer::init() {
	Size winSize = Director::getInstance()->getWinSize();
	auto * background = Sprite::create("res/BackGround.jpg");
	background->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(background, 0);
	auto * label = Label::createWithTTF("Tetris", "fonts/Marker Felt.ttf", 48);
	label->setColor(Color3B(255, 0, 0));
	label->setPosition(winSize.width / 2, winSize.height * 4 / 5);
	this->addChild(label);
	auto * menuItem_1 = MenuItemLabel::create
	(Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	menuItem_1->setTag(101);
	menuItem_1->setPosition(Vec2(winSize.width / 2, winSize.height * 0.49));
	auto * menuItem_2 = MenuItemLabel::create
	(Label::createWithTTF("Quit", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width / 2, winSize.height * 0.13));
	auto * menuItem_3 = MenuItemLabel::create
	(Label::createWithTTF("Option", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	menuItem_3->setTag(103);
	menuItem_3->setPosition(Vec2(winSize.width / 2, winSize.height * 0.25));
	auto * menuItem_4 = MenuItemLabel::create
	(Label::createWithTTF("Ranklist", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OpenLayer::menuCallBack, this));
	menuItem_4->setTag(104);
	menuItem_4->setPosition(Vec2(winSize.width / 2, winSize.height * 0.37));
	auto menu = Menu::create(menuItem_1, menuItem_2, menuItem_3, menuItem_4, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);

	return true;
}
void OpenLayer::menuCallBack(Ref * pSender) {
	switch ((static_cast<MenuItem*>(pSender))->getTag()) {
	case 101: {
		tsm->goStartScene();
	}
			  break;
	case 102: {
		Director::getInstance()->end();
		exit(0);
	}
			  break;
	case 103: {
		tsm->goOptionScene();
	}
			  break;
	case 104: {
		tsm->goRankListLayer();
	}
			  break;
	}
}
