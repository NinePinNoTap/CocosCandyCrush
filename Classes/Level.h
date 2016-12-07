#pragma once

#include <vector>

class Level
{
public:
	Level();
	~Level();

	Level(int width, int height, std::vector<int> data);

	void getWidth(int& width) const;
	void getHeight(int& height) const;
	void getData(std::vector<int>& data) const;

private:
	int m_width;
	int m_height;
	std::vector<int> m_data;
};

