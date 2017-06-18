#include "RankListLayer.h"

bool RankListLayer::init()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto * background = Sprite::create("res/BackGround.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);
	auto * menuItem_1 = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(RankListLayer::menuCallBack, this));
	menuItem_1->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height * 0.9));
	auto menu = Menu::create(menuItem_1, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);

	if (!UD_getBool("isExist", false)) {
		UD_setBool("isExist", true);
		for (auto iter = m_Player.begin(); iter != m_Player.end() -1;++iter) {
			UD_setString(StringUtils::format("p%d_name", (iter._Idx+1)).c_str(), "name");
			UD_setInt(StringUtils::format("p%d_score", (iter._Idx + 1)).c_str(), 0);
			iter->name = "name";
			iter->score = 0;
		}
	}
	else {
		for (auto iter = m_Player.begin(); iter != m_Player.end() - 1; ++iter) {
			iter->name = UD_getString(StringUtils::format("p%d_name", (iter._Idx + 1)).c_str());
			iter->score = UD_getInt(StringUtils::format("p%d_score", (iter._Idx + 1)).c_str());
		}
	}

	TableView* tableView = TableView::create(this, CCSizeMake(200, 250));
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	tableView->setPosition(Vec2(visibleSize.width / 4, visibleSize.height / 5));
	tableView->setDelegate(this);
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	tableView->reloadData();
	this->addChild(tableView);
	return true;
}

void RankListLayer::menuCallBack(Ref * pSender)
{
	tsm->goOpenScene();
}

void RankListLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
	
}

Size RankListLayer::tableCellSizeForIndex(TableView *table, ssize_t idx)
{
	return CCSizeMake(60, 60);
}

TableViewCell* RankListLayer::tableCellAtIndex(TableView *table, ssize_t idx)
{
	CCString *string = CCString::create(m_Player[idx].name + ":" + StringUtils::format("%d", m_Player[idx].score));

	TableViewCell *cell = table->dequeueCell();

	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();

		LabelTTF *label = LabelTTF::create(string->getCString(), "Arial", 20.0);
		label->setPosition(Vec2::ZERO);
		label->setAnchorPoint(Vec2::ZERO);
		label->setTag(100);
		cell->addChild(label);
	}
	else
	{
		LabelTTF *label = (LabelTTF*)cell->getChildByTag(100);
		label->setString(string->getCString());
	}

	return cell;
}

ssize_t RankListLayer::numberOfCellsInTableView(TableView *table)
{
	return max_range;
}