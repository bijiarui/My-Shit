#include "LoadLayer.h"

bool LoadLayer::init() {
	auto * lable = Label::createWithTTF("Loading...", "fonts/Marker Felt.ttf", 24);
	lable->setPosition(Vec2(400, 50));
	this->addChild(lable);
	scheduleOnce(CC_SCHEDULE_SELECTOR(LoadLayer::onScheduleOnce), 1.0);
	return true;
}
void LoadLayer::onScheduleOnce(float dt) {
	tsm->goOpenScene();
}