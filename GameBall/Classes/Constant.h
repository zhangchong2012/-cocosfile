#ifndef __CONSTANE_H__
#define __CONSTANE_H__
#include <string>

#define PI					(3.14)
#define MENU_SPACE			(40)
#define BUBBLE_RADIUS		(32)

#define MAX_ROWS			(11)
#define MAX_COLS			(11)
#define INIT_LINE			(4)

#define MAX_WAIT_BUBBLE		(4)
#define BUBBLE_SPEED		(30)

#define READY_BUBBLE_POS	ccp(360, 128)

#define REMOVE_COUNT		(3)
#define SILVERY_COUNT		(4)
#define GOLDEN_COUNT		(5)

//6种普通颜色（黄、紫、蓝、红、绿、黑）， 两种特殊颜色（金、银）
enum BUBBLE_COLOR
{
	BUBBLE_YELLOW,
	BUBBLE_PURPLE,	//紫色
	BUBBLE_BULE,
	BUBBLE_RED,
	BUBBLE_GREEN,
	BUBBLE_BLACK,

	BUBBLE_SILVERY,	//银色
	BUBBLE_GOLDEN,	//金色

	COLOR_COUNT	//泡泡颜色数量
};

enum GameDirection 
{
	LEFT, 
	RIGHT,
	TOP_LEFT, 
	TOP_RIGHT,
	BOTTOM_LEFT, 
	BOTTOM_RIGHT, 
	DIRECTION_COUNT
};

enum GameState
{
	GS_START,
	GS_FLY,
	GS_FIXED,
	GS_FALL
};

static const std::string g_bubbleName[COLOR_COUNT] = 
{
	"bubble_0.png",
	"bubble_1.png",
	"bubble_2.png",
	"bubble_3.png",
	"bubble_4.png",
	"bubble_5.png",
	"bubble_6.png",
	"bubble_7.png"
};

struct RowCol
{
	bool operator==(const RowCol& rPos) const{
		return m_Row == rPos.m_Row && m_Col == rPos.m_Col;
	}

	RowCol(int nRow, int nCol){
		m_Col = nCol;
		m_Row = nRow;
	}
	int m_Row;
	int m_Col;
};

#endif // !__CONSTANE_H__
