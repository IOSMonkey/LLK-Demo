#include "GameMap.h"


/** icon��*/
const int GameMap::iconWidth	= 45;
/** icon��*/
const int GameMap::iconHeight	= 51;
/** ��ͼ��*/
int GameMap::mapRow				= 0;
/** ��ͼ��*/
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

/** �趨��ͼ��ʼ������ �����г�ʼ����ͼ����*/
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
			//��¼icon��ǰλ��
			meIcon->setRow(i);
			meIcon->setCol(j);

			Icon* iconClone = Icon::create();
			iconClone->initSkinWithType(type);
			
			addChild(iconClone);
			//ע�������++j
			iconClone->setPosition(Point( ++j * meIcon->getContentSize().width ,
										i * meIcon->getContentSize().height ));
			//��¼iconClone��ǰλ��
			iconClone->setRow(i);
			iconClone->setCol(j);

			temp->addObject(meIcon);
			temp->addObject(iconClone);
		}
	}
	randomMapArray(20);//�������icon  100��
}

 /** ������ҵ�ͼicon����*/
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
		
		//���������������е���������
		Point tempPoint	=	Point(oneIcon->getRow(),oneIcon->getCol());
		oneIcon->setRow(twoIcon->getRow());
		oneIcon->setCol(twoIcon->getCol());
		twoIcon->setRow(tempPoint.x);
		twoIcon->setCol(tempPoint.y);
		
		//�����������е���������
		Icon	temp	=	*oneIcon;
		*oneIcon		=	*twoIcon;
		*twoIcon		=	temp;

		oneIcon->updatePosintInParant();
		twoIcon->updatePosintInParant();

	}

}


/** ��ȡ��ͼʵ�ʴ�С*/
Size GameMap::getMapSize()
{
	return Size(mapWidth,mapHeight);
}


/** ��ȡ��ͼ��������*/
 Array*& GameMap::getMapDataArray()
{
	return mapsArray;
}

 /** �����������������ϲ�*/
void GameMap::setIconToMaxTop(Icon* icon)
{
	removeChild(icon);
	addChild(icon,this->getChildrenCount());
}

/** �Ӷ�ά��ͼ�е������л�ȡһ�� Icon*/
Icon* GameMap::getIconAtRowAndCol(const int& row,const int& col)
{
	Array* oneArray	=	(Array*)(mapsArray->getObjectAtIndex(row));
	Icon* getIcon	=	(Icon*)(oneArray->getObjectAtIndex(col));
	return getIcon;
}

/** ��ȫ�ͷ�*/
void GameMap::dispose()
{
	CC_SAFE_DELETE_ARRAY(mapsArray);
}


