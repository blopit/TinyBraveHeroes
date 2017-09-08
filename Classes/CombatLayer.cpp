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
#include "CombatLogic.hpp"

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
    
    graph = new GridGraph();
    current = NULL;
    destTile = NULL;
    drawNode = DrawNode::create();
    addChild(drawNode, 10);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(CombatLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(CombatLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(CombatLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    auto winWidth = Director::getInstance()->getWinSize().width;
    auto winHeight = Director::getInstance()->getWinSize().height;
    auto tileSize = GameManager::getInstance()->getTileSize();

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
    
    this->addChild(node, 0);
    
    
    //create pawn
    auto pawn = Pawn::create(graph->getTileAt(Vec(0, 0)), CharInfo(100, 48, 25));
    pawns.push_back(pawn);
    this->addChild(pawn, 20);
    
    pawn = Pawn::create(graph->getTileAt(Vec(4, 4)), CharInfo(100, 64, 20));
    pawns.push_back(pawn);
    this->addChild(pawn, 20);
    
    return true;
}

void CombatLayer::update(float dt) {
    drawNode->clear();
    
    GridTile *citem = NULL;
    for (auto item : path) {
        if (citem != NULL) {
            Vec2 v1 = citem->getCoordinate();
            Vec2 v2 = item->getCoordinate();
            drawNode->drawSegment(v1, v2, 4, Color4F::RED);
        }
        citem = item;
    }
    
    for (auto move : viableMoves) {
        Vec2 v = move->getCoordinate();
        drawNode->drawCircle(v, 40, 0, 8, false, 1.0f, 1.0f, Color4F::BLUE);
    }
}

Point CombatLayer::touchToPoint(Touch * touch) {
    return Director::getInstance()->convertToGL(touch->getLocationInView());
}

bool CombatLayer::isTouchingSprite(Touch* touch, Pawn *pawn) {
    //TODO: do this better
    Vec2 pos = pawn->getHero()->getPosition();
    return (pos.getDistance(touchToPoint(touch)) < 100.0f);
}

void CombatLayer::generatePaths(GridTile * dest) {
    path = pathToTile(distData, dest);
    viableMoves = reachableTiles(distData, current->info.MVE);
    
    // Cull occupied squares
    viableMoves.erase(std::remove_if(viableMoves.begin(), viableMoves.end(), [](const GridTile *x) {
        return x->occupied;
    }), viableMoves.end());
}

bool CombatLayer::onTouchBegan(Touch* touch, Event* event) {
    if (current) {
        if (touch && isTouchingSprite(touch, current)) {
            dragging = true;
            auto tile = current->getTile();
            distData = dijkstra(graph, tile);
            generatePaths(tile);
            return true;
        }
    }
    return false;
}

void CombatLayer::onTouchMoved(Touch* touch, Event* event) {
    if (current and dragging) {
        auto gotoTile = CombatLayer::getTileAt(touchToPoint(touch));
        if (destTile != gotoTile) {
            destTile = gotoTile;
            generatePaths(destTile);
        }
    }
}

void CombatLayer::onTouchEnded(Touch* touch, Event* event) {
    if (current and dragging) {
        current->jumpToDest(destTile);
        current = NULL;
        dragging = false;
        path.clear();
        viableMoves.clear();
    }
}



///////////////////////////////////////////

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
    
    x = boundToRange(offsetx - tileSize * 3, x, offsetx + tileSize * 2);
    y = boundToRange(offsety - tileSize * 4, y, offsety + tileSize * 3);
    
    return Vec2(x, y);
}

////////////////////////////////////////

