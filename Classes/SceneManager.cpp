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

	Director::getInstance()->replaceScene(openScene);
}

void SceneManager::goStartScene() {

	this->startScene = Scene::create();
	StartLayer * layer = StartLayer::create();
	layer->tsm = this;
	startScene->addChild(layer);

	Director::getInstance()->replaceScene(startScene);

}
void SceneManager::goOptionScene()
{
	this->optionScene = Scene::create();
	OptionLayer * layer = OptionLayer::create();
	layer->tsm = this;
	optionScene->addChild(layer);

	Director::getInstance()->replaceScene(optionScene);
}

void SceneManager::goClassicGameScene()
{
	ClassicGameScene* classicGameScene = ClassicGameScene::create();
	classicGameScene->tsm = this;

	Director::getInstance()->replaceScene(classicGameScene);

}

void SceneManager::goClassicGameOverScene()
{
	this->classicGameOverScene = Scene::create();
	ClassicGameOverLayer * layer = ClassicGameOverLayer::create();
	layer->tsm = this;
	classicGameOverScene->addChild(layer);

	Director::getInstance()->replaceScene(classicGameOverScene);
}

void SceneManager::goRankListLayer()
{
	this->rankListScene = Scene::create();
	RankListLayer * layer = RankListLayer::create();
	layer->tsm = this;
	rankListScene->addChild(layer);

	Director::getInstance()->replaceScene(rankListScene);
}

void SceneManager::goMuitiPlayerScene()
{
	MultiPlayerScene* multiPlayersScene = MultiPlayerScene::create();
	multiPlayersScene->tsm = this;

	Director::getInstance()->replaceScene(multiPlayersScene);
}

void SceneManager::goMuitiPlayerGameOverScene()
{
	this->MuitiPlayerGameOverScene = Scene::create();
	MutiPlayersGameOverLayer *layer = MutiPlayersGameOverLayer::create();
	layer->tsm = this;
	MuitiPlayerGameOverScene->addChild(layer);
	Director::getInstance()->replaceScene(MuitiPlayerGameOverScene);
}

void SceneManager::goRhythmGameScene()
{
	RhythmGameScene* rhythmGmaeScene = RhythmGameScene::create();
	rhythmGmaeScene->tsm = this;
	Director::getInstance()->replaceScene(rhythmGmaeScene);
}

void SceneManager::goRhythmGameOverScene()
{
	this->RhythmGameOverScene = Scene::create();
	RhythmGameOverLayer * layer = RhythmGameOverLayer::create();
	layer->tsm = this;
	RhythmGameOverScene->addChild(layer);

	Director::getInstance()->replaceScene(RhythmGameOverScene);
}