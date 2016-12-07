#pragma once

#include <cocos2d.h>
#include <string>

class Global
{
public:
	// [Duration]
	static float MoveAnimationDuration;
	
	// [Board]
	static int ChainLength;
	
	// [Filenames]
	static const std::string CandySpriteFilenames[];
	static const std::string BonusCandySpriteFilenames[];
};

