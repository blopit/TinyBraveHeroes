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
    waitLabel = Label::createWithSystemFont("wait", "arial", 24);
    waitLabel->setAnchorPoint(Vec2(0, 1));
    waitLabel->setTextColor(Color4B::WHITE);
    addChild(waitLabel);
    
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
    waitTime = 100.0;
    drawNode = DrawNode::create();
}

void Pawn::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) {
    
    hero->setPosition(tile->getCoordinate());
    hero->draw(renderer, transform, transformFlags);
    
    int tileSize = GameManager::getInstance()->getTileSize();
    
    waitLabel->setString(std::to_string(remainingWait()));
    waitLabel->setPosition(hero->getPosition() + Vec2(-tileSize/2, tileSize/2));
    waitLabel->draw(renderer, transform, transformFlags);
    
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

void Pawn::setTile(GridTile* newTile, GridGraph* graph) {
    tile = newTile;
}

GridTile* Pawn::getTile() {
    return tile;
}

void Pawn::jumpToDest(GridTile* destTile) {
    tile->occupied = false;
    tile = destTile;
    tile->occupied = true;
}
