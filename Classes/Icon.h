#ifndef _ICON_H_
#define _ICON_H_ 

#include "cocos2d.h"
USING_NS_CC;

/************************************  Icon图标类  ******************************************/

/** 选中状态枚举*/
enum ICON_SEL
{
	SELECTED = 0,
	UN_SELECTED
};


class Icon : public Sprite
{
public:
	Icon(void);
	~Icon(void);

	virtual bool init();
	
	/** Icon行*/
	CC_SYNTHESIZE_PASS_BY_REF(int,row,Row);
	
	/** Icon列*/
	CC_SYNTHESIZE_PASS_BY_REF(int,col,Col);
	
	/** Icon是否销毁*/
	CC_SYNTHESIZE_PASS_BY_REF(bool,destroyed,Destroyed);	

	CREATE_FUNC(Icon);

public:

	/** 初始icon皮肤*/
	void initSkinWithType(const int& type);

	/** 点击替换选中或非选中的皮肤*/
	void changeIconViewWithType(ICON_SEL type);

	/** 移除时的动画效果*/
	void fadeOutAction(float dt);

	/** 更新坐标点*/
	void updatePosintInParant();

	/** 释放处理*/
	void dispose();

	/** 动画效果*/
	void playAction();

	/** 动画效果*/
	void unplayAction();

	/** 获取Icon的Type类型*/
	const int& getIconType();

private:

	/** icon的类型*/
	 int iconType;

};

#endif // _ICON_H_

