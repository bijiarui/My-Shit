#include "RhythmGameScene.h"
#include "ListDefine.h"

bool RhythmGameScene::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto * background = Sprite::create("res/rhy.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);

	auto blue = LayerColor::create(Color4B(255, 100, 255, 100), 160, 288);
	blue->setPosition(135, visibleSize.height / 2 + 145 - 18 * 16);
	this->addChild(blue, 1);

	m_controlLayer = ControlLayer::create();
	m_controlLayer->setDelegate(this);
	this->addChild(m_controlLayer);

	m_gameLayer = GameLayer::create();
	m_gameLayer->setDelegate(this);
	this->addChild(m_gameLayer, 2);

	auto * menuItem = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(RhythmGameScene::menuCallBackBack, this));
	menuItem->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height * 0.9));
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);

	rhythm = Sprite::create("res/rhythm.png");
	rhythm->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	rhythm->setVisible(false);
	this->addChild(rhythm, 5);

	music.push_back("Bad Apple!!");
	music.push_back("The Hampster\nDance Song");
	music.push_back("We No Speak\nAmericano");

	TableView* tableView = TableView::create(this, CCSizeMake(220, 60));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(Vec2(visibleSize.width *0.65, visibleSize.height *0.2));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->reloadData();
	this->addChild(tableView,5);

	myRhythm.push_back(0.4838709677);
	myRhythm.push_back(0.441014333);
	myRhythm.push_back(0.48);

	return true;
}

void RhythmGameScene::menuCallBackBack(Ref * pSender)
{
	for (int i = 0; i < 3; ++i) {
		UD_setBool(StringUtils::format("is_rhythm%d", i).c_str(), false);
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	tsm->goStartScene();
}


void RhythmGameScene::undateRhytnm(float dt)
{
	if (m_iMusicID == 0) {
		scheduleOnce(schedule_selector(RhythmGameScene::canClickTrue), 0.08f);
		scheduleOnce(schedule_selector(RhythmGameScene::canSeeTrue), 0.15f);
		scheduleOnce(schedule_selector(RhythmGameScene::canSeeFalse), 0.40f);
		scheduleOnce(schedule_selector(RhythmGameScene::canClickFalse), 0.43f);
	}
	else if (m_iMusicID == 1) {
		scheduleOnce(schedule_selector(RhythmGameScene::canClickTrue), 0.08f);
		scheduleOnce(schedule_selector(RhythmGameScene::canSeeTrue), 0.15f);
		scheduleOnce(schedule_selector(RhythmGameScene::canSeeFalse), 0.40f);
		scheduleOnce(schedule_selector(RhythmGameScene::canClickFalse), 0.43f);
	}
	else if (m_iMusicID == 2) {
		scheduleOnce(schedule_selector(RhythmGameScene::canClickTrue), 0.08f);
		scheduleOnce(schedule_selector(RhythmGameScene::canSeeTrue), 0.15f);
		scheduleOnce(schedule_selector(RhythmGameScene::canSeeFalse), 0.40f);
		scheduleOnce(schedule_selector(RhythmGameScene::canClickFalse), 0.43f);
	}
}

void RhythmGameScene::canSeeTrue(float dt)
{
	rhythm->setVisible(true);
}

void RhythmGameScene::canSeeFalse(float dt)
{
	rhythm->setVisible(false);
}

void RhythmGameScene::canClickTrue(float dt)
{
	m_bCanClick = true;
}

void RhythmGameScene::canClickFalse(float dt)
{
	m_bCanClick = false;
}

void RhythmGameScene::gameOverAction()
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	for (int i = 0; i < 3; ++i) {
		UD_setBool(StringUtils::format("is_rhythm%d", i).c_str(), false);
	}
	UD_setInt(StringUtils::format("rhythmScore%d", m_iMusicID).c_str(), m_gameLayer->getScore());
	UD_setInt("musicID", m_iMusicID);
	if (m_gameLayer->getScore() >= UserDefault::sharedUserDefault()->getIntegerForKey(StringUtils::format("highScore%d", m_iMusicID).c_str())) {
		UD_setInt(StringUtils::format("highScore%d", m_iMusicID).c_str(), m_gameLayer->getScore());
	}
	tsm->goRhythmGameOverScene();
}

void RhythmGameScene::tableCellTouched(TableView * table, TableViewCell * cell)
{
	UD_setBool(StringUtils::format("is_rhythm%d", cell->getIdx()).c_str(), true);
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(StringUtils::format("musics/rhythm%d.mp3", cell->getIdx()).c_str(), true);
	m_iMusicID = cell->getIdx();
	schedule(schedule_selector(RhythmGameScene::undateRhytnm), myRhythm.at(cell->getIdx()), kRepeatForever, 0);
	m_gameLayer->startGame();
}

Size RhythmGameScene::tableCellSizeForIndex(TableView * table, ssize_t idx)
{
	return CCSizeMake(120,60);
}

TableViewCell * RhythmGameScene::tableCellAtIndex(TableView * table, ssize_t idx)
{
	TableViewCell *cell = table->dequeueCell();
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();
		LabelTTF *label = LabelTTF::create(music.at(idx), "fonts/Marker Felt.ttf", 24.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(100);
		cell->addChild(label,5);
	}
	else {
		LabelTTF *label = (LabelTTF*)cell->getChildByTag(100);
		label->setString(music.at(idx));
	}
	return cell;
}

ssize_t RhythmGameScene::numberOfCellsInTableView(TableView * table)
{
	return 3;
}

void RhythmGameScene::clickUp()
{
	if (m_bCanClick == true) {
		m_gameLayer->rotate(); 
		m_bCanClick = false;
	}
}

void RhythmGameScene::clickDown() {
	if (m_bCanClick == true) {
		m_gameLayer->throwDown();
		m_bCanClick = false;
	}
}

void RhythmGameScene::clickLeft() {
	if (m_bCanClick == true) {
		m_gameLayer->moveLeft();
		m_bCanClick = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/rotate.wav");
	}
}

void RhythmGameScene::clickRight() {
	if (m_bCanClick == true) {
		m_gameLayer->moveRight();
		m_bCanClick = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/rotate.wav");
	}
}

void RhythmGameScene::clickA() {
	if (m_bCanClick == true) {
		m_gameLayer->moveLeft();
		m_bCanClick = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/rotate.wav");
	}
}

void RhythmGameScene::clickS() 
{
	if (m_bCanClick == true) {
		m_gameLayer->throwDown();
		m_bCanClick = false;
	}
}

void RhythmGameScene::clickD() {
	if (m_bCanClick == true) {
		m_gameLayer->moveRight(); 
		m_bCanClick = false;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/rotate.wav");
	}
}

void RhythmGameScene::clickW() {
	if (m_bCanClick == true){
		m_gameLayer->rotate();
		m_bCanClick = false;
	}
}