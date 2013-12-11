#ifndef _GMAE_MAP_H_
#define _GMAE_MAP_H_ 
#include "cocos2d.h"
#include "Icon.h"
USING_NS_CC;

/************************************ ��Ϸ��ͼ��  ******************************************/

class GameMap : public cocos2d::Layer
{
public:
	GameMap(void);
	~GameMap(void);
	virtual bool init();
	CREATE_FUNC(GameMap);

public:

	/** �趨��ͼ��ʼ������ �����г�ʼ����ͼ����*/
	void initMapWithRowAndCol(const int& row,const int& col);

	/** ��ȡ��ͼʵ�ʴ�С*/
	Size getMapSize();

	/** ��ȡ��ͼ��������*/
	 static Array*& getMapDataArray();

	 /** �����������������ϲ�*/
	 void setIconToMaxTop(Icon* icon);

	  /** �Ӷ�ά��ͼ�е������л�ȡһ�� Icon*/
	 static Icon* getIconAtRowAndCol(const int& row,const int& col);
	
public:
	
	/** icon��*/
	static const int iconWidth;

	/** icon��*/
	static const int iconHeight;

	/** ��ͼ��*/
	static int mapRow;

	/** ��ͼ��*/
	static int mapCol;

private:
	
	/** ��ͼʵ�ʿ�*/
	int mapWidth;

	/** ��ͼʵ�ʸ�*/
	int mapHeight;

	/** icons����*/
	static Array* mapsArray;

private:
	/** ������ҵ�ͼicon����*/
	void randomMapArray(const int& repeat);

	/** ��ȫ�ͷ�*/
	void dispose();

};
#endif //_GMAE_MAP_H_

