#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
   
       
    rippleSprite = pgeRippleSprite::create("image.png");
//    rippleSprite->setPosition(ccp(160,240));
//    rippleSprite->setScale(0.5);
    rippleSprite->setScale(480.0 / 320);
    this->addChild(rippleSprite);
    
//    rippleSprite->setRotation(20);

    
    this->scheduleUpdate();
    
    
   
    
    return true;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::update(float dt)
{
    rippleSprite->update(dt);
    
}



