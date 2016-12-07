#pragma once

#include <cocos2d.h>
#include <set>
#include <string>
#include <vector>

#include "Candy.h"
#include "LevelManager.h"

class GameBoard : public cocos2d::Node
{
public:
	GameBoard();
	~GameBoard();

	void initialise(const std::string levelName);
	
	Candy* getCandy(int x, int y);

private:
	// [Properties]
	int m_width = 1;
	int m_height = 1;

	// [Creation]
	Candy* createRandomCandy(int index);

	// [Positions]
	cocos2d::Vec2 m_bottomLeft;

	// [Board data]
	std::vector<Candy*> m_candy;
};