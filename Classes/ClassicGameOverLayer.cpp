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
		for (int i = 1; i <= max_range; ++i) {
			UD_setString(StringUtils::format("p%d_name", i).c_str(), "name");
			UD_setInt(StringUtils::format("p%d_score", i).c_str(), 0);
			m_Player[i - 1].name = "name";
			m_Player[i - 1].score = 0;
		}
	}
	else {
		for (int i = 1; i <= max_range; ++i) {
			m_Player[i - 1].name = UD_getString(StringUtils::format("p%d_name", i).c_str());
			m_Player[i - 1].score = UD_getInt(StringUtils::format("p%d_score", i).c_str());
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
		for (int i = 0; i < max_range; ++i) {
			if (m_Player[i].name == m_Player[max_range].name) {
				m_Player[i].score = m_Player[i].score>m_Player[max_range].score ? m_Player[i].score : m_Player[max_range].score;
				isExist = true;
				break;
			}
		}

		if (!isExist) {
			for(int i = 0; i < max_range; ++i) {
				for (int j = max_range - i; j > 0; j--) {
					if (m_Player[j].score > m_Player[j - 1].score) {
						Player temp;
						temp = m_Player[j];
						m_Player[j] = m_Player[j - 1];
						m_Player[j - 1] = temp;
					}
				}
			}
		}
		for (int i = 1; i <= max_range; ++i) {
			UD_setString(StringUtils::format("p%d_name", i).c_str(), m_Player[i - 1].name);
			UD_setInt(StringUtils::format("p%d_score", i).c_str(), m_Player[i - 1].score);
		}
	}
			  break;
	case 103: {
		tsm->goOpenScene();
	}
			  break;
	}

}