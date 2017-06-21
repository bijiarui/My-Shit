#include "MultiPlayerScene.h"
#include "ListDefine.h"

bool MultiPlayerScene::init()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("musics/Tetris.mp3", true);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto * background = Sprite::create("res/0001.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	m_controlLayer = ControlLayer::create();
	m_controlLayer->setDelegate(this);
	this->addChild(m_controlLayer);

	auto blue = LayerColor::create(Color4B(100, 255, 100, 100), 130, 231);
	blue->setPosition(8, visibleSize.height / 2 + 153 - 18 * 16);
	this->addChild(blue, 1);

	auto red = LayerColor::create(Color4B(255, 100, 100, 100), 130, 231);
	red->setPosition(258, visibleSize.height / 2 + 153 - 18 * 16);
	this->addChild(red, 1);

	m_gameLayer1 = GameLayer::create();
	m_gameLayer1->setDelegate(this);
	m_gameLayer1->setScale(0.8f);
	m_gameLayer1->setPosition(-100, 10);
	this->addChild(m_gameLayer1, 2);

	m_gameLayer2 = GameLayer::create();
	m_gameLayer2->setDelegate(this);
	m_gameLayer2->setScale(0.8f);
	m_gameLayer2->setPosition(150, 10);
	this->addChild(m_gameLayer2, 2);

	auto * menuItem_1 = MenuItemLabel::create
	(Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(MultiPlayerScene::menuCallBackStart, this));
	menuItem_1->setPosition(Vec2(visibleSize.width *0.5, visibleSize.height * 0.9));
	auto * menuItem_2 = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(MultiPlayerScene::menuCallBackBack, this));
	menuItem_2->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height * 0.9));

	auto menu1 = Menu::create(menuItem_1, NULL);
	menu1->setPosition(0, 0);
	this->addChild(menu1);
	auto menu2 = Menu::create(menuItem_2, NULL);
	menu2->setPosition(0, 0);
	this->addChild(menu2);

	return true;
}

void MultiPlayerScene::menuCallBackStart(Ref * pSender)
{
	m_gameLayer1->startGame();
	m_gameLayer2->startGame();
}

void MultiPlayerScene::menuCallBackBack(Ref * pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	tsm->goStartScene();
}
void MultiPlayerScene::gameOverAction()
{
	if (!m_gameLayer2->getGameCondition() && !m_gameLayer1->getGameCondition()) {
			UD_setInt("player2Score", m_gameLayer2->getScore());
			UD_setInt("player1Score", m_gameLayer1->getScore());
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
			tsm->goMuitiPlayerGameOverScene();
	}
}