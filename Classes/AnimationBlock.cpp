//
//  AnimationBlock.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-13.
//
//

#include "AnimationBlock.hpp"
#include "GameManager.hpp"
#include <iostream>


void AnimClawSlash::process(CallFunc *cf) {
    auto gm = GameManager::getInstance();
    float dur = 0.3;
    int n = 5;
    float impact = 20;
    
    auto frames = gm->getAnimation("fx/cut_c/cut_c_%04d.png", n);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    gm->getEffectLayer()->addChild(sprite);
    sprite->setPosition(dest->getTile()->getCoordinate());
    
    auto delay = DelayTime::create(dur/n * 1);
    auto scale = ScaleBy::create(0.0f, 0.5);
    auto animation = Animation::createWithSpriteFrames(frames, dur/n);
    auto catchUp = CallFunc::create([=](){
        dest->catchupDisplayHP();
    });
    auto move = MoveBy::create(0.15f, Vec2(impact*cos(angle),impact*sin(angle)));
    auto move_back_ease = EaseBackOut::create(move->clone());
    auto move_back = MoveTo::create(0.3f, dest->getTile()->getCoordinate());
    
    auto seq0 = Sequence::create(scale, cocos2d::Animate::create(animation), RemoveSelf::create(), nullptr);
    auto seq1 = Sequence::create(delay, catchUp, nullptr);
    auto seq2 = Sequence::create(delay->clone(), move_back_ease, move_back, cf, nullptr);
    sprite->runAction(seq0);
    sprite->runAction(seq1);
    dest->getHero()->runAction(seq2);
}
