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
	backGround->setAnchorPoint(CCPointZero);
	backGround->setPosition(CCPointZero);
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

bool GameScene::initBoard(){

}