#include "MultiPlayerGameOverLayer.h"
#include "ListDefine.h"

bool MutiPlayersGameOverLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto * background = Sprite::create("res/BackGround.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);
	auto * lable = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 40);
	lable->setPosition(visibleSize.width*0.5,visibleSize.height*0.7);
	this->addChild(lable);

	int player1 = UD_getInt("player1Score");
	int player2 = UD_getInt("player2Score");
	
	auto * menuItem_1 = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(MutiPlayersGameOverLayer::menuCallBack, this));
	menuItem_1->setTag(101);
	menuItem_1->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height * 0.9));
	auto * menuItem_2 = MenuItemLabel::create
	(Label::createWithTTF("Restart", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(MutiPlayersGameOverLayer::menuCallBack, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(visibleSize.width * 0.4, visibleSize.height * 0.1));
	auto * menuItem_3 = MenuItemLabel::create
	(Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(MutiPlayersGameOverLayer::menuCallBack, this));
	menuItem_3->setTag(103);
	menuItem_3->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.1));
	auto menu = Menu::create(menuItem_1, menuItem_2, menuItem_3, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);


	if (player1 > player2) {
		auto * label = Label::createWithTTF("Player1 Win!", "fonts/Marker Felt.ttf", 48);
		label->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 5);
	//	label->enableGlow(Color4B::GREEN);
		this->addChild(label);
	}
	else if (player1 < player2) {
		auto * label = Label::createWithTTF("Player2 Win!", "fonts/Marker Felt.ttf", 48);
		label->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 5);
	//	label->enableGlow(Color4B::RED);
		this->addChild(label);
	}
	else if (player1 == player2) {
		auto * label = Label::createWithTTF("Draw!", "fonts/Marker Felt.ttf", 48);
		label->setPosition(visibleSize.width / 2, visibleSize.height * 2 / 5);
	//	label->enableGlow(Color4B::RED);
		this->addChild(label);
	}
	return true;
}

void MutiPlayersGameOverLayer::menuCallBack(Ref * pSender)
{
	switch ((static_cast<MenuItem*>(pSender))->getTag()) {
	case 101: {
		tsm->goMuitiPlayerScene();
	}
			  break;
	case 102: {
		tsm->goMuitiPlayerScene();
	}
			  break;
	case 103: {
		tsm->goOpenScene();
	}
			  break;
	}
}
