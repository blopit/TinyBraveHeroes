//
//  Pawn.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-05.
//
//

#include <iostream>
#include <string>
#include "Pawn.hpp"
#include "GameManager.hpp"
#include "Passive.hpp"

USING_NS_CC;

bool Pawn::init() {
    hero = Sprite::create("res/whitepawn.png");
    addChild(hero);
    
    waitLabel = Label::createWithTTF("wait", "fonts/dpcomic.ttf", 24);
    waitLabel->setAnchorPoint(Vec2(0, 1));
    waitLabel->setTextColor(Color4B(Color4F(0.3, 1, 0, 1)));
    waitLabel->enableOutline(Color4B::BLACK, 3);
    addChild(waitLabel);
    
    healthbar = Healthbar::create(maxHP);
    addChild(healthbar);
    
    return true;
}

Pawn *Pawn::create(GridTile *tile, CharInfo info) {
    Pawn *pRet = new Pawn(tile, info);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

Pawn::Pawn(GridTile *tile, CharInfo info): tile(tile), info(info){
    maxHP = HP = info.HP;
    tile->occupied = true;
    waitTime = 0.0;
    selectedAbility = new Ability(this); //TODO: fix
    drawNode = DrawNode::create();
    
    givePassive(new Bleed(this, this, 50, 1), this);
}

void Pawn::activate(GridTile *location, GridGraph *graph, std::vector<Pawn *> pawns) {
    selectedAbility->activate(location, graph, pawns);
    waitTime += selectedAbility->waitTime;
}

void Pawn::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) {
    
    hero->setPosition(tile->getCoordinate());
    hero->draw(renderer, transform, transformFlags);
    
    int tileSize = GameManager::getInstance()->getTileSize();
    
    if (!selected) {
        waitLabel->setVisible(true);
        waitLabel->setString(std::to_string(remainingWait()));
        waitLabel->setPosition(hero->getPosition() + Vec2(-tileSize/2 + 6, tileSize/2));
        waitLabel->draw(renderer, transform, transformFlags);
    } else {
        waitLabel->setVisible(false);
    }
    
    healthbar->setPosition(hero->getPosition() + Vec2(-tileSize/2, -tileSize/2));
    healthbar->draw(renderer, transform, transformFlags);
}

double Pawn::waitSpeed() {
    return cMULT(info.SPD);
}

int Pawn::remainingWait() {
    double waitSpeed = Pawn::waitSpeed();
    if (waitSpeed == 0) {
        return 999.0;
    }
    auto x = (int) ceil(waitTime / waitSpeed);
    
    return boundToRange(0, x, 999);
}

bool Pawn::tick() {
    double waitSpeed = Pawn::waitSpeed();
    waitTime -= waitSpeed;
    
    triggerPassives(Trigger::PAWN_TICK);
    
    return waitTime <= 0;
}

void Pawn::setTile(GridTile* newTile, GridGraph* graph) {
    tile = newTile;
}

GridTile* Pawn::getTile() {
    return tile;
}

void Pawn::jumpToDest(GridTile* destTile) {
    tile->occupied = false;
    tile = destTile;
    selected = false;
    tile->occupied = true;
}

void Pawn::triggerPassives(Trigger t) {
    for (auto p : passives) {
        if (std::find(p->triggers.begin(), p->triggers.end(), t) == p->triggers.end()) continue;
        p->tick(t);
    }
}

void Pawn::damage(Pawn *src, double amount, AttackType at) {
    double removal = amount;
    
    for (auto p : passives) {
        if (std::find(p->triggers.begin(), p->triggers.end(), Trigger::BEFORE_DAMAGE_MIT) == p->triggers.end()) continue;
        p->trigger_before_damage_mit(amount, at);
    }
    
    switch (at) {
        case PHYSICAL:
            removal *= (1-cMIT(info.DEF));
            break;
        case MAGICAL:
            removal *= (1-cMIT(info.RES));
            break;
        case MIXED:
            removal *= (1-cMIT((info.RES+info.DEF)/2));
            break;
        default:
            break;
    }
    
    triggerPassives(Trigger::AFTER_DAMAGE_MIT);
}
