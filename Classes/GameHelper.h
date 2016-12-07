#pragma once

#include <cocos2d.h>

#include "Candy.h"
#include "Global.h"

class GameHelper
{
public:
	static int getIndex(int x, int y, int width);
	static cocos2d::Vec2 getCoordinate(int index, int width);
	static void transitionSwapCandy(Candy* candyA, Candy* candyB, cocos2d::Layer* layer, bool success = true);
	static void destroyCandy(Candy* candy);
};

