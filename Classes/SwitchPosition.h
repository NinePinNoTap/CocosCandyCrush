#pragma once

#include <cocos2d.h>

class SwitchPosition : public cocos2d::ActionInterval
{
public:
	SwitchPosition() {}
	virtual ~SwitchPosition() {}

	static SwitchPosition* create(float duration, cocos2d::Node* nodeA, cocos2d::Node* nodeB, bool reverseAction = false);

	virtual void update(float dt) override;

private:
	bool initWithDuration(float duration, cocos2d::Node* nodeA, cocos2d::Node* nodeB, bool reverseAction);
};

