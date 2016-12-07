#include "CandyExplosion.h"
#include "Global.h"

USING_NS_CC;

CandyExplosion::CandyExplosion()
{
}


CandyExplosion::~CandyExplosion()
{
}

void CandyExplosion::create(const std::string filename, const cocos2d::Vec2 targetPosition, cocos2d::Node * node)
{
	Vector<SpriteFrame*> animFrames(5);
	Sprite* sprite = nullptr;
	Animation* animation = nullptr;
	Animate* animate = nullptr;
	Sequence* sequence = nullptr;

	// Load the spritesheet
	char str[100] = { 0 };
	for (int i = 1; i < 5; i++)
	{
		sprintf(str, "%02d.png", i);
		auto frame = SpriteFrame::create("effects/" + filename + str, Rect(0, 0, 164, 164));
		animFrames.pushBack(frame);
	}

	// Create animation
	animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
	animate = Animate::create(animation);
	sequence = Sequence::create(animate, RemoveSelf::create(), NULL);

	// Create sprite
	sprite = Sprite::create("effects/explosionblue01.png");
	sprite->setPosition(targetPosition);
	sprite->runAction(sequence);

	// Add to layer
	node->addChild(sprite, 1);
}
