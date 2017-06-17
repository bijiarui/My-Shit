# include "OptionLayer.h"

bool OptionLayer::init()
{
	Size winSize = Director::getInstance()->getWinSize();
	auto * background = Sprite::create("res/BackGround.jpg");
	background->setPosition(winSize.width / 2, winSize.height / 2);
	addChild(background, 0);
	auto * menuItem_1 = MenuItemLabel::create
	(Label::createWithTTF("Easy", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OptionLayer::menuCallBack, this));
	menuItem_1->setTag(101);
	menuItem_1->setPosition(Vec2(winSize.width / 2, winSize.height * 0.7));
	auto * menuItem_2 = MenuItemLabel::create
	(Label::createWithTTF("Normal", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OptionLayer::menuCallBack, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(winSize.width / 2, winSize.height * 0.5));
	auto * menuItem_3 = MenuItemLabel::create
	(Label::createWithTTF("Hard", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OptionLayer::menuCallBack, this));
	menuItem_3->setTag(103);
	menuItem_3->setPosition(Vec2(winSize.width / 2, winSize.height * 0.3));
	auto * menuItem_4 = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(OptionLayer::menuCallBack, this));
	menuItem_4->setTag(104);
	menuItem_4->setPosition(Vec2(winSize.width *0.1, winSize.height * 0.9));
	auto menu = Menu::create(menuItem_1, menuItem_2, menuItem_3, menuItem_4, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);

	return true;
}

void OptionLayer::menuCallBack(Ref * pSender)
{
	switch ((static_cast<MenuItem*>(pSender))->getTag()) {
	case(101) :{
		UserDefault::sharedUserDefault()->setStringForKey("Level", "Easy");
		tsm->goOpenScene();
		}
			   break;
	case(102): {
		UserDefault::sharedUserDefault()->setStringForKey("Level", "Normal");
		tsm->goOpenScene();
	}
			   break;
	case(103): {
		UserDefault::sharedUserDefault()->setStringForKey("Level", "Hard");
		tsm->goOpenScene();
	}
			   break;
	case(104): {
		tsm->goOpenScene();
	}
			   break;
	}
}