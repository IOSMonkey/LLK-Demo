#ifndef _LLK_LOGIC_H_
#define _LLK_LOGIC_H_ 
#include "Icon.h"
#include "GameMap.h"


/************************************  �������ж��߼���  ******************************************/

class LLKLogic
{
public:

	/** �ж��Ƿ��������ʧ*/
	static bool canFadeAway(Icon*& first,Icon*& second);

private:

	/** ֱ������*/
	static bool checkLine(Icon*& first,Icon*& second);

	/** һ�յ�����*/
	static bool checkOneCorner(Icon*& first,Icon*& second);

	/** ���յ�����*/
	static bool checkTwoCorner(Icon*& first,Icon*& second);
};

#endif //_LLK_LOGIC_H_
