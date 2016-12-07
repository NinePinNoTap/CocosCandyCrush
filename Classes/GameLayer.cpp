#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "GameHelper.h"
#include "LevelManager.h"

USING_NS_CC;

Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameLayer::create();

    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameLayer::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	Vec2 origin;
	LevelManager* levelManager = nullptr;
    
    m_screenSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

	//
	// Load Levels
	//

	levelManager = LevelManager::getInstance();
	levelManager->loadLevel("level1", "levels/level_1.json");
	levelManager->loadLevel("level2", "levels/level_2.json");
	
	// Create the gameboard
	m_board = new GameBoard;
	m_board->initialise("level2");
	this->addChild(m_board, 1);

	// Place the board in the middle of the screen
	m_layerOffset = origin + Vec2(m_screenSize.width / 2.0f, m_screenSize.height / 2.0f);
	m_board->setPosition(m_layerOffset);

	// Enable touch
	setTouchMode(cocos2d::Touch::DispatchMode::ONE_BY_ONE);
	setTouchEnabled(true);
    
    return true;
}

bool GameLayer::onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	m_touchPosition = touch->getLocation();
	m_firstCandy = getCandyAtTouch(m_touchPosition);

	return m_firstCandy != nullptr;
}

void GameLayer::onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	int otherRow, otherColumn;
	int rowDelta, colDelta;
	Candy* candyAtTouch = nullptr;

	// Ensure we have retrieve an initial candy
	if (m_firstCandy == nullptr)
	{
		onTouchBegan(touch, evnt);
		return;
	}

	// Retrieve the candy we are on
	candyAtTouch = getCandyAtTouch(touch->getLocation());
	if (candyAtTouch == m_firstCandy || candyAtTouch == nullptr)
	{
		candyAtTouch = nullptr;
		return;
	}

	// Store our working grid location
	otherRow = m_firstCandy->getRow();
	otherColumn = m_firstCandy->getColumn();

	// Calculate swipe direction
	colDelta = candyAtTouch->getColumn() - m_firstCandy->getColumn();
	rowDelta = candyAtTouch->getRow() - m_firstCandy->getRow();

	// Calculate which neighbour
	if (colDelta < 0)
		otherColumn--;
	else if (colDelta > 0)
		otherColumn++;
	else if (rowDelta < 0)
		otherRow--;
	else if (rowDelta > 0)
		otherRow++;

	// Get the other candy we are swiping to
	m_secondCandy = m_board->getCandy(otherColumn, otherRow);
	if (m_secondCandy == nullptr)
	{
		m_firstCandy = nullptr;
		return;
	}

	// Make the move
	if (m_board->canSwapCandy(m_firstCandy, m_secondCandy))
	{
		setTouchEnabled(false);

		// Swap candy properties
		m_board->swapCandy(m_firstCandy, m_secondCandy);

		// Check board for valid moves
		if (m_board->isValidMove(m_firstCandy, m_secondCandy))
		{
			// TODO
			// Refactor this into the gameboard class
			// Or move to an animation class
			GameHelper::transitionSwapCandy(m_firstCandy, m_secondCandy, this);

			auto delay = DelayTime::create(0.5f);
			auto destroyCallback = CallFunc::create([&]()
			{
				m_board->destroyMatches();
			});
			auto collapseCallback = CallFunc::create([&]()
			{
				m_board->collapseBoard();
			});

			this->runAction(Sequence::create(delay, destroyCallback, delay, collapseCallback, nullptr));
		}
		else
		{
			// Swap properties back
			m_board->swapCandy(m_firstCandy, m_secondCandy);

			// Run the animation
			GameHelper::transitionSwapCandy(m_firstCandy, m_secondCandy, this, false);

			// Re-enable touch (this should be included in the above refactoring)
			setTouchEnabled(true);
		}
	}

	onTouchEnded(touch, evnt);
}

void GameLayer::onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	m_firstCandy = nullptr;
	m_secondCandy = nullptr;
}

void GameLayer::onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * evnt)
{
	onTouchEnded(touch, evnt);
}

Candy * GameLayer::getCandyAtTouch(const cocos2d::Vec2 touchPosition)
{
	float gridX = (touchPosition.x - m_board->getGridPosition().x - m_layerOffset.x) / 70.0f;
	float gridY = (touchPosition.y - m_board->getGridPosition().y - m_layerOffset.y) / 70.0f;

	return m_board->getCandy(round(gridX), round(gridY));
}