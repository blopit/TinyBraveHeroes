//
//  GameManager.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-06.
//
//

#ifndef GameManager_hpp
#define GameManager_hpp

#include "cocos2d.h"
#include "AnimationBlock.hpp"

class GameManager
{
private:
    GameManager();
    ~GameManager();
    vector<AnimationBlock *> animations;
    bool running = false;
    
public:
    static GameManager* getInstance();
    void addAnimation(AnimationBlock *ab);
    bool isAnimationRunning();
    
    CC_SYNTHESIZE(int, tileSize, TileSize);
    CC_SYNTHESIZE(cocos2d::Node *, effectLayer, EffectLayer);
    CC_SYNTHESIZE(cocos2d::Node *, particleLayer, ParticleLayer);
    CC_SYNTHESIZE(cocos2d::Node *, backLayer, BackLayer);
    
    const cocos2d::Vector<cocos2d::SpriteFrame *> getAnimation(const char *format, int count);
};

#endif /* GameManager_hpp */
