//
//  CombatLayer.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-05.
//
//

#include "CombatLayer.hpp"
#include <iostream>
#include "Pawn.hpp"
#include "GameManager.hpp"

Scene* CombatLayer::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = CombatLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool CombatLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CombatLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CombatLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CombatLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto winWidth = Director::getInstance()->getWinSize().width;
    auto winHeight = Director::getInstance()->getWinSize().height;
    int tileSize = GameManager::getInstance()->getTileSize();

    auto node = DrawNode::create();
    
    int upper = winHeight / 2 + tileSize * 4;
    int lower = winHeight / 2 - tileSize * 4;
    
    //vertical lines
    for (int i = 0; i < 9; i++) {
        node->drawLine(Vec2(0, lower + i * tileSize), Vec2(winWidth, lower + i * tileSize), Color4F(1.0, 1.0, 1.0, 0.5));
    }
    
    //horizontal lines
    for (int i = -3; i < 4; i++) {
        node->drawLine(Vec2(i * tileSize + winWidth / 2, upper), Vec2(i * tileSize + winWidth / 2, lower), Color4F(1.0, 1.0, 1.0, 0.5));
    }
    
    node->drawCircle(Vec2(winWidth/2, winHeight/2), winWidth/2, 0.0f, 8, true, 1.0f, 1.0f, Color4F::RED);
    this->addChild(node, 0);
    
    graph = new GridGraph();
    selected = NULL;
    
    //create pawn
    auto pawn = Pawn::create(graph->getTileAt(Vec(0, 0)));
    pawns.push_back(pawn);
    this->addChild(pawn, 2);
    
    return true;
}

Point CombatLayer::touchToPoint(Touch * touch) {
    return Director::getInstance()->convertToGL(touch->getLocationInView());
}

bool CombatLayer::isTouchingSprite(Touch* touch, Pawn *pawn) {
    //TODO: do this better
    Vec2 pos = pawn->getHero()->getPosition();
    return (pos.getDistance(touchToPoint(touch)) < 100.0f);
}

GridTile *CombatLayer::getTileAt(Vec2 p) {
    int tileSize = GameManager::getInstance()->getTileSize();
    
    auto winWidth = Director::getInstance()->getWinSize().width;
    auto winHeight = Director::getInstance()->getWinSize().height;
    auto offsetx = (tileSize + winWidth) / 2;
    auto offsety = (tileSize + winHeight) / 2;
    
    int x = round((p.x - offsetx) / ((float) tileSize)) + 3;
    int y = round((p.y - offsety) / ((float) tileSize)) + 4;
    
    return graph->getTileAt(Vec(x, y));
}

Vec2 CombatLayer::getClosestTile(Vec2 p) {
    auto tileSize = GameManager::getInstance()->getTileSize();

    auto winWidth = Director::getInstance()->getWinSize().width;
    auto winHeight = Director::getInstance()->getWinSize().height;
    auto offsetx = (tileSize + winWidth) / 2;
    auto offsety = (tileSize + winHeight) / 2;
    
    auto x = round((p.x - offsetx) / ((float) tileSize)) * tileSize + offsetx;
    auto y = round((p.y - offsety) / ((float) tileSize)) * tileSize + offsety;
    
    boundToRange(offsetx - tileSize * 3, x, offsetx + tileSize * 2);
    boundToRange(offsety - tileSize * 4, y, offsety + tileSize * 3);
    
    return Vec2(x, y);
}

bool CombatLayer::onTouchBegan(Touch* touch, Event* event) {
    for (auto pawn : pawns) {
        if (touch && isTouchingSprite(touch, pawn)) {
            selected = pawn;
            return true;
        }
    }
    return false;
}

void CombatLayer::onTouchMoved(Touch* touch, Event* event) {
    if (selected) {
        selected->setDestTile(CombatLayer::getTileAt(touchToPoint(touch)), graph);
    }
}

void CombatLayer::onTouchEnded(Touch* touch, Event* event) {
    if (selected) {
        selected->jumpToDest();
        selected = NULL;
    }
}
