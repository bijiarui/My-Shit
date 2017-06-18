#include "ClassicGameOverLayer.h"

bool ClassicGameOverLayer::init()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto * background = Sprite::create("res/BackGround.jpg");
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background, 0);
	textEdit = CCTextFieldTTF::textFieldWithPlaceHolder("Please input your name:","Arial", 24);  
	textEdit->setPosition(Vec2(visibleSize.width/2, visibleSize.height/3 ));  
	this->addChild(textEdit);
	setTouchMode(kCCTouchesOneByOne);
	setTouchEnabled(true);

	auto * label = Label::createWithTTF("Your score is", "fonts/Marker Felt.ttf", 23);
	label->setPosition(visibleSize.width / 2, visibleSize.height * 2/3);
	this->addChild(label);
   
	m_iScore = UD_getInt("score");
	CCString* strScore = CCString::createWithFormat("%d", m_iScore);
	scoreItem = LabelTTF::create("0", "fonts/Marker Felt.ttf", 40);
	scoreItem->setString(strScore->_string.c_str());
	scoreItem->setAnchorPoint(ccp(0, 0.5));
	scoreItem->setPosition(ccp(visibleSize.width*0.5, visibleSize.height*0.5));
	this->addChild(scoreItem);

	if (!UD_getBool("isExist", false)) {
		UD_setBool("isExist", true);
		for (auto iter = m_Player.begin(); iter!=m_Player.end()-1; ++iter) {
			int i = 1;
			UD_setString(StringUtils::format("p%d_name", (iter._Idx + 1)).c_str(), "name");
			UD_setInt(StringUtils::format("p%d_score", (iter._Idx + 1)).c_str(), 0);
			iter->name = "name";
			iter->score = 0;
			++i;
		}
	}
	else {
		for (auto iter = m_Player.begin(); iter != m_Player.end() - 1; ++iter) {
			iter->name = UD_getString(StringUtils::format("p%d_name", (iter._Idx + 1)).c_str());
			iter->score = UD_getInt(StringUtils::format("p%d_score", (iter._Idx + 1)).c_str());
		}
	}


	auto * menuItem_1 = MenuItemLabel::create
	(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(ClassicGameOverLayer::menuCallBack, this));
	menuItem_1->setTag(101);
	menuItem_1->setPosition(Vec2(visibleSize.width *0.1, visibleSize.height * 0.9));
	auto * menuItem_2 = MenuItemLabel::create
	(Label::createWithTTF("Submit", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(ClassicGameOverLayer::menuCallBack, this));
	menuItem_2->setTag(102);
	menuItem_2->setPosition(Vec2(visibleSize.width * 0.4, visibleSize.height * 0.1));
	auto * menuItem_3 = MenuItemLabel::create
	(Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 30), CC_CALLBACK_1(ClassicGameOverLayer::menuCallBack, this));
	menuItem_3->setTag(103);
	menuItem_3->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.1));
	auto menu = Menu::create(menuItem_1, menuItem_2, menuItem_3, NULL);
	menu->setPosition(0, 0);
	this->addChild(menu);


	return true;
}

bool ClassicGameOverLayer::onTouchBegan(Touch * touch, Event * event)
{
	bool isClicked = textEdit->boundingBox().containsPoint(touch->getLocation());
	
	if (isClicked) {
		textEdit->attachWithIME();
	}
	else {
		textEdit->detachWithIME();
	}
	return true;
}

void ClassicGameOverLayer::menuCallBack(Ref * pSender)
{
	switch ((static_cast<MenuItem*>(pSender))->getTag()) {
	case 101: {
		tsm->goClassicGameScene();
	}
			  break;
	case 102: {
		m_Player[max_range].name = textEdit->getString();
		m_Player[max_range].score = m_iScore;

		bool isExist = false;
		for (auto iter = m_Player.begin(); iter != m_Player.end() - 1;++iter) {
			if (iter->name == m_Player[max_range].name) {
				iter->score = iter->score>m_Player[max_range].score ? iter->score : m_Player[max_range].score;
				isExist = true;
				break;
			}
		}

		if (!isExist) {
			for (auto iteri = m_Player.begin(); iteri != m_Player.end() - 1;++iteri) {
				for (auto iterj = (m_Player.end() - iteri._Idx-1); iterj != m_Player.begin();--iterj) {
					if (iterj->score > (iterj-1)->score) {
						Player temp;
						temp = (*iterj);
						(*iterj) = (*(iterj-1));
						(*(iterj - 1)) = temp;
					}
				}
			}
		}
		for (auto iter = m_Player.begin(); iter != m_Player.end() - 1; ++iter) {
			UD_setString(StringUtils::format("p%d_name", (iter._Idx + 1)).c_str(), iter->name);
			UD_setInt(StringUtils::format("p%d_score", (iter._Idx + 1)).c_str(), iter->score);
		}
	}
			  break;
	case 103: {
		tsm->goOpenScene();
	}
			  break;
	}

}