#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

using namespace std;

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/misc.plist");
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/icons.plist");
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    this->schedule(schedule_selector(HelloWorld::step));
    
    /*auto ss = Director::getInstance()->getVisibleSize();
    ScreenInhertedFromColorLayer *scl = new ScreenInhertedFromColorLayer();
    if (scl && scl->initWithColor(Color4B(0,0,0,128), ss.width, ss.height))
        //other initialisation for create() method. Create your best popup layout here
    */
    guy = new Character(
                             Attributes(3, 7, 6, 3, 4, 6),
                             Attributes(28, 47, 40, 24, 31, 40),
                             Attributes(0, 0, 0, 0, 0, 0),
                        1, CharRarity::SILVER
    );
    
    p = getItemPassive(PassiveItemIndex::ELEPHANT, ItemRarity::COMMON, 30);
    cout << p->name << endl;
    cout << p->getDescription() << endl;
    
    auto spr = p->generateSprite();
    spr->setPosition(Vec2(512, 512));
    addChild(spr);
    
    return true;
}


void HelloWorld::step(float dt) {
    
    p->generateSpin(total);
    
    total += 5;
    
    /*if (guy) {
        auto amount = guy->level * (2+cocos2d::random(1, 5));
        guy->giveExp(amount);
        total += 1;
        cout << "tot " << total << endl;
    }*/
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
