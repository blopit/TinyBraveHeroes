//
//  GameManager.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-06.
//
//

#include "GameManager.hpp"

USING_NS_CC;

static GameManager* gameManager = nullptr;

GameManager::GameManager() {
    tileSize = Director::getInstance()->getWinSize().width / 6;
}

GameManager* GameManager::getInstance() {
    if (!gameManager) {
        gameManager = new (std::nothrow)GameManager();
    }
    
    return gameManager;
}


const Vector<SpriteFrame *> GameManager::getAnimation(const char *format, int count) {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame *> animFrames;
    char str[255];
    for(int i = 1; i <= count; i++) {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}



void GameManager::addAnimation(AnimationBlock *ab) {
    animations.push_back(ab);
}

bool GameManager::isAnimationRunning() {
    if (animations.empty()) {
        return false;
    } else {
        if (!running) {
            running = true;
            
            auto callback = CallFunc::create([=](){
                running = false;
                animations.erase(animations.begin());
            });
            
            animations[0]->process(callback);
        }
        return true;
    }
}
