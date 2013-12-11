#include "Icon.h"


Icon::Icon(void)
{
}


Icon::~Icon(void)
{
}
bool Icon::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	return true;
}

void Icon::initSkinWithType(const int& type)
{
	String* iconFrameName	=	String::createWithFormat("point%d.png",type); 
	iconType				=	type;
	initWithSpriteFrameName(iconFrameName->getCString());
	setDestroyed(false);
	auto fadeInAction = FadeIn::create(1.5f);
	runAction(fadeInAction);
	setAnchorPoint(Point(0,0));
}

void Icon::changeIconViewWithType(ICON_SEL type)
{
	String* iconFrameName ;
	switch (type)
	{
	case SELECTED:
		iconFrameName = String::createWithFormat("point_h_%d.png",iconType);
		break;

	case UN_SELECTED:
		iconFrameName = String::createWithFormat("point%d.png",iconType);
		break;
	}
	initWithSpriteFrameName(iconFrameName->getCString());
	setAnchorPoint(Point(0,0));
}

void Icon::updatePosintInParant()
{
	setPosition(Point((col * getContentSize().width ),(row * getContentSize().height)));
	

}


void Icon::fadeOutAction(float dt)
{
	dispose();
	
	log("out one");
}


const int& Icon::getIconType()
{
	return iconType;
}


/** 动画效果*/
void Icon::playAction()
{

	auto actionBy = ScaleTo::create(.5f, 1.05f, 1.05f);
	auto actionByBack = ScaleTo::create(.5f, 0.95f, 0.95f);
	runAction(RepeatForever::create(Sequence::create(actionBy, actionByBack, NULL)));

}

/** 动画效果*/
void Icon::unplayAction()
{
	stopAllActions();
	auto actionByBack = ScaleTo::create(.5f, 1.0f, 1.0f);
	runAction(Sequence::create(actionByBack,NULL));
}
/** 释放处理*/
void Icon::dispose()
{
	if (this->getParent())
	{
		this->removeFromParent();
	}
}