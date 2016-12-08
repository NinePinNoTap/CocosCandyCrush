#include "GameBoard.h"
#include "Global.h"
#include "GameHelper.h"
#include "CandyExplosion.h"

USING_NS_CC;

GameBoard::GameBoard()
{
}

GameBoard::~GameBoard()
{
}

void GameBoard::initialise(std::string levelName)
{
	std::vector<int> data;
	Level* levelData = nullptr;

	m_screenSize = Director::getInstance()->getVisibleSize();

	// Retrieve the level
	levelData = LevelManager::getInstance()->getLevel(levelName);
	levelData->getWidth(m_width);
	levelData->getHeight(m_height);
	levelData->getData(data);

	// Calculate where grid[0][0] is
	m_bottomLeft = {
		-((m_width - 1) * 70.0f) / 2.0f,
		-((m_height - 1) * 70.0f) / 2.0f
	};

	// Generate a board of random candy
	for (int index = 0; index < data.size(); index++)
	{
		Candy* candy = nullptr;

		if (data[index] == 1)
		{
			candy = createRandomCandy(index);
			this->addChild(candy);
		}

		m_candy.push_back(candy);
	}

	// TODO
	// Processing to ensure we can actually match 
}

bool GameBoard::canSwapCandy(const Candy * candyA, const Candy * candyB) const
{
	if (candyA == nullptr || candyB == nullptr)
		return false;

	if (candyA->isEmpty() || candyB->isEmpty())
		return false;

	if (candyA == candyB)
		return false;

	return true;
}

void GameBoard::swapCandy(Candy * candyA, Candy * candyB)
{
	int row, column, index;

	// Swap within vector
	std::swap(m_candy[candyA->getIndex()], m_candy[candyB->getIndex()]);

	// Take temporary copy
	row = candyB->getRow();
	column = candyB->getColumn();
	index = candyB->getIndex();

	// Update the other with our data
	candyB->setIndex(candyA->getIndex());
	candyB->setRow(candyA->getRow());
	candyB->setColumn(candyA->getColumn());

	// Restore other candyB to our data
	candyA->setIndex(index);
	candyA->setRow(row);
	candyA->setColumn(column);
}

bool GameBoard::isValidMove(Candy * candyA, Candy * candyB)
{
	std::set<Candy*> workingSet;

	m_currentMatches.clear();

	// Candy A matches
	workingSet = checkForMatches(candyA->getColumn(), candyA->getRow());
	m_currentMatches.insert(workingSet.begin(), workingSet.end());

	// Candy B matches
	workingSet = checkForMatches(candyB->getColumn(), candyB->getRow());
	m_currentMatches.insert(workingSet.begin(), workingSet.end());

	return m_currentMatches.size() > 0;
}

void GameBoard::destroyMatches()
{
	for(std::set<Candy*>::iterator it = m_currentMatches.begin(); it != m_currentMatches.end(); it++)
	{
		GameHelper::destroyCandy(static_cast<Candy*>(*it));
	}
}

Candy * GameBoard::getCandy(int x, int y)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		int index = GameHelper::getIndex(x, y, m_width);

		return m_candy.at(index);
	}

	return nullptr;
}

cocos2d::Vec2 GameBoard::getGridPosition() const
{
	return m_bottomLeft;
}

void GameBoard::collapseBoard()
{
	std::set<int> collapsedColumns;
	int column;

	// Collapse unprocessed columns
	for (std::set<Candy*>::iterator it = m_currentMatches.begin(); it != m_currentMatches.end(); it++)
	{
		column = (*it)->getColumn();

		if (collapsedColumns.count(column) == 0)
		{
			collapseColumn(column);
			collapsedColumns.insert(column);
		}
	}

	m_currentMatches.clear();
}

void GameBoard::collapseColumn(int column)
{
	cocos2d::Vector<FiniteTimeAction*> spawns;

	for (int y = 0; y < m_height; y++)
	{
		Candy* emptyCandy = getCandy(column, y);
		if (emptyCandy == nullptr)
			continue;

		// Ensure its not taken by a coloured candy
		if(emptyCandy->isEmpty())
		{
			// Search upwards to find a candy to pull it down
			for (int row = y + 1; row < m_height; row++)
			{
				Candy* takenCandy = getCandy(column, row);
				if (takenCandy == nullptr)
					continue;

				if (takenCandy->isEmpty())
					continue;

				// Get the world position of the tile
				auto takenTilePosition = takenCandy->getPosition();
				auto emptyTilePosition = emptyCandy->getPosition();
				
				// Swap data
				swapCandy(emptyCandy, takenCandy);

				// Animate the taken tile into its new position
				spawns.pushBack(TargetedAction::create(takenCandy, EaseBackOut::create(MoveTo::create(Global::MoveAnimationDuration, emptyCandy->getPosition()))));
				emptyCandy->setPosition(takenCandy->getPosition());

				break;
			}
		}
	}

	if (spawns.size() > 0)
	{
		auto spawn = Spawn::create(spawns);
		auto sequence = Sequence::create(spawn, CallFunc::create([&]()
		{
			this->fillBoard();
		}),
			nullptr);

		this->runAction(sequence);
	}
	else
	{
		fillBoard();
	}
}

std::set<Candy*> GameBoard::checkForMatches(int x, int y)
{
	std::set<Candy*> matches, horizontalMatches, verticalMatches;
	Candy *target, *leftNeighbour, *rightNeighbour, *upNeighbour, *downNeighbour;
	
	// Retrieve the current target and its neighbours
	target = getCandy(x, y);
	leftNeighbour = getCandy(x - 1, y);
	rightNeighbour = getCandy(x + 1, y);
	upNeighbour = getCandy(x, y + 1);
	downNeighbour = getCandy(x, y - 1);

	// Radiate outwards until all neighbours do not match
	for (int distance = 2; distance < std::max(m_width, m_height); distance++)
	{
		// We have stopped the chain
		if (leftNeighbour == nullptr && rightNeighbour == nullptr && upNeighbour == nullptr && downNeighbour == nullptr)
			break;

		// Check for matches
		if (target->isSameColour(leftNeighbour))
		{
			horizontalMatches.insert(leftNeighbour);
			leftNeighbour = getCandy(x - distance, y);
		}

		if (target->isSameColour(rightNeighbour))
		{
			horizontalMatches.insert(rightNeighbour);
			rightNeighbour = getCandy(x + distance, y);
		}

		if (target->isSameColour(upNeighbour))
		{
			verticalMatches.insert(upNeighbour);
			upNeighbour = getCandy(x, y + distance);
		}

		if (target->isSameColour(downNeighbour))
		{
			verticalMatches.insert(downNeighbour);
			downNeighbour = getCandy(x, y - distance);
		}
	}

	horizontalMatches.insert(target);
	verticalMatches.insert(target);

	if (horizontalMatches.size() >= Global::ChainLength)
		matches.insert(horizontalMatches.begin(), horizontalMatches.end());

	if(verticalMatches.size() >= Global::ChainLength)
		matches.insert(verticalMatches.begin(), verticalMatches.end());

	return matches;
}

void GameBoard::fillBoard()
{
	std::set <Candy*> emptySlots;

	for (int x = 0; x < m_width; x++)
	{
		for (int y = m_height - 1; y >= 0; y--)
		{
			Candy* candy = getCandy(x, y);

			if (candy == nullptr)
				continue;

			if (candy->isEmpty())
			{
				emptySlots.insert(candy);
				continue;
			}

			break;
		}
	}

	cocos2d::Vec2 topRightWorldPos(m_screenSize.width, m_screenSize.height);

	cocos2d::Vec2 topRightLocalToBoard = this->convertToNodeSpace(topRightWorldPos);
	
	for (std::set<Candy*>::iterator it = emptySlots.begin(); it != emptySlots.end(); it++)
	{
		Candy* candy = static_cast<Candy*>(*it);
		candy->setRandom();
		candy->dropCandyIntoGame(topRightLocalToBoard.y + (candy->getRow() * candy->getSize().height));
	}
}

Candy * GameBoard::createRandomCandy(int index)
{
	Candy* candy = nullptr;
	cocos2d::Vec2 worldPos;
	cocos2d::Vec2 grid;

	grid = GameHelper::getCoordinate(index, m_width);

	// Create the base candy
	candy = new Candy;
	candy->setIndex(index);
	candy->setColumn(grid.x);
	candy->setRow(grid.y);
	candy->setRandom();

	// Set tile position in screen
	worldPos = m_bottomLeft + cocos2d::Vec2(candy->getSize().width * grid.x, candy->getSize().height * grid.y);
	candy->setPosition(worldPos);

	return candy;
}