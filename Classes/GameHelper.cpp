#include "GameHelper.h"
#include "CandyExplosion.h"

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
	cocos2d::Spawn* spawn = nullptr;

	if (moveSuccess)
	{
		// Create spawn for running switch animation
		auto action1 = TargetedAction::create(candyA, EaseBounceOut::create(MoveTo::create(0.5f, positionB)));
		auto action2 = TargetedAction::create(candyB, EaseBounceOut::create(MoveTo::create(0.5f, positionA)));
		spawn = Spawn::create(action1, action2, nullptr);
	}
	else
	{
		// Candy A
		auto actionA1 = TargetedAction::create(candyA, MoveTo::create(0.25f, positionB));
		auto actionA2 = TargetedAction::create(candyA, MoveTo::create(0.25f, positionA));
		auto sequenceA = Sequence::create(actionA1, actionA2, nullptr);

		// Candy B
		auto actionB1 = TargetedAction::create(candyB, MoveTo::create(0.25f, positionA));
		auto actionB2 = TargetedAction::create(candyB, MoveTo::create(0.25f, positionB));
		auto sequenceB = Sequence::create(actionB1, actionB2, nullptr);

		spawn = Spawn::create(sequenceA, sequenceB, nullptr);
	}

	layer->runAction(Sequence::create(spawn, touchCallback, nullptr));
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
