//
//  AnimationBlock.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-13.
//
//

#ifndef AnimationBlock_hpp
#define AnimationBlock_hpp

#include "cocos2d.h"
#include "Pawn.hpp"

USING_NS_CC;

enum Command {
    MOVE, SHAKE
};

class AnimationBlock {
protected:
    Pawn *src;
    Pawn *dest;
    double angle;
    AnimationBlock(Pawn *src, Pawn *dest) : src(src), dest(dest) {
        Vec2 p2 = src->getTile()->getCoordinate();
        Vec2 p1 = dest->getTile()->getCoordinate();
        angle = atan2(p1.y - p2.y, p1.x - p2.x);
    };
    
public:
    virtual void process(CallFunc *cf) = 0;
};

class AnimClawSlash : public AnimationBlock {
public:
    AnimClawSlash(Pawn *src, Pawn *dest) : AnimationBlock(src, dest) {}
    void process(CallFunc *cf) override;
};

#endif /* AnimationBlock_hpp */
