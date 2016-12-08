#include "GameHelper.h"
#include "CandyExplosion.h"
#include "SwitchPosition.h"

USING_NS_CC;

int GameHelper::getIndex(int x, int y, int width)
{
	return (width * y) + x;
}

cocos2d::Vec2 GameHelper::getCoordinate(int index, int width)
{
	return cocos2d::Vec2
	{
		static_cast<float>(index % width),
		static_cast<float>(index / width)
	};
}

void GameHelper::transitionSwapCandy(Candy * candyA, Candy * candyB, cocos2d::Layer * layer, bool moveSuccess)
{
	auto positionA = candyA->getPosition();
	auto positionB = candyB->getPosition();
	auto touchCallback = CallFunc::create([layer]()
	{
		layer->setTouchEnabled(true);
	});

	SwitchPosition* switchPosition = SwitchPosition::create(0.5f, candyA, candyB, !moveSuccess);

	layer->runAction(Sequence::create(switchPosition, touchCallback, nullptr));
}

void GameHelper::destroyCandy(Candy * candy)
{
	// Create the visual effect
	auto sprite = candy->getSprite();
	CandyExplosion::create("explosionblue", sprite->getPosition(), candy);

	// Destroy the sprite
	auto fadeOut = FadeOut::create(0.25f);
	auto sequence = Sequence::create(fadeOut, nullptr);
	sprite->runAction(sequence);

	candy->setEmpty();
}
