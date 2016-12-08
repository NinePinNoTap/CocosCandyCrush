#include "Candy.h"
#include "Global.h"

USING_NS_CC;

Candy::Candy()
{
	
}

Candy::~Candy()
{
	
}

void Candy::setIndex(int index)
{
	m_index = index;
}

void Candy::setRow(int row)
{
	m_row = row;
}

void Candy::setColumn(int column)
{
	m_column = column;
}

int Candy::getIndex() const
{
	return m_index;
}

int Candy::getRow() const
{
	return m_row;
}

int Candy::getColumn() const
{
	return m_column;
}

cocos2d::Sprite * Candy::getSprite()
{
	return m_sprite;
}

cocos2d::Size Candy::getSize() const
{
	return m_tileSize;
}

void Candy::setRandom()
{
	int randomID = RandomHelper::random_int(1, static_cast<int>(CandyType::Count) - 1);
	
	setAttributes(static_cast<CandyType>(randomID), CandyBonus::None);
}

void Candy::dropCandyIntoGame(float height)
{
	if (m_sprite == nullptr)
		return;

	m_sprite->setPositionY(height);
	
	m_sprite->runAction(EaseCubicActionOut::create(MoveTo::create(Global::MoveAnimationDuration, Vec2::ZERO)));
}

void Candy::setAttributes(CandyType colour, CandyBonus bonus)
{
	if (m_sprite != nullptr)
	{
		m_sprite->runAction(RemoveSelf::create());
	}

	int index;

	m_type = colour;
	m_bonus = bonus;

	index = static_cast<int>(colour);

	switch (m_bonus)
	{
	case CandyBonus::None:
		m_sprite = Sprite::create(Global::CandySpriteFilenames[index - 1]);
		break;

	case CandyBonus::DoublePoints:
		m_sprite = Sprite::create(Global::BonusCandySpriteFilenames[index - 1]);
		break;

	default:
		std::logic_error("Incorrect bonus found!");
		break;
	}

	m_tileSize = m_sprite->getContentSize();

	this->addChild(m_sprite, 1);
}

CandyType Candy::getColour() const
{
	return m_type;
}

CandyBonus Candy::getBonus() const
{
	return m_bonus;
}

bool Candy::isSameColour(const Candy * candy) const
{
	if (candy == nullptr)
		return false;

	return m_type == candy->m_type;
}

void Candy::setEmpty()
{
	m_type = CandyType::Empty;
}

bool Candy::isEmpty() const
{
	return m_type == CandyType::Empty;
}
