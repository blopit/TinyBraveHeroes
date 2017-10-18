#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Character.hpp"

enum class MenuState {
    HOME,
    TAVERN,
    CARAVAN,
    BLACKSMITH,
    SUMMON,
    BARRACKS,
};

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    void step(float dt);
    
    Character *guy = NULL;
    int total = 0;
    
private:
    cocos2d::Sprite *sprite;
};

#endif // __HELLOWORLD_SCENE_H__
