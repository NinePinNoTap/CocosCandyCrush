#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "GameBoard.h"
#include "LevelManager.h"

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

	// Load levels
	LevelManager* levelManager = LevelManager::getInstance();
	levelManager->loadLevel("level1", "levels/level_1.json");
	levelManager->loadLevel("level2", "levels/level_2.json");

	// Gameboard
	auto gameBoard = new GameBoard;
	gameBoard->initialise("level2");
	this->addChild(gameBoard);

	// Center the board in the layer
	gameBoard->setPosition((origin + static_cast<Vec2>(visibleSize)) / 2.0f);

	// Play background music
	SimpleAudioEngine::getInstance()->playBackgroundMusic("sounds/background.mp3");

    return true;
}