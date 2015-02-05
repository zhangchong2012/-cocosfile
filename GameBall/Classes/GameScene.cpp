#include "GameScene.h"
#include "Utility.h"

GameScene::GameScene(void):
	m_state(GS_START), 
	m_nGoldenBubbleCount(0),
	m_nSliveryBubbleCount(0),
	m_nScore(0)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("game_scene_bg.mp3",true);
	SimpleAudioEngine::sharedEngine()->playEffect("ready_go.mp3");
	srand(time(NULL));
}


GameScene::~GameScene(void)
{
	//clear();
}

CCScene* GameScene::scene(){
	CCScene* scene = CCScene::create();
	GameScene* layer = GameScene::create();
	if(scene && layer)
		scene->addChild(layer);

	return scene;
}

bool GameScene::init(){
	if(!CCLayer::init())
		return false;

	CCSprite* backGround = CCSprite::create("background1.jpg");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	backGround->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(backGround);

	initScheduler();
	initBoard();
	initReadyBubble();
	initWaitBubble();
	setEnable();

	return true;
}

void GameScene::setEnable(){
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

void GameScene::setDisableEnable(){
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

bool GameScene::initScheduler(){
	return true;
}

//初始化泡泡队列，
bool GameScene::initBoard(){
	for (int row = 0; row < MAX_ROWS; row ++){
		for (int col = 0; col < MAX_COLS; col++){
			if(row > INIT_LINE){
				m_board[row][col] = NULL;
				continue;
			}
			Bubble* pBubble = randomBubble();
			if(!pBubble)
				return false;
			pBubble->setPosition(getPosByRowAndCol(row, col));
			this->addChild(pBubble);

			m_board[row][col] = pBubble;
			m_board[row][col]->setRowColIndex(row, col);
			m_listBubble.push_back(pBubble);
		}
	}
	return true;
}

//初如化泡泡发射器
bool GameScene::initReadyBubble(){
	m_curReady = randomBubble();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	m_curReady->setPosition(ccp(winSize.width/2, winSize.height/10));
	this->addChild(m_curReady);
	return true;
}

bool GameScene::initWaitBubble(){
	for (int i = 0; i < MAX_WAIT_BUBBLE; i++)
	{
		Bubble* bubble = randomBubble();

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		bubble->setPosition(ccp(winSize.width/2 + (i+1) * BUBBLE_RADIUS * 2,  winSize.height/20));
		m_wait[i] = bubble;
		this->addChild(bubble);
	}
	return true;
}

Bubble* GameScene::randomBubble(){
	BUBBLE_COLOR color = static_cast<BUBBLE_COLOR>(rand() % COLOR_COUNT);
	Bubble* bubble = Bubble::create();
	if(bubble && bubble->initWithFile(g_bubbleName[color].c_str())){
		bubble->setBubbleColor(color);
	}
	return bubble;
}


void GameScene::clear(){
	for (int row = 0; row < MAX_ROWS; row++)
	{
		for (int col = 0; col < MAX_COLS; col++)
		{
			CC_SAFE_DELETE(m_board[row][col]);
		}
	}
	m_listBubble.clear();
}

bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent){
	return true;
}

void GameScene::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent){

}

void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
	m_state = GS_FLY;
	CCPoint pos = pTouch->getLocation();
	//标准化向量
	m_real = ccpNormalize(ccpSub(pos, m_curReady->getPosition()));

	setDisableEnable();
	this->scheduleUpdate();
}

void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
	
}

void GameScene::update(float delta){
	if(isCollisionWithBorder())
	{
		m_real.x =- m_real.x;
	}

	CCPoint pos = m_curReady->getPosition();
	m_curReady->setPosition(ccp(pos.x + m_real.x * BUBBLE_SPEED, pos.y + m_real.y * BUBBLE_SPEED));

	if(isCollision()){
		m_real = CCPointZero;

		adjustBubblePosition();

		this->unscheduleUpdate();
		setEnable();

		changeWaitToReady();
	}
}

bool GameScene::isCollisionWithBorder(){
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint pos = m_curReady->getPosition();
	if (pos.x < BUBBLE_RADIUS || pos.x > size.width - BUBBLE_RADIUS)
	{
		return true;
	}

	return false;
}

bool GameScene::isCollision(){
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	if(m_curReady->getPosition().y > winSize.height - BUBBLE_RADIUS){
		return true;
	}
	for (BUBBLE_LIST::reverse_iterator iterBubble = m_listBubble.rbegin(); iterBubble != m_listBubble.rend(); ++iterBubble)
	{
		Bubble* bubble = *iterBubble;
		if (bubble && isCollisionWithBubble(bubble->getPosition(), BUBBLE_RADIUS, m_curReady->getPosition(), BUBBLE_RADIUS))
		{
			return true;
		}
	}

	return false;
}


bool GameScene::isCollisionWithBubble(CCPoint pos, float radius, CCPoint pos2, float radius2){
	return pow(pos.x - pos2.x, 2) + pow(pos.y - pos2.y, 2) < pow(radius + radius2, 2);	//判断两圆是否相交, 公式：（x1-x2)^2 + (y1-y2)^2 < (r1 + r2)^2
	//return pow(pos.x - pos2.x, 2) + pow(pos.y - pos.y, 2) < pow(radius + radius2, 2);
}

void GameScene::adjustBubblePosition(){
	CCPoint curPos = m_curReady->getPosition();
	RowCol rowcol_Index = getRowColByPos(curPos.x, curPos.y);
	CCPoint adjustPos = getPosByRowAndCol(rowcol_Index.m_Row, rowcol_Index.m_Col);

	m_curReady->setPosition(adjustPos);
	m_curReady->setRowColIndex(rowcol_Index.m_Row, rowcol_Index.m_Col);

	m_board[rowcol_Index.m_Row][rowcol_Index.m_Col] = m_curReady;
	m_listBubble.push_back(m_curReady);
}


void GameScene::changeWaitToReady(){
	m_curReady = m_wait[0];
	m_curReady->setPosition(READY_BUBBLE_POS);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	for (int index = 0; index < MAX_WAIT_BUBBLE - 1; index++)
	{
		m_wait[index] = m_wait[index + 1];
		m_wait[index]->setPosition(ccp(winSize.width/2 + (index+1) * BUBBLE_RADIUS * 2, winSize.height/20));
	}

	m_wait[MAX_WAIT_BUBBLE - 1] = randomBubble();
	m_wait[MAX_WAIT_BUBBLE - 1]->setPosition(ccp(winSize.width/2+MAX_WAIT_BUBBLE * BUBBLE_RADIUS *2, winSize.height/20));

	this->addChild(m_wait[MAX_WAIT_BUBBLE - 1]);
}