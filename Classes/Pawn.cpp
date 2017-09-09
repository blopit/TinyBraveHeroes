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

USING_NS_CC;

bool Pawn::init() {
    hero = Sprite::create("res/whitepawn.png");
    addChild(hero);
    
    waitLabel = Label::createWithTTF("wait", "fonts/dpcomic.ttf", 24);
    waitLabel->setAnchorPoint(Vec2(0, 1));
    waitLabel->setTextColor(Color4B(Color4F(0.3, 1, 0, 1)));
    waitLabel->enableOutline(Color4B::BLACK, 3);
    addChild(waitLabel);
    
    maxHP = HP = info.HP;
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
    tile->occupied = true;
    waitTime = 0.0;
    selectedAbility = new Ability(this); //TODO: fix
    drawNode = DrawNode::create();
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
    return waitTime <= 0;
}

void Pawn::setHP(double HP_){
    HP = HP_;
    healthbar->HP = HP;
}

double Pawn::getHP(){
    return HP;
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
