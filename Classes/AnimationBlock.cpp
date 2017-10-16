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
    float impact = 30;
    float s = 0.5f;
    
    auto frames = gm->getAnimation("cut_c/cut_c_%04d.png", n);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    gm->getEffectLayer()->addChild(sprite);
    sprite->setPosition(dest->getTile()->getCoordinate());
    
    auto delay = DelayTime::create(dur/n * 1);
    auto scale = ScaleBy::create(0.0f, s * xscale, s);
    auto animation = Animation::createWithSpriteFrames(frames, dur/n);
    auto catchUp = CallFunc::create([=](){
        auto p = new PtPow(dest->getTile()->getCoordinate());
        p->process();
        dest->catchupDisplayHP();
        dest->highlightLeveL = 1.2;
    });
    auto move = MoveBy::create(0.15f, Vec2(impact*cos(angle),impact*sin(angle)));
    auto move_back_ease = EaseBackOut::create(move->clone());
    auto move_back = MoveTo::create(0.3f, dest->getTile()->getCoordinate());
    auto move_back2 = EaseInOut::create(move_back->clone(), 0.7f);
    
    auto seq0 = Sequence::create(scale, cocos2d::Animate::create(animation), RemoveSelf::create(), nullptr);
    auto seq1 = Sequence::create(delay, catchUp, nullptr);
    auto seq2 = Sequence::create(delay->clone(), move_back_ease, move_back2, cf, nullptr);
    
    sprite->runAction(seq0);
    sprite->runAction(seq1);
    dest->getHero()->runAction(seq2);
}

void AnimClawSlashDouble::process(CallFunc *cf) {
    auto gm = GameManager::getInstance();
    float dur = 0.3;
    int n = 5;
    float impact = 30;
    float s = 0.5f;
    
    auto frames = gm->getAnimation("fx/cut_c/cut_c_%04d.png", n);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    gm->getEffectLayer()->addChild(sprite);
    sprite->setPosition(dest->getTile()->getCoordinate());
    
    auto delay = DelayTime::create(dur/n * 1);
    auto scale = ScaleBy::create(0.0f, s * xscale, s);
    auto animation = Animation::createWithSpriteFrames(frames, dur/n);
    auto catchUp = CallFunc::create([=](){
        auto p = new PtPow(dest->getTile()->getCoordinate());
        p->process();
        dest->catchupDisplayHP();
        dest->highlightLeveL = 1.2;
    });
    auto move = MoveBy::create(0.15f, Vec2(impact*cos(angle),impact*sin(angle)));
    auto move_back_ease = EaseBackOut::create(move->clone());
    auto move_back = MoveTo::create(0.3f, dest->getTile()->getCoordinate());
    auto move_back2 = EaseInOut::create(move_back->clone(), 0.7f);
    
    auto seq0 = Sequence::create(scale, cocos2d::Animate::create(animation), RemoveSelf::create(), nullptr);
    auto seq1 = Sequence::create(delay, catchUp, nullptr);
    auto seq2 = Sequence::create(delay->clone(), move_back_ease, move_back2, cf, nullptr);
    
    sprite->runAction(seq0);
    sprite->runAction(seq1);
    dest->getHero()->runAction(seq2);
}

void PtPow::process() {
    int n = 6;
    float dur = 0.3f;
    float s = 0.3f;
    
    auto gm = GameManager::getInstance();
    auto frames = gm->getAnimation("blood_c/blood_c_%04d.png", n);
    auto sprite = Sprite::createWithSpriteFrame(frames.front());
    gm->getParticleLayer()->addChild(sprite);
    sprite->setPosition(loc);
    auto animation = Animation::createWithSpriteFrames(frames, dur/n);
    auto scale = ScaleBy::create(0.0f, s);
    auto fade = FadeTo::create(0.3, 128.0f);
    
    auto seq0 = Sequence::create(scale, cocos2d::Animate::create(animation), RemoveSelf::create(), nullptr);
    auto seq1 = Sequence::create(fade, nullptr);
    sprite->runAction(seq0);
    sprite->runAction(seq1);
}
