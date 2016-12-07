#include "Level.h"

Level::Level()
{
}


Level::~Level()
{
}

Level::Level(int width, int height, std::vector<int> data)
{
	m_width = width;
	m_height = height;
	m_data = data;
}

void Level::getWidth(int & width) const
{
	width = m_width;
}

void Level::getHeight(int & height) const
{
	height = m_height;
}

void Level::getData(std::vector<int>& data) const
{
	data = m_data;
}
