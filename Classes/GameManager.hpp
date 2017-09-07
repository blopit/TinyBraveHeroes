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
void boundToRange(T lower, T &value, T upper) {
    value = value < lower ? lower : value > upper ? upper : value;
}

#endif /* GameManager_hpp */
