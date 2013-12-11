#include "LLKAssets.h"


LLKAssets::LLKAssets(void)
{
}


LLKAssets::~LLKAssets(void)
{
}

void LLKAssets::initAssests()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("point.plist");
}

