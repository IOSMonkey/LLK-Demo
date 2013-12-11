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
	//��ʼ�ز�
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

	//��ʼ��ͼ
	gameMap			=	GameMap::create();
	gameMap->initMapWithRowAndCol(8,12);
	gameMap->setAnchorPoint(Point(0.5,0.5));
	addChild(gameMap);
	

	//gameMapΪ�˾�����ʾ ��������ƫ��
	gameMap->setPositionX((winSize.width / 2) - (gameMap->getMapSize().width / 2));
	gameMap->setPositionY((winSize.height / 2) - (gameMap->getMapSize().height / 2));

	initTouchEvents();


    return true;
}

/** ��ʼ�����¼�*/
void InGame::initTouchEvents()
{
	EventListenerTouch* touchEvent = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
	touchEvent->setSwallowTouches(true);
	touchEvent->onTouchBegan = CC_CALLBACK_2(InGame::touchBegin,this);

	//ע���¼�
	EventDispatcher::getInstance()->addEventListenerWithSceneGraphPriority(touchEvent, this);

}


bool InGame::touchBegin(Touch* touch,Event* event)
{
	//�Ƚ������껻�㣨����gameMapΪ�˾�����ʾ ����������ƫ�ƣ�
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

/** ǰ��ѡȡ��Iconָ������*/
void InGame::initSelIconToNull()
{
	firstIcon	= NULL;
	secondIocn	= NULL;
}

/** ���ǰ��ѡȡ��Icon�Ƿ���ͬ*/
inline bool InGame::checkSelIcon(Icon* one,Icon* two)
{
	return one->getIconType() == two->getIconType();
}
