#ifndef _LLK_LOGIC_H_
#define _LLK_LOGIC_H_ 
#include "Icon.h"
#include "GameMap.h"


/************************************  连连看判断逻辑类  ******************************************/

class LLKLogic
{
public:

	/** 判断是否可连上消失*/
	static bool canFadeAway(Icon*& first,Icon*& second);

private:

	/** 直线连法*/
	static bool checkLine(Icon*& first,Icon*& second);

	/** 一拐点连法*/
	static bool checkOneCorner(Icon*& first,Icon*& second);

	/** 二拐点连法*/
	static bool checkTwoCorner(Icon*& first,Icon*& second);
};

#endif //_LLK_LOGIC_H_
