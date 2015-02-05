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


	bool isCollisionWithBorder();//�Ƿ�����ұ�Ե��ײ
	bool isCollisionWithTopBorder(Bubble *pBubble);	//�Ƿ�Ͷ����Ե��ײ��
	bool isCollision();	//�Ƿ���ײ���������Ƿ���Ϸ����е�����ײ�Ͷ����Ե��ײ�� �����������ұ�Ե��ײ
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

	double m_radian;//��ΧΪ30��Ϊ150;Ĭ��Ϊ90�ȣ� ��ֱ����

	int m_nWidth;			//��Ϸ����Ŀ�Ⱥ͸߶�
	int m_nHeight;

	int m_nScore;			//��Ϸ���õ��ķ���

	int m_nGoldenBubbleCount;
	int m_nSliveryBubbleCount;

	GameState m_state;
	CCPoint m_real;
};

#endif

