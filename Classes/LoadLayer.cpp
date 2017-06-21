#include "LoadLayer.h"

bool LoadLayer::init() {
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto * lable = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 24);
	lable->setPosition(visibleSize.width*0.7,visibleSize.height*0.15);
	this->addChild(lable);

	auto * sprite = Sprite::create("res/png_1.png");
	sprite->setPosition(visibleSize.width*0.9, visibleSize.height*0.15);
	this->addChild(sprite);
	auto* animation = Animation::create();
	for (int i = 1; i < 5; ++i) {
		animation->addSpriteFrameWithFile(StringUtils::format("res/png_%d.png", i).c_str());
	}
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.1f);
	auto* action = Animate::create(animation);
	sprite->runAction(action);
	scheduleOnce(CC_SCHEDULE_SELECTOR(LoadLayer::onScheduleOnce), 1.0);
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("musics/Tetris.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("musics/rhythm0.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("musics/rhythm1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("musics/rhythm2.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("musics/backgroundmusic.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/clean.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/rotate.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/throwdown.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/Great.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/Excellent.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/Unbelievable.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sounds/click.wav");
	return true;
}
void LoadLayer::onScheduleOnce(float dt) {
	tsm->goOpenScene();
}