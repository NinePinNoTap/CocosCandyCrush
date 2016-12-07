#pragma once

#include <cocos2d.h>

enum CandyType
{
	Empty,
	Blue, Green, Orange, Pink, Purple, Red, White, Yellow, 
	Count
};

enum CandyBonus
{
	None,
	DoublePoints
};

class Candy : public cocos2d::Node
{
public:
	Candy();
	~Candy();

	// [Sprite]
	cocos2d::Sprite* getSprite();
	cocos2d::Size getSize() const;

	// [Properties]
	void setIndex(int index);
	void setRow(int row);
	void setColumn(int column);
	int getIndex() const;
	int getRow() const;
	int getColumn() const;

	// [Candy]
	void setRandom();
	void dropCandyIntoGame(float height);
	void setAttributes(CandyType colour, CandyBonus bonus);

	CandyType getColour() const;
	CandyBonus getBonus() const;

	// [Destruction]
	void setEmpty();
	bool isEmpty() const;

	// [Swap Checks]
	bool isSameColour(const Candy* candy) const;
	
private:
	int m_index = 0;
	int m_row = 0;
	int m_column = 0;

	CandyType m_type = CandyType::Empty;
	CandyBonus m_bonus = CandyBonus::None;

	cocos2d::Sprite* m_sprite = nullptr;
	cocos2d::Size m_tileSize;
};