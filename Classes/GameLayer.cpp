#include "GameLayer.h"

bool GameLayer::init()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/clean.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/rotate.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/throwdown.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/Great.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/Excellent.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/Unbelievable.mp3");
	m_bGameRun = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* *backGround = new Sprite*[m_iRowTetris*m_iColumnTetris];
	for (int r = 0; r < m_iRowTetris; ++r) {
		for (int c = 0; c < m_iColumnTetris; ++c) {
			backGround[r*m_iColumnTetris + c] = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("res/back.png"));
			backGround[r*m_iColumnTetris + c]->setPosition(visibleSize.width*0.3 + c * 16, visibleSize.height *0.93 - r * 16);
			backGround[r*m_iColumnTetris + c]->setOpacity(75);
			this->addChild(backGround[r*m_iColumnTetris + c], 2);
		}
	}
	//创建游戏区
	m_spriteBrickMatrix = new Sprite*[m_iRowTetris*m_iColumnTetris];
	for (int r = 0; r < m_iRowTetris; ++r) {
		for (int c = 0; c < m_iColumnTetris; ++c) {
			m_spriteBrickMatrix[r*m_iColumnTetris + c] = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("res/tetris_0.png"));
			m_spriteBrickMatrix[r*m_iColumnTetris + c]->setPosition(visibleSize.width*0.3 + c * 16, visibleSize.height *0.93 - r * 16);
			this->addChild(m_spriteBrickMatrix[r*m_iColumnTetris + c], 3);
		}
	}
	m_spriteNextBrick = new Sprite*[4 * 4];
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			m_spriteNextBrick[i * 4 + j] = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey("res/tetris_0.png"));
			m_spriteNextBrick[i * 4 + j]->setPosition(visibleSize.width *0.7 + j * 16, visibleSize.height * 0.75 - i * 16);
			this->addChild(m_spriteNextBrick[i * 4 + j], 3);
		}
	}

	m_tetris = new Tetris(m_iRowTetris, m_iColumnTetris);

	scoreItem = LabelTTF::create("0", "fonts/Marker Felt.ttf", 40);
	scoreItem->setColor(ccc3(255, 255, 255));
	scoreItem->setAnchorPoint(ccp(0, 0.5));
	scoreItem->setPosition(ccp(visibleSize.width*0.7, visibleSize.height*0.5));
	this->addChild(scoreItem);

	return true;
}

void GameLayer::updateBrickMatrix()
{
	for (int r = 0; r < m_iRowTetris; ++r) {
		for (int c = 0; c < m_iColumnTetris; ++c) {
			std::string filePath = StringUtils::format("res/tetris_%i.png", m_tetris->getBrickValue(r, c));
			m_spriteBrickMatrix[r*m_iColumnTetris + c]->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey(filePath));
		}
	}
}

void GameLayer::updateNextBrick()
{
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			if (m_tetris->getNextValue(r, c))
				m_spriteNextBrick[r * 4 + c]->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("res/tetris_next.png"));
			else
				m_spriteNextBrick[r * 4 + c]->setTexture(Director::getInstance()->getTextureCache()->getTextureForKey("res/tetris_0.png"));
		}
	}
}

void GameLayer::fall()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (!m_tetris->fallBrick())
	{
		int lineIndex = 0;
		while (m_tetris->clearOneLine(lineIndex)) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/clean.mp3");
			m_iScore += 100;
			updateScore(m_iScore);
			for(int i=0;i<3;++i){
				if (m_iScore >= UserDefault::sharedUserDefault()->getIntegerForKey(StringUtils::format("highScore%d", i).c_str()) && UserDefault::sharedUserDefault()->getBoolForKey(StringUtils::format("is_rhythm%d", i).c_str())
					&& UserDefault::sharedUserDefault()->getIntegerForKey(StringUtils::format("highScore%d", i).c_str()) != 0 && m_bCan ) {
					auto plist = ParticleSystemQuad::create("particles/highScore.plist");
					plist->setPosition(visibleSize.width*0.438, visibleSize.height *0.5);
					this->addChild(plist, 5);
					m_bCan == false;
				}
			}
			GameLayer::initPartical(lineIndex);
		}
		// 下一个方块
		if (!m_tetris->setNextBrick(m_tetris->getNextBrickType()))
		{
			m_bGameRun = false;
		}
		BrickType brickType = rand() % BrickType_Count;
		m_tetris->getNextBrick(brickType, (BrickCellValue)(brickType + 1));
		this->updateNextBrick();
	}
	this->updateBrickMatrix();
}
void GameLayer::moveLeft()
{
	if (m_bGameRun == true) {
		if (m_tetris->moveLeftBrick())
			this->updateBrickMatrix();
	}
}

void GameLayer::moveRight()
{
	if (m_bGameRun == true) {
		if (m_tetris->moveRightBrick())
			this->updateBrickMatrix();
	}
}

void GameLayer::rotate()
{
	if (m_bGameRun == true) {
		if (m_tetris->rotateBrick()) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/rotate.wav");
			this->updateBrickMatrix();
		}
	}
}

void GameLayer::throwDown()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (m_bGameRun == true) {
		m_tetris->throwDownBrick();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/throwdown.wav");
		int lineIndex = 0;
		int combo = 0;
		while (m_tetris->clearOneLine(lineIndex)) {
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/clean.mp3");
			++combo;
			m_iScore += 100;
			updateScore(m_iScore);
			for (int i = 0; i < 3; ++i) {
				if (m_iScore >= UserDefault::sharedUserDefault()->getIntegerForKey(StringUtils::format("highScore%d", i).c_str()) && UserDefault::sharedUserDefault()->getBoolForKey(StringUtils::format("is_rhythm%d", i).c_str())
					&& UserDefault::sharedUserDefault()->getIntegerForKey(StringUtils::format("highScore%d", i).c_str()) != 0 && m_bCan) {
					auto plist = ParticleSystemQuad::create("particles/highScore.plist");
					plist->setPosition(visibleSize.width*0.438, visibleSize.height *0.5);
					this->addChild(plist, 5);
					m_bCan == false;
				}
			}
			GameLayer::initPartical(lineIndex);
		}
		if (combo == 2) {
			GameLayer::initCombo("particles/2X.plist");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Great.mp3");
		}
		else if (combo == 3) {
			GameLayer::initCombo("particles/3X.plist");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Excellent.mp3");
		}
		else if (combo == 4) {
			GameLayer::initCombo("particles/4X.plist");
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/Unbelievable.mp3");
		}

		if (!m_tetris->setNextBrick(m_tetris->getNextBrickType()))
		{
			m_bGameRun = false;
		}
		this->updateBrickMatrix();
		BrickType brickType = rand() % BrickType_Count;
		m_tetris->getNextBrick(brickType, (BrickCellValue)(brickType + 1));
		this->updateNextBrick();
	}
}

float GameLayer::level()
{
	if (UserDefault::sharedUserDefault()->getBoolForKey("is_rhythm0")) {
		return 0.4838709677;
	}
	else if (UserDefault::sharedUserDefault()->getBoolForKey("is_rhythm1")) {
		return 0.441014333;
	}
	else if (UserDefault::sharedUserDefault()->getBoolForKey("is_rhythm2")) {
		return 0.48;
	}
	else {
		std::string level = UserDefault::sharedUserDefault()->getStringForKey("Level");
		if (level.empty() || level == "Normal") {
			return 0.6;
		}
		else if (level == "Easy") {
			return 0.9;
		}
		else if (level == "Hard") {
			return 0.3;
		}
	}
	return 0.6;
}

void GameLayer::updateScore(int score)
{
	CCString* strScore = CCString::createWithFormat("%d", score);
	scoreItem->setString(strScore->_string.c_str());
}

void GameLayer::startGame()
{
	m_bGameRun = true;
	m_tetris->clearBrickMatrix();
	m_tetris->clearNextBrick();
	m_iScore = 0;
	updateScore(m_iScore);
	BrickType brickType = (BrickType)(rand() % BrickType_Count);
	m_tetris->setNewBrick(brickType, (BrickCellValue)(brickType + 1));
	brickType = (BrickType)(rand() % BrickType_Count);
	m_tetris->getNextBrick(brickType, (BrickCellValue)(brickType + 1));
	this->updateBrickMatrix();
	this->updateNextBrick();
	this->stopAllActions();
	CallFunc *callFunc = CallFunc::create([=] {
		if (m_bGameRun) {
			this->fall();
		}
		else {
			m_delegate->gameOverAction();
		}
	});
	this->runAction(RepeatForever::create(Sequence::create(DelayTime::create(level()), callFunc, NULL)));
}

void GameLayer::initPartical(int r)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_Particle = ParticleSystemQuad::create("particles/2444.plist");
	m_Particle->setPosition(visibleSize.width*0.438, visibleSize.height *0.93 - r * 16);
	this->addChild(m_Particle,5);

	this->scheduleOnce(schedule_selector(GameLayer::deletePartical), m_Particle->getLife() + 1.0f);
}

void GameLayer::deletePartical(float dt)
{
	this->removeChild(m_Particle, true);
}

void GameLayer::initCombo(char* s)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	m_Combo = ParticleSystemQuad::create(s);
	m_Combo->setPosition(visibleSize.width*0.438, visibleSize.height *0.5);
	this->addChild(m_Combo, 6);
	this->scheduleOnce(schedule_selector(GameLayer::deleteCombo), m_Combo->getLife() + 1.0f);

}

void GameLayer::deleteCombo(float dt)
{
	this->removeChild(m_Combo, true);

}
