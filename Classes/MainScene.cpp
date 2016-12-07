#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "GameLayer.h"
#include "Global.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();

    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Game Layer
	auto gameLayer = GameLayer::create();
	this->addChild(gameLayer);

	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/background.mp3");

    return true;
}