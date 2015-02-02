#include "GameScene.h"


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
	clear();
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
	return true;
}

//初如化泡泡发射器
bool GameScene::initReadyBubble(){
	for (int row = 0; row < MAX_ROWS; row++){
		for (int col = 0; col < MAX_COLS - row%2; col++){
			if (row >= INIT_LINE){
				m_board[row][col] = NULL;
			}

			Bubble* pBubble = randomBubble();
			if (pBubble == NULL)
			{
				return;
			}
			pBubble->setPosition();
		}
	}
	return true;
}

bool GameScene::initWaitBubble(){
	return true;
}


