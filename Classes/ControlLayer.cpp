#include "ControlLayer.h"

bool ControlLayer::init()
{
	
	auto listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(ControlLayer::onKeyPressed, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}


void ControlLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event * event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		m_delegate->clickRight();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		m_delegate->clickLeft();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		m_delegate->clickUp();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		m_delegate->clickDown();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_A) {
		m_delegate->clickA();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_S) {
		m_delegate->clickS();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_D) {
		m_delegate->clickD();
	}
	else if (keyCode == EventKeyboard::KeyCode::KEY_W) {
		m_delegate->clickW();
	}
}