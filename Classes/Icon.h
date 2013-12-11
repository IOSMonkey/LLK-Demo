#ifndef _ICON_H_
#define _ICON_H_ 

#include "cocos2d.h"
USING_NS_CC;

/************************************  Iconͼ����  ******************************************/

/** ѡ��״̬ö��*/
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
	
	/** Icon��*/
	CC_SYNTHESIZE_PASS_BY_REF(int,row,Row);
	
	/** Icon��*/
	CC_SYNTHESIZE_PASS_BY_REF(int,col,Col);
	
	/** Icon�Ƿ�����*/
	CC_SYNTHESIZE_PASS_BY_REF(bool,destroyed,Destroyed);	

	CREATE_FUNC(Icon);

public:

	/** ��ʼiconƤ��*/
	void initSkinWithType(const int& type);

	/** ����滻ѡ�л��ѡ�е�Ƥ��*/
	void changeIconViewWithType(ICON_SEL type);

	/** �Ƴ�ʱ�Ķ���Ч��*/
	void fadeOutAction(float dt);

	/** ���������*/
	void updatePosintInParant();

	/** �ͷŴ���*/
	void dispose();

	/** ����Ч��*/
	void playAction();

	/** ����Ч��*/
	void unplayAction();

	/** ��ȡIcon��Type����*/
	const int& getIconType();

private:

	/** icon������*/
	 int iconType;

};

#endif // _ICON_H_

