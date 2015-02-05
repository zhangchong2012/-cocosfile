#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "Bubble.h"
#include "Constant.h"
#include <list>
#include <vector>

using namespace cocos2d;
using namespace CocosDenshion;

typedef std::list<Bubble*> BUBBLE_LIST;
typedef std::list<RowCol>  ROWCOL_LIST;

class GameScene: public CCLayer
{
public:
	GameScene(void);
	virtual ~GameScene(void);

public:
	static CCScene* scene();

	virtual bool init();

	void loop();
	void update(float delta);
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	CREATE_FUNC(GameScene);

private:
	Bubble* randomBubble();
	Bubble* createBubble(BUBBLE_COLOR color);

	void clear();

	bool initScheduler();
	bool initReadyBubble();
	bool initBoard();
	bool initWaitBubble();


	bool isCollisionWithBorder();//是否和左右边缘碰撞
	bool isCollisionWithTopBorder(Bubble *pBubble);	//是否和顶层边缘碰撞，
	bool isCollision();	//是否碰撞，仅包括是否和上方所有的球碰撞和顶层边缘碰撞， 不包括和左右边缘碰撞
	bool isCollisionWithBubble(CCPoint pos, float radius, CCPoint pos2, float radius2);

	void changeWaitToReady();

	void adjustBubblePosition();
	void setEnable();
	void setDisableEnable();



private:
	Bubble* m_board[MAX_ROWS][MAX_COLS];

	Bubble* m_wait[MAX_WAIT_BUBBLE];

	Bubble* m_curReady;
	BUBBLE_LIST m_listBubble;

	double m_radian;//范围为30度为150;默认为90度， 竖直方向

	int m_nWidth;			//游戏界面的宽度和高度
	int m_nHeight;

	int m_nScore;			//游戏所得到的分数

	int m_nGoldenBubbleCount;
	int m_nSliveryBubbleCount;

	GameState m_state;
	CCPoint m_real;
};

#endif

