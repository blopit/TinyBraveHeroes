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
