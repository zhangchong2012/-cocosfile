#include "StartScene.h"
#include "GameScene.h"

StartScene::StartScene(void)
{
	SimpleAudioEngine::sharedEngine()->playBackgroundMusic("main_music.mp3", true);
}


StartScene::~StartScene(void)
{
}

CCScene* StartScene::scene(){
	CCScene* scene = CCScene::create();

	StartScene* layout = StartScene::create();
	
	if(scene && layout){
		scene->addChild(layout);
	}

	return scene;
}

bool StartScene::init(){
	if(!CCLayer::init()){
		return false;
	}
	
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCLabelTTF* label = CCLabelTTF::create("New Game", "Arial", 24 * 2);
	CCMenuItemLabel* pNewGameItem = CCMenuItemLabel::create(label, this, menu_selector(StartScene::menuNewGameCallback));
	pNewGameItem->setTag(1);
	pNewGameItem->setPosition(winSize.width/2, winSize.height/2);

	CCMenu* pMenu = CCMenu::create(pNewGameItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCSprite* pSprite = CCSprite::create("StartScene_CN.jpg");
	pSprite->setPosition(ccp(winSize.width/2, winSize.height/2));
	this->addChild(pSprite, 0);

	return true;
}

void StartScene::menuCloseCallback(CCObject* pSender){
	CCDirector::sharedDirector()->end();
}

void StartScene::menuNewGameCallback(CCObject* pSender){
	CCDirector::sharedDirector()->replaceScene(GameScene::scene());
}