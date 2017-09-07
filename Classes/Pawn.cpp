//
//  Pawn.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-05.
//
//

#include <iostream>
#include "Pawn.hpp"

USING_NS_CC;

bool Pawn::init() {
    hero = Sprite::create("res/whitepawn.png");
    addChild(hero);
    
    return true;
}

Pawn *Pawn::create(GridTile *tile) {
    Pawn *pRet = new Pawn(tile);
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

void Pawn::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) {
    
    hero->setPosition(tile->getCoordinate());
    
    hero->draw(renderer, transform, transformFlags);
}

void Pawn::setTile(GridTile* newTile, GridGraph* graph) {
    tile = newTile;
}

GridTile* Pawn::getTile() {
    return tile;
}

void Pawn::jumpToDest(GridTile* destTile) {
    tile = destTile;
}
