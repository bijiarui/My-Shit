#include "ClassicGameScene.h"

bool ClassicGameScene::init()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("musics/backgroundmusic.mp3", true);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto * background = Sprite::create("res/bao.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	auto blue = LayerColor::create(Color4B(100, 100, 255, 100), 160, 288);
	blue->setPosition(135, visibleSize.height /2+145 - 18 * 16);
	this->addChild(blue, 1);

	m_controlLayer = ControlLayer::create();
	m_controlLayer->setDelegate(this);
	this->addChild(m_controlLayer);

	m_gameLayer = GameLayer::create();
	m_gameLayer->setDelegate(this);
	this->addChild(m_gameLayer,2);

	auto * menuItem_1 = MenuItemLabel::create
	(Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(ClassicGameScene::menuCallBackStart, this));
	menuItem_1->setPosition(Vec2(visibleSize.width *0.75, visibleSize.height * 0.25));
	auto * menuItem_2 = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(ClassicGameScene::menuCallBackBack, this));
	menuItem_2->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height * 0.9));

	auto menu1 = Menu::create(menuItem_1, NULL);
	menu1->setPosition(0, 0);
	this->addChild(menu1);
	auto menu2 = Menu::create(menuItem_2, NULL);
	menu2->setPosition(0, 0);
	this->addChild(menu2);

	return true;
}

void ClassicGameScene::gameOverAction()
{
	UserDefault::sharedUserDefault()->setIntegerForKey("score",m_gameLayer->getScore());
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	tsm->goClassicGameOverScene();
}

void ClassicGameScene::menuCallBackStart(Ref * pSender)
{
	m_gameLayer->startGame();
}

void ClassicGameScene::menuCallBackBack(Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	tsm->goStartScene();
}