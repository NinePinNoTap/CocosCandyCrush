#pragma once

#include <cocos2d.h>
#include <string>

class CandyExplosion
{
public:
	CandyExplosion();
	~CandyExplosion();

	static void create(const std::string filename, const cocos2d::Vec2 targetPosition, cocos2d::Node* node);
};

