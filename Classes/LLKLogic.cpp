#include "LLKLogic.h"


/** 判断是否可连上消失*/
bool LLKLogic::canFadeAway(Icon*& first,Icon*& second)
{
	if(	checkLine(first,second) || 
		checkOneCorner(first,second) ||
		checkTwoCorner(first,second	))
	{
		return true;
	}
	return false;
}
/** 直线连法*/
bool LLKLogic::checkLine(Icon*& first,Icon*& second)
{
	int dx			=	first->getRow() - second->getRow();
	int dy			=	first->getCol() - second->getCol();
	int next		=	0;
	Icon* getNext	=	NULL;
	if (dx == 0)
	{
		for (int i = 0; i < abs(dy); i++)
		{
			if (dy < 0) next++;
				else	next--;
			getNext = GameMap::getIconAtRowAndCol(first->getRow(),first->getCol() + next);
			if (getNext == second)
			{
				return true;
			}else if (!getNext->getDestroyed())
			{
				return false;
			}
		}
	}else if(dy == 0)
	{
		for (int i = 0; i < abs(dx); i++)
		{
			if (dx < 0) next++;
			else	next--;
			getNext = GameMap::getIconAtRowAndCol(first->getRow() + next,first->getCol());
			if (getNext == second)
			{
				return true;
			}else if (!getNext->getDestroyed())
			{
				return false;
			}
		}
	}
	return false;
}

/** 一拐点连法*/
bool LLKLogic::checkOneCorner(Icon*& first,Icon*& second)
{
	int oneCornerRow	=	first->getRow();
	int oneCornerCol	=	second->getCol();
	int twoCornerRow	=	second->getRow();
	int twoCornerCol	=	first->getCol();
	Icon* oneCornerIcon	=	GameMap::getIconAtRowAndCol(oneCornerRow,oneCornerCol);
	Icon* twoCornerIcon	=	GameMap::getIconAtRowAndCol(twoCornerRow,twoCornerCol);

	if (oneCornerIcon->getDestroyed() &&  checkLine(oneCornerIcon,first) && checkLine(oneCornerIcon,second)||
		 twoCornerIcon->getDestroyed() && checkLine(twoCornerIcon,first) && checkLine(twoCornerIcon,second))
	{
		return true;
	}
	return false;
}

/** 二拐点连法*/
bool LLKLogic::checkTwoCorner(Icon*& first,Icon*& second)
{
	Icon* getIcon	= NULL;
	int i			= 0;
	for ( i = first->getRow() + 1; i < GameMap::mapRow; i++)
	{
		getIcon	=	GameMap::getIconAtRowAndCol(i,first->getCol());
		if (!getIcon->getDestroyed())
		{
			return false;
		}else if (checkOneCorner(getIcon,second))
		{
			return true;
		}
	}
	for ( i = first->getRow() - 1; i >= 0; i--)
	{
	    getIcon	=	GameMap::getIconAtRowAndCol(i,first->getCol());
		if (!getIcon->getDestroyed())
		{
			return false;
		}else if (checkOneCorner(getIcon,second))
		{
			return true;
		}
	}
	for ( i = first->getCol() - 1; i >= 0; i--)
	{
		getIcon	=	GameMap::getIconAtRowAndCol(first->getRow(),i);
		if (!getIcon->getDestroyed())
		{
			return false;
		}else if (checkOneCorner(getIcon,second))
		{
			return true;
		}
	}
	for ( i = first->getCol() + 1; i < GameMap::mapCol; i++)
	{
		getIcon	=	GameMap::getIconAtRowAndCol(first->getRow(),i);
		if (!getIcon->getDestroyed())
		{
			return false;
		}else if (checkOneCorner(getIcon,second))
		{
			return true;
		}
	}
	return false;
}