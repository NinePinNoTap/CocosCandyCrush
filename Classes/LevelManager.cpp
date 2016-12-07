#include "LevelManager.h"

LevelManager* LevelManager::m_instance = nullptr;

USING_NS_CC;

LevelManager::LevelManager()
{
}

LevelManager::~LevelManager()
{
}

void LevelManager::loadLevel(std::string levelName, std::string fileLocation)
{
	rapidjson::Document document;
	cocos2d::Data fileData;
	std::string fileContent;
	rapidjson::Value layout;
	int width, height;
	std::vector<int> data;

	fileData = FileUtils::getInstance()->getDataFromFile(fileLocation.c_str());
	fileContent = std::string((const char*)fileData.getBytes(), fileData.getSize());

	document.Parse<0>(fileContent.c_str());

	assert(document.HasMember("width"));
	assert(document.HasMember("height"));
	assert(document.HasMember("layout"));

	width = document["width"].GetInt();
	height = document["height"].GetInt();
	layout = document["layout"];

	for (unsigned int y = 0; y < layout.Size(); y++)
	{
		rapidjson::Value& row = layout[y];
		for (unsigned int x = 0; x < row.Size(); x++)
		{
			data.push_back(row[x].GetInt());
		}
	}

	assert(data.size() == (width * height));

	m_levels.insert(std::pair<std::string, Level*>(levelName, new Level(width, height, data)));

	data.clear();
}

Level * LevelManager::getLevel(std::string levelName) const
{
	std::map<std::string, Level*>::const_iterator it;
	Level* level = nullptr;

	it = m_levels.find(levelName);

	if (it == m_levels.end())
		std::logic_error("No map found! Check resources!");

	level = static_cast<Level*>(it->second);

	return level;
}

LevelManager * LevelManager::getInstance()
{
	if (m_instance == nullptr)
		m_instance = new LevelManager;

	return m_instance;
}
