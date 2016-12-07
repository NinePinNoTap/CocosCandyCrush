#pragma once

#include <cocos2d.h>
#include <json\document.h>
#include <map>
#include <string>
#include <vector>

#include "Level.h"

class LevelManager
{
public:
	LevelManager();
	~LevelManager();

	void loadLevel(std::string levelName, std::string fileLocation);

	Level* getLevel(std::string levelName) const;

	static LevelManager* getInstance();

private:

	static LevelManager* m_instance;

	std::map<std::string, Level*> m_levels;
};

