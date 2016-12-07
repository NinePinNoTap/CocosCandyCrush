#pragma once

#include <cocos2d.h>

enum CandyType
{
	Empty,
	Blue, Green, Orange, Pink, Purple, Red, White, Yellow, 
	Count
};

class Candy : public cocos2d::Node
{
public:
	Candy();
	~Candy();
	
	// [Properties]
	void setIndex(int index);
	void setRow(int row);
	void setColumn(int column);

	int getIndex() const;
	int getRow() const;
	int getColumn() const;

	// [Candy]
	void setRandom();
	void setType(CandyType type);

	CandyType getColour() const;

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

	cocos2d::Sprite* m_sprite = nullptr;
};