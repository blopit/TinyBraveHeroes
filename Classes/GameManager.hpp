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

#define CB_BLACK Color4F(0.0, 0.0, 0.0, 1.0)

#define CB_SKBLUE Color4F(0.35, 0.7, 0.9, 1.0)
#define CB_BLUE Color4F(0, 0.45, 0.7, 1.0)

#define CB_GREEN Color4F(0.0, 0.6, 0.5, 1.0)
#define CB_LTGREEN Color4F(0.4, 1.0, 0.6, 1.0)

#define CB_YELLOW Color4F(0.95, 0.9, 0.25, 1.0)

#define CB_ORANGE Color4F(0.9, 0.6, 0.0, 1.0)
#define CB_RED Color4F(0.8, 0.4, 0.0, 1.0)
#define CB_DKRED Color4F(0.85, 0.0, 0.0, 1.0)

#define CB_PINK Color4F(0.8, 0.4, 0.0, 1.0)

enum Faction {
    ALLY,
    ENEMY,
    THIRD_PARTY_ENEMY,
    THIRD_PARTY_ALLY
};


class GameManager
{
private:
    GameManager();
    ~GameManager();
    
public:
    static GameManager* getInstance();
    
    CC_SYNTHESIZE(int, tileSize, TileSize);
};

template <class T>
T boundToRange(T lower, T value, T upper) {
    return value < lower ? lower : value > upper ? upper : value;
}

cocos2d::Color4F factionColour(const Faction f);

#endif /* GameManager_hpp */
