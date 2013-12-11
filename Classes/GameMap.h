#ifndef _GMAE_MAP_H_
#define _GMAE_MAP_H_ 
#include "cocos2d.h"
#include "Icon.h"
USING_NS_CC;

/************************************ 游戏地图类  ******************************************/

class GameMap : public cocos2d::Layer
{
public:
	GameMap(void);
	~GameMap(void);
	virtual bool init();
	CREATE_FUNC(GameMap);

public:

	/** 设定地图初始行与列 并进行初始化地图事务*/
	void initMapWithRowAndCol(const int& row,const int& col);

	/** 获取地图实际大小*/
	Size getMapSize();

	/** 获取地图数组数据*/
	 static Array*& getMapDataArray();

	 /** 将子项提至容器最上层*/
	 void setIconToMaxTop(Icon* icon);

	  /** 从二维地图中的行与列获取一个 Icon*/
	 static Icon* getIconAtRowAndCol(const int& row,const int& col);
	
public:
	
	/** icon宽*/
	static const int iconWidth;

	/** icon高*/
	static const int iconHeight;

	/** 地图行*/
	static int mapRow;

	/** 地图列*/
	static int mapCol;

private:
	
	/** 地图实际宽*/
	int mapWidth;

	/** 地图实际高*/
	int mapHeight;

	/** icons数组*/
	static Array* mapsArray;

private:
	/** 随机打乱地图icon布局*/
	void randomMapArray(const int& repeat);

	/** 安全释放*/
	void dispose();

};
#endif //_GMAE_MAP_H_

