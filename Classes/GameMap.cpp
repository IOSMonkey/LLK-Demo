#include "GameMap.h"


/** icon宽*/
const int GameMap::iconWidth	= 45;
/** icon高*/
const int GameMap::iconHeight	= 51;
/** 地图行*/
int GameMap::mapRow				= 0;
/** 地图列*/
int GameMap::mapCol				= 0;
Array* GameMap::mapsArray = Array::create();

GameMap::GameMap(void)
{
}
GameMap::~GameMap(void)
{
	dispose();
}

 bool GameMap::init()
 {
	 if (!CCLayer::init())
	 {
		 
		 return false;
	 }
	mapsArray->retain();
	
	return true;
 }

/** 设定地图初始行与列 并进行初始化地图事务*/
void GameMap::initMapWithRowAndCol(const int& row,const int& col)
{
	
	mapRow					=	row;
	mapCol					=	col;
	mapWidth				=	mapCol * iconWidth;
	mapHeight				=	mapRow * iconHeight;

	for (int i = 0; i < mapRow ; i++)
	{
		Array*	temp	=	Array::create();
		temp->retain();
		mapsArray->addObject(temp);
		for (int j = 0; j < mapCol ; j++)
		{
			if (i == 0 || i == mapRow - 1 || j == 0 || j == mapCol - 1 )
			{
				Icon* nullIcon	=	Icon::create();
				nullIcon->initSkinWithType(1);
				temp->addObject(nullIcon);
				nullIcon->setPosition(Point(j * nullIcon->getContentSize().width ,
					i * nullIcon->getContentSize().height ));
				addChild(nullIcon);
				nullIcon->setVisible(false);
				nullIcon->setDestroyed(true);
				nullIcon->setRow(i);
				nullIcon->setCol(j);
				continue;
			}
			int type = CCRANDOM_0_1() * 35 + 1;
			Icon* meIcon		=	Icon::create();
			meIcon->initSkinWithType(type);
			addChild(meIcon);
			
			meIcon->setPosition(Point(j * meIcon->getContentSize().width ,
									i * meIcon->getContentSize().height ));
			//记录icon当前位置
			meIcon->setRow(i);
			meIcon->setCol(j);

			Icon* iconClone = Icon::create();
			iconClone->initSkinWithType(type);
			
			addChild(iconClone);
			//注意这里的++j
			iconClone->setPosition(Point( ++j * meIcon->getContentSize().width ,
										i * meIcon->getContentSize().height ));
			//记录iconClone当前位置
			iconClone->setRow(i);
			iconClone->setCol(j);

			temp->addObject(meIcon);
			temp->addObject(iconClone);
		}
	}
	randomMapArray(20);//随机打乱icon  100次
}

 /** 随机打乱地图icon布局*/
void GameMap::randomMapArray(const int& repeat)
{
	unsigned int maxRow	=	mapsArray->count();
	unsigned int maxCol	=	((Array*)(mapsArray->getObjectAtIndex(0)))->count();


	for (int i = 0; i < repeat; i++)
	{
		int indexOneRow	=	CCRANDOM_0_1() * (maxRow - 2) + 1;
		int indexOneCol	=	CCRANDOM_0_1() * (maxCol - 2) + 1;
		int indexTwoRow	=	CCRANDOM_0_1() * (maxRow - 2) + 1;
		int indexTwoCol	=	CCRANDOM_0_1() * (maxCol - 2) + 1  ;
		log("--random row: %d random col: %d",indexOneRow,indexOneCol);
		log("++random row: %d random col: %d",indexTwoRow,indexTwoCol);
		log("   ");

		Icon*	oneIcon	=	getIconAtRowAndCol(indexOneRow,indexOneCol);
		Icon*	twoIcon	=	getIconAtRowAndCol(indexTwoRow,indexTwoCol);
		
		//对象数据在数组中的两两交换
		Point tempPoint	=	Point(oneIcon->getRow(),oneIcon->getCol());
		oneIcon->setRow(twoIcon->getRow());
		oneIcon->setCol(twoIcon->getCol());
		twoIcon->setRow(tempPoint.x);
		twoIcon->setCol(tempPoint.y);
		
		//对象在数组中的两两交换
		Icon	temp	=	*oneIcon;
		*oneIcon		=	*twoIcon;
		*twoIcon		=	temp;

		oneIcon->updatePosintInParant();
		twoIcon->updatePosintInParant();

	}

}


/** 获取地图实际大小*/
Size GameMap::getMapSize()
{
	return Size(mapWidth,mapHeight);
}


/** 获取地图数组数据*/
 Array*& GameMap::getMapDataArray()
{
	return mapsArray;
}

 /** 将子项提至容器最上层*/
void GameMap::setIconToMaxTop(Icon* icon)
{
	removeChild(icon);
	addChild(icon,this->getChildrenCount());
}

/** 从二维地图中的行与列获取一个 Icon*/
Icon* GameMap::getIconAtRowAndCol(const int& row,const int& col)
{
	Array* oneArray	=	(Array*)(mapsArray->getObjectAtIndex(row));
	Icon* getIcon	=	(Icon*)(oneArray->getObjectAtIndex(col));
	return getIcon;
}

/** 安全释放*/
void GameMap::dispose()
{
	CC_SAFE_DELETE_ARRAY(mapsArray);
}


