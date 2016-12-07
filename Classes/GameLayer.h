#pragma once

#include "cocos2d.h"
#include "GameBoard.h"

class GameLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);

private:
	// [Touch]
	virtual bool onTouchBegan(cocos2d::Touch * touch, cocos2d::Event * evnt);
	virtual void onTouchMoved(cocos2d::Touch * touch, cocos2d::Event * evnt);
	virtual void onTouchEnded(cocos2d::Touch * touch, cocos2d::Event * evnt);
	virtual void onTouchCancelled(cocos2d::Touch * touch, cocos2d::Event * evnt);

	Candy* getCandyAtTouch(const cocos2d::Vec2 touchPosition);

	cocos2d::Size m_screenSize;
	cocos2d::Vec2 m_layerOffset;
	GameBoard* m_board = nullptr;

	cocos2d::Vec2 m_touchPosition;
	Candy* m_firstCandy = nullptr;
	Candy* m_secondCandy = nullptr;
};