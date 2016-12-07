#include "Candy.h"

USING_NS_CC;

// [Filenames]
static std::string CandySpriteFilenames[] = {
	"candy/bean_blue.png",
	"candy/bean_green.png",
	"candy/bean_orange.png",
	"candy/bean_pink.png",
	"candy/bean_purple.png",
	"candy/bean_red.png",
	"candy/bean_white.png",
	"candy/bean_yellow.png"
};

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

void Candy::setRandom()
{
	int randomID = RandomHelper::random_int(1, static_cast<int>(CandyType::Count) - 1);
	
	setType(static_cast<CandyType>(randomID));
}

void Candy::setType(CandyType type)
{
	m_type = type;
	
	int index = static_cast<int>(type);

	m_sprite = Sprite::create(CandySpriteFilenames[index - 1]);

	this->addChild(m_sprite, 1);
}

CandyType Candy::getColour() const
{
	return m_type;
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
