#include "GameBoard.h"
#include "LevelManager.h"

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

Candy * GameBoard::getCandy(int x, int y)
{
	if (x >= 0 && x < m_width && y >= 0 && y < m_height)
	{
		int index = (y * m_width) + x;

		return m_candy.at(index);
	}

	return nullptr;
}

Candy * GameBoard::createRandomCandy(int index)
{
	Candy* candy = nullptr;
	cocos2d::Vec2 worldPos;
	int x, y;

	x = index % m_width;
	y = index / m_width;

	// Create the base candy
	candy = new Candy;
	candy->setIndex(index);
	candy->setColumn(x);
	candy->setRow(y);
	candy->setRandom();

	// Set tile position in screen
	worldPos = m_bottomLeft + cocos2d::Vec2(70.0f * x, 70.0f * y);
	candy->setPosition(worldPos);

	return candy;
}