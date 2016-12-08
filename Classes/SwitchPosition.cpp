#include "SwitchPosition.h"

USING_NS_CC;

SwitchPosition * SwitchPosition::create(float duration, cocos2d::Node * nodeA, cocos2d::Node * nodeB, bool reverseAction)
{
	SwitchPosition *switchPosition = new SwitchPosition();
	switchPosition->initWithDuration(duration, nodeA, nodeB, reverseAction);
	switchPosition->autorelease();

	return switchPosition;
}

void SwitchPosition::update(float dt)
{
}

bool SwitchPosition::initWithDuration(float duration, cocos2d::Node * nodeA, cocos2d::Node * nodeB, bool reverseAction)
{
	if (ActionInterval::initWithDuration(duration))
	{
		MoveTo* moveToFirst = nullptr;
		MoveTo* moveToSecond = nullptr;

		if (reverseAction)
		{
			moveToFirst = MoveTo::create(duration / 2.0f, nodeA->getPosition());
			moveToSecond = MoveTo::create(duration / 2.0f, nodeB->getPosition());

			auto firstSequence = Sequence::create(moveToSecond->clone(), moveToFirst->clone(), nullptr);
			auto secondSequence = Sequence::create(moveToFirst->clone(), moveToSecond->clone(), nullptr);

			nodeA->runAction(firstSequence);
			nodeB->runAction(secondSequence);
		}
		else
		{
			moveToFirst = MoveTo::create(duration, nodeA->getPosition());
			moveToSecond = MoveTo::create(duration, nodeB->getPosition());

			nodeA->runAction(moveToSecond);
			nodeB->runAction(moveToFirst);
		}

		return true;
	}

	return false;
}
