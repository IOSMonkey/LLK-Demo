#ifndef __In_Game_H__
#define __In_Game_H__

#include "cocos2d.h"
#include "LLKAssets.h"
#include "GameMap.h"
#include "LLKLogic.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion; 

/************************************  ��Ϸ������  ******************************************/

class InGame : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(InGame);
     bool touchBegin(Touch* touch,Event* event);

public:

	/** ��ʼ�����¼�*/
	void initTouchEvents();

private:

	/** ��Ϸ��ͼ��*/
	GameMap* gameMap;

	/** ����ĵ�һ��icon*/
	Icon* firstIcon;

	/** ����ĵڶ���iconicon*/
	Icon* secondIocn;

private:

	/** ǰ��ѡȡ��Iconָ������*/
	void initSelIconToNull();

	/** ���ǰ��ѡȡ��Icon�Ƿ���ͬ*/
	bool checkSelIcon(Icon* one,Icon* two);

};

#endif // __In_Game_H__
