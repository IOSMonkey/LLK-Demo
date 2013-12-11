#ifndef __In_Game_H__
#define __In_Game_H__

#include "cocos2d.h"
#include "LLKAssets.h"
#include "GameMap.h"
#include "LLKLogic.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion; 

/************************************  游戏界面类  ******************************************/

class InGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(InGame);
     bool touchBegin(Touch* touch,Event* event);

public:

	/** 初始触屏事件*/
	void initTouchEvents();

private:

	/** 游戏地图层*/
	GameMap* gameMap;

	/** 点击的第一个icon*/
	Icon* firstIcon;

	/** 点击的第二个iconicon*/
	Icon* secondIocn;

private:

	/** 前后选取的Icon指针悬垂*/
	void initSelIconToNull();

	/** 检查前后选取的Icon是否相同*/
	bool checkSelIcon(Icon* one,Icon* two);

};

#endif // __In_Game_H__
