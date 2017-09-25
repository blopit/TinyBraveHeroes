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

class additiveTint : public FiniteTimeAction {
    
};

class AnimationBlock {
protected:
    Pawn *src;
    Pawn *dest;
    double angle;
    float xscale;
    AnimationBlock(Pawn *src, Pawn *dest) : src(src), dest(dest) {
        Vec2 p2 = src->getTile()->getCoordinate();
        Vec2 p1 = dest->getTile()->getCoordinate();
        angle = atan2(p1.y - p2.y, p1.x - p2.x);
        xscale = p2.x < p1.x ? 1.0f : -1.0f;
    };
    
public:
    virtual void process(CallFunc *cf) = 0;
};

class AnimClawSlash : public AnimationBlock {
public:
    AnimClawSlash(Pawn *src, Pawn *dest) : AnimationBlock(src, dest) {}
    void process(CallFunc *cf) override;
};

class AnimClawSlashDouble : public AnimationBlock {
public:
    AnimClawSlashDouble(Pawn *src, Pawn *dest) : AnimationBlock(src, dest) {}
    void process(CallFunc *cf) override;
};

class Particle {
protected:
    Vec2 loc;
public:
    Particle(Vec2 loc) : loc(loc) {}
    virtual void process() = 0;
};

class PtPow : public Particle {
public:
    PtPow(Vec2 loc) : Particle(loc) {}
    void process() override;
};

#endif /* AnimationBlock_hpp */
