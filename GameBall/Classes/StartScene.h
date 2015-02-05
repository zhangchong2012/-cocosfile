#ifndef __START_SCENE__
#define __START_SCENE__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "SimpleAudioEngine.h"

using namespace CocosDenshion;
using namespace cocos2d;

class StartScene : public cocos2d::CCLayer
{
public:
	StartScene(void);
	~StartScene(void);

	bool virtual init();

	static cocos2d::CCScene* scene();

	void menuCloseCallback(CCObject* pSender);
	void menuNewGameCallback(CCObject* pSender);

	CREATE_FUNC(StartScene);

};
#endif __START_SCENE__

