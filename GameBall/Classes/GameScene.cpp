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
	m_real = ccpNormalize(ccpSub(pos, m_curReady->getPosition()));

	setDisableEnable();
	this->scheduleUpdate();
}

void GameScene::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){
	
}

void GameScene::update(float delta){
	if(isCollisionWithBorder()){
		m_real.x =- m_real.x;
	}

	CCPoint pos = m_curReady->getPosition();
	m_curReady->setPosition(ccp(pos.x + m_real.x * BUBBLE_SPEED, pos.y + m_real.y * BUBBLE_SPEED));

	//if(isCollision()){
	//	m_real = CCPointZero;
	//}
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
	return false;
}
