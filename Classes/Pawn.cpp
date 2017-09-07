//
//  Pawn.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-05.
//
//

#include "Pawn.hpp"

USING_NS_CC;

bool Pawn::init() {
    hero = Sprite::create("res/whitepawn.png");
    marker = Sprite::create("res/marker0.png");
    
    addChild(hero);
    addChild(marker);
    
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

void Pawn::onDrawPrimitives(const cocos2d::Mat4 &transform, uint32_t flags)
{
    cocos2d::Director* director = cocos2d::Director::getInstance();
    director->pushMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
    director->loadMatrix(cocos2d::MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);
    
    for (auto it : path) {
        Vec2 v1 = it.first->getCoordinate();
        Vec2 v2 = it.second->getCoordinate();
        cocos2d::DrawPrimitives::drawLine(v1, v2);
    }
}

void Pawn::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) {
    
    hero->setPosition(tile->getCoordinate());
    
    if (destTile) {
        marker->setPosition(destTile->getCoordinate());
        marker->draw(renderer, transform, transformFlags);
    }
    
    hero->draw(renderer, transform, transformFlags);
    
    _drawLines.init(_globalZOrder);
    _drawLines.func = CC_CALLBACK_0(Pawn::onDrawPrimitives, this, transform, _transformUpdated);
    renderer->addCommand(&_drawLines);
}

void Pawn::setDestTile(GridTile* newTile, GridGraph* graph) {
    destTile = newTile;
    path = breadthFirstSearch(*graph, tile, destTile);
}

GridTile* Pawn::getDestTile() {
    return destTile;
}

void Pawn::setTile(GridTile* newTile, GridGraph* graph) {
    tile = newTile;
}

GridTile* Pawn::getTile() {
    return tile;
}

void Pawn::jumpToDest() {
    tile = destTile;
    destTile = NULL;
    path.clear();
}
