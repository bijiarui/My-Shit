#include "SceneManager.h"
#include "LoadLayer.h"
#include "OpenLayer.h"
#include "StartLayer.h"
#include "OptionLayer.h"
#include "ClassicGameOverLayer.h"
#include "RankListLayer.h"
#include "ClassicGameScene.h"
#include "MultiPlayerScene.h"
#include "MultiPlayerGameOverLayer.h"
#include "RhythmGameScene.h"
#include "RhythmGameOverLayer.h"

void SceneManager::creatLoadScene() {
	this->loadScene = Scene::create();
	LoadLayer * layer = LoadLayer::create();
	layer->tsm = this;
	loadScene->addChild(layer);
}

void SceneManager::goOpenScene() {
	this->openScene = Scene::create();
	OpenLayer * layer = OpenLayer::create();
	layer->tsm = this;
	openScene->addChild(layer);
	auto transitions = TransitionFade::create(0.4f, openScene);
	Director::getInstance()->replaceScene(transitions);
}

void SceneManager::goStartScene() {

	this->startScene = Scene::create();
	StartLayer * layer = StartLayer::create();
	layer->tsm = this;
	startScene->addChild(layer);
	auto transitions = TransitionFade::create(0.4f, startScene);
	Director::getInstance()->replaceScene(transitions);

}
void SceneManager::goOptionScene()
{
	this->optionScene = Scene::create();
	OptionLayer * layer = OptionLayer::create();
	layer->tsm = this;
	optionScene->addChild(layer);
	auto transitions = TransitionFade::create(0.4f, optionScene);
	Director::getInstance()->replaceScene(transitions);
}

void SceneManager::goClassicGameScene()
{
	ClassicGameScene* classicGameScene = ClassicGameScene::create();
	classicGameScene->tsm = this;
	auto transitions = TransitionFade::create(0.4f, classicGameScene);
	Director::getInstance()->replaceScene(transitions);

}

void SceneManager::goClassicGameOverScene()
{
	this->classicGameOverScene = Scene::create();
	ClassicGameOverLayer * layer = ClassicGameOverLayer::create();
	layer->tsm = this;
	classicGameOverScene->addChild(layer);
	auto transitions = TransitionFade::create(0.4f, classicGameOverScene);
	Director::getInstance()->replaceScene(transitions);
}

void SceneManager::goRankListLayer()
{
	this->rankListScene = Scene::create();
	RankListLayer * layer = RankListLayer::create();
	layer->tsm = this;
	rankListScene->addChild(layer);
	auto transitions = TransitionFade::create(0.4f, rankListScene);
	Director::getInstance()->replaceScene(transitions);
}

void SceneManager::goMuitiPlayerScene()
{
	MultiPlayerScene* multiPlayersScene = MultiPlayerScene::create();
	multiPlayersScene->tsm = this;
	auto transitions = TransitionFade::create(0.4f, multiPlayersScene);
	Director::getInstance()->replaceScene(transitions);
}

void SceneManager::goMuitiPlayerGameOverScene()
{
	this->MuitiPlayerGameOverScene = Scene::create();
	MutiPlayersGameOverLayer *layer = MutiPlayersGameOverLayer::create();
	layer->tsm = this;
	MuitiPlayerGameOverScene->addChild(layer);
	auto transitions = TransitionFade::create(0.4f, MuitiPlayerGameOverScene);
	Director::getInstance()->replaceScene(transitions);
}

void SceneManager::goRhythmGameScene()
{
	RhythmGameScene* rhythmGmaeScene = RhythmGameScene::create();
	rhythmGmaeScene->tsm = this;
	auto transitions = TransitionFade::create(0.4f, rhythmGmaeScene);
	Director::getInstance()->replaceScene(transitions);
}

void SceneManager::goRhythmGameOverScene()
{
	this->RhythmGameOverScene = Scene::create();
	RhythmGameOverLayer * layer = RhythmGameOverLayer::create();
	layer->tsm = this;
	RhythmGameOverScene->addChild(layer);
	auto transitions = TransitionFade::create(0.4f, RhythmGameOverScene);
	Director::getInstance()->replaceScene(transitions);
}