//
//  Pawn.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-05.
//
//

#ifndef Pawn_hpp
#define Pawn_hpp

#include <stdio.h>

class Pawn : public cocos2d::Layer {
    static cocos2d::Layer* createLayer();
    virtual bool init();
    
    cocos2d::EventListenerTouchOneByOne listener;
};


#endif /* Pawn_hpp */
