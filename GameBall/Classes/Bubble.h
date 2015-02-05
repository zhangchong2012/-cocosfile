#ifndef __BUBBLE_H__
#define __BUBBLE_H__
#include "cocos2d.h"
#include "Constant.h"
using namespace cocos2d;

class Bubble: public CCSprite
{
public:
	Bubble(void);
	virtual ~Bubble(void);

public:
	virtual bool init();
	CREATE_FUNC(Bubble);

public:
	void setBubbleColor(BUBBLE_COLOR color);
	BUBBLE_COLOR getBubbleColor();

	void setRowIndex(int row);
	int getRowIndex();

	void setColIndex(int col);
	int getColIndex();

	void setRowColIndex(int row, int col);

	BUBBLE_COLOR randomColor();

private:
	int m_RowIndex;
	int m_ColIndex;
	BUBBLE_COLOR m_color;
};
#endif 
