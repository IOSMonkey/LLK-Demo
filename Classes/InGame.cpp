#include "InGame.h"

USING_NS_CC;

Scene* InGame::createScene()
{
    auto scene = Scene::create();
    auto layer = InGame::create();
    scene->addChild(layer);
    return scene;
}

bool InGame::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
	//初始素材
	LLKAssets::initAssests();
	
	Size winSize	=	Director::getInstance()->getWinSize();

	Sprite* background		=	Sprite::create("backMain.jpg");
	addChild(background);
	background->setAnchorPoint(Point(0,0));

	Sprite* alphaBackground	=	Sprite::create("gameFace.png");
	addChild(alphaBackground);
	alphaBackground->setAnchorPoint(Point(0.5f,0.5f));
	alphaBackground->setPosition(Point(winSize.width / 2,winSize.height / 2));

	initSelIconToNull();

	//初始地图
	gameMap			=	GameMap::create();
	gameMap->initMapWithRowAndCol(8,12);
	gameMap->setAnchorPoint(Point(0.5,0.5));
	addChild(gameMap);
	

	//gameMap为了居中显示 进行坐标偏移
	gameMap->setPositionX((winSize.width / 2) - (gameMap->getMapSize().width / 2));
	gameMap->setPositionY((winSize.height / 2) - (gameMap->getMapSize().height / 2));

	initTouchEvents();


    return true;
}

/** 初始触屏事件*/
void InGame::initTouchEvents()
{
	EventListenerTouch* touchEvent = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
	touchEvent->setSwallowTouches(true);
	touchEvent->onTouchBegan = CC_CALLBACK_2(InGame::touchBegin,this);

	//注册事件
	EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(touchEvent, this);

}


bool InGame::touchBegin(Touch* touch,Event* event)
{
	//先进行坐标换算（本身gameMap为了居中显示 进行了坐标偏移）
	Point converPoint		=	gameMap->convertToNodeSpace(touch->getLocation());
	
	if (converPoint.x < 0 || converPoint.y < 0)
	{
		return false;
	}		
	   	int touchRow		=	converPoint.y / GameMap::iconHeight;
	    int touchCol		=	converPoint.x / GameMap::iconWidth;

		if (touchRow >= GameMap::mapRow || touchCol >= GameMap::mapCol || touchRow < 0 || touchCol < 0 )
		{
			return true;
		}

		Icon*	getIcon		= GameMap::getIconAtRowAndCol(touchRow,touchCol);
		
		if (getIcon->getDestroyed())
		{
			return true;
		}
		getIcon->changeIconViewWithType(SELECTED);
		if (firstIcon == NULL || firstIcon == getIcon)
		{
				firstIcon	= getIcon;
				gameMap->setIconToMaxTop(firstIcon);
				firstIcon->playAction();
				SimpleAudioEngine::getInstance()->playEffect("click.wav");
				return false;
		}else if(secondIocn == NULL && getIcon != firstIcon)
		{
			secondIocn	= getIcon;
			SimpleAudioEngine::getInstance()->playEffect("click.wav");
		}	
		if( checkSelIcon(firstIcon,secondIocn))
		{
			bool bl	=	LLKLogic::canFadeAway(firstIcon,secondIocn);
			if (bl)
			{
				firstIcon->unplayAction();
				firstIcon->fadeOutAction(1.3f);
				secondIocn->fadeOutAction(1.3f);
				firstIcon->setDestroyed(true);
				secondIocn->setDestroyed(true);
				SimpleAudioEngine::getInstance()->playEffect("dis.wav");
			}
		}
			firstIcon->changeIconViewWithType(UN_SELECTED);
			secondIocn->changeIconViewWithType(UN_SELECTED);
			firstIcon->unplayAction();
			SimpleAudioEngine::getInstance()->playEffect("err.wav");
			initSelIconToNull();

	return false;
}

/** 前后选取的Icon指针悬垂*/
void InGame::initSelIconToNull()
{
	firstIcon	= NULL;
	secondIocn	= NULL;
}

/** 检查前后选取的Icon是否相同*/
inline bool InGame::checkSelIcon(Icon* one,Icon* two)
{
	return one->getIconType() == two->getIconType();
}
