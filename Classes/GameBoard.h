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

	bool canSwapCandy(const Candy* candyA, const Candy* candyB) const;
	void swapCandy(Candy* candyA, Candy* candyB);
	bool isValidMove(Candy* a, Candy* b);

	void destroyMatches();
	void collapseBoard();

	Candy* getCandy(int x, int y);
	cocos2d::Vec2 getGridPosition() const;

private:
	void collapseColumn(int column);
	std::set<Candy*> checkForMatches(int x, int y);
	void fillBoard();

	// [Properties]
	int m_width = 1;
	int m_height = 1;

	// [Creation]
	Candy* createRandomCandy(int index);

	// [Positions]
	cocos2d::Vec2 m_bottomLeft;
	cocos2d::Size m_screenSize;

	std::set<Candy*> m_currentMatches;
	std::vector<Candy*> m_candy;
};