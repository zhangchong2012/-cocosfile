#ifndef __UTILITY_H__
#define __UTILITY_H__
#include <cmath>
#include <vector>
#include <list>
#include "cocos2d.h"
#include "Constant.h"

using namespace cocos2d;

inline CCPoint getPosByRowAndCol(int row, int col);
inline RowCol getRowColByPos(int posX, int posY);

inline bool isValidPos(int row, int col);
inline bool isValidPos(RowCol rowCol);
inline void getAroud(int row, int col, std::vector<RowCol>& vecRowCol);

inline void getGoldenLine(int row, int col, ROWCOL_LIST& listRowCol);
inline void getSliverLine(int row, int col, ROWCOL_LIST& listRowCol);

CCPoint getPosByRowAndCol(int row, int col){
	float posX, posY;
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	posX = col * 2 * BUBBLE_RADIUS + BUBBLE_RADIUS + (row % 2) * BUBBLE_RADIUS;
	posY = winSize.height - (row * 2 * BUBBLE_RADIUS * sin(PI/3) + BUBBLE_RADIUS);
	
	return ccp(posX, posY);
}

RowCol getRowColByPos(int posX, int posY){
	int y = CCDirector::sharedDirector()->getWinSize().height - posY;
	int row = (y - BUBBLE_RADIUS)/(2 * BUBBLE_RADIUS * sin(PI /3 )) + 0.5;
	int col = (y - (row % 2) * BUBBLE_RADIUS - BUBBLE_RADIUS)/(2 * BUBBLE_RADIUS) + 0.5;
	return RowCol(row, col);
}

bool isValidPos(RowCol rowCol){
	return isValidPos(rowCol.m_Row, rowCol.m_Col);
}

bool isValidPos(int row, int col){
	if(row < 0 || col <0){
		return false;
	}

	if(row >= MAX_ROWS || col >= MAX_COLS - row %2){
		return false;
	}

	return true;
}

void getAroud(int row, int col, std::vector<RowCol>& vecRowCol){
	if(!isValidPos(row, col)){
		return;
	}

	if(isValidPos(row, col - 1))
		vecRowCol.push_back(RowCol(row, col-1));
	if(isValidPos(row, col + 1))
		vecRowCol.push_back(RowCol(row, col+1));

	if(isValidPos(row -1, col))
		vecRowCol.push_back(RowCol(row-1, col));
	if(isValidPos(row + 1, col))
		vecRowCol.push_back(RowCol(row + 1, col));

	int curCol;
	if(row%2 == 0){
		curCol = col - 1;
	}else{
		curCol = col + 1;
	}


	if(isValidPos(row - 1, curCol)){
		vecRowCol.push_back(RowCol(row - 1, curCol));
	}
	if(isValidPos(row + 1, curCol)){
		vecRowCol.push_back(RowCol(row + 1, curCol));
	}
}

void getGoldenLine(int row, int col, ROWCOL_LIST& listRowCol){
	if(!isValidPos(row, col))
		return;
	RowCol nextRowPol(row, col);
	bool nextFlag = false;
	listRowCol.push_back(nextRowPol);

	//×óÉÏ½Ç
	do {
		if (nextRowPol.m_Row%2 == 0)
		{
			nextRowPol.m_Col --;
			nextRowPol.m_Row --;
		}else{
			nextRowPol.m_Row --;
		}

		if (isValidPos(nextRowPol))
		{
			listRowCol.push_back(nextRowPol);
			nextFlag = true;
		}else{
			nextFlag = false;
		}

	} while (nextFlag);

	//ÓÒÏÂ½Ç
	nextRowPol.m_Col = col;
	nextRowPol.m_Row = row;
	do 
	{
		if (nextRowPol.m_Row%2 == 0)
		{
			nextRowPol.m_Row ++;
		}else
		{
			nextRowPol.m_Row ++;
			nextRowPol.m_Col ++;
		}

		if(isValidPos(nextRowPol)){
			listRowCol.push_back(nextRowPol);
			nextFlag = true;
		}else{
			nextFlag = false;
		}
	} while (nextFlag);

	//×ó±ß
	nextRowPol.m_Row = row;
	nextRowPol.m_Col = col;
	do 
	{
		nextRowPol.m_Col --;
		if(isValidPos(nextRowPol)){
			listRowCol.push_back(nextRowPol);
			nextFlag = true;
		}else
		{
			nextFlag = false;
		}
	} while (nextFlag);

	//ÓÒ±ß
	nextRowPol.m_Col = col;
	do 
	{
		nextRowPol.m_Col ++;
		if(isValidPos(nextRowPol)){
			listRowCol.push_back(nextRowPol);
			nextFlag = true;
		}else
		{
			nextFlag = false;
		}
	} while (nextFlag);

	//ÓÒÉÏ½Ç
	nextRowPol.m_Col = col;
	nextRowPol.m_Row = row;
	do 
	{
		if (nextRowPol.m_Row %2 == 0)
		{
			nextRowPol.m_Row -- ;
		}else
		{
			nextRowPol.m_Row --;
			nextRowPol.m_Col ++;
		}
		if (isValidPos(nextRowPol))
		{
			listRowCol.push_back(nextRowPol);
			nextFlag = true;
		}else
		{
			nextFlag = false;
		}
	} while (nextFlag);

	//×óÏÂ½Ç
	nextRowPol.m_Col = col;
	nextRowPol.m_Row = row;
	do 
	{
		if (nextRowPol.m_Row %2 == 0)
		{
			nextRowPol.m_Row ++ ;
			nextRowPol.m_Col --;
		}else
		{
			nextRowPol.m_Row ++;
		}
		if (isValidPos(nextRowPol))
		{
			listRowCol.push_back(nextRowPol);
			nextFlag = true;
		}else
		{
			nextFlag = false;
		}
	} while (nextFlag);
}

#endif