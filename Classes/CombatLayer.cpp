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
    
    char format[255] = "res/spritesheet-%d.plist";
    char str[255];
    for(int i = 1; i <= 12; i++) {
        sprintf(str, format, i);
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(str);
    }
    
    auto bk = Sprite::create("res/IMG_1341.jpg");
    bk->setAnchorPoint(Vec(0,0));
    addChild(bk);
    
    turnPointer = Sprite::createWithSpriteFrameName("misc/turnpointer.png");
    turnPointer->setVisible(false);
    addChild(turnPointer, 21);
    
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
    drawNodeAdd = DrawNode::create();
    drawNodeBorder = DrawNode::create();
    auto effectLayer = DrawNode::create();
    GameManager::getInstance()->setEffectLayer(effectLayer);
    
    addChild(drawNode, 10);
    addChild(drawNodeAdd, 11);
    addChild(drawNodeBorder, 12);
    addChild(effectLayer, 21);
    
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
    auto pawn = Pawn::create(graph->getTileAt(Vec(0, 0)), CharInfo("50,50,50,50,50,50,20"));
    pawns.push_back(pawn);
    this->addChild(pawn, 20);
    
    pawn = Pawn::create(graph->getTileAt(Vec(4, 4)), CharInfo("50,50,50,40,50,40,30"));
    pawns.push_back(pawn);
    this->addChild(pawn, 20);
    
    return true;
}

bool compareMinWait(const Pawn *lhs, const Pawn *rhs){
    return lhs->waitTime < rhs->waitTime;
}

void CombatLayer::setTurnPointerPosition() {
    turnPointer->setPosition(current->getTile()->getCoordinate() + Vec2(0, 70 + 10 * sin(MATH_DEG_TO_RAD(timedRotate * 5))));
}

void CombatLayer::update(float dt) {
    timedRotate = (timedRotate+1) % 360;
    
    int tileSize = GameManager::getInstance()->getTileSize();
    drawNode->clear();
    drawNodeAdd->clear();
    drawNodeAdd->setBlendFunc(BlendFunc::ADDITIVE);
    drawNodeBorder->clear();
    
    if (current) {
        if (!dragging) {
            CombatLayer::setTurnPointerPosition();
        }
        
        //TODO: fix this
        GridTile *citem = NULL;
        for (auto item : path) {
            if (citem != NULL) {
                auto v1 = citem->getCoordinate();
                auto v2 = item->getCoordinate();
                drawNodeBorder->drawSegment(v1, v2, 4, CB_RED);
            }
            citem = item;
        }
        
        auto n = Color4F(0, 0, 0, 0);
        Color4F coloured[COLUMNS][ROWS] = {
            {n,n,n,n,n,n,n,n},
            {n,n,n,n,n,n,n,n},
            {n,n,n,n,n,n,n,n},
            {n,n,n,n,n,n,n,n},
            {n,n,n,n,n,n,n,n},
            {n,n,n,n,n,n,n,n}
        };
        
        for (auto move : telegraphed) {
            auto l = move->location;
            auto v = move->getCoordinate();
            
            auto col = CB_RED;
            for (auto targ : targeted) {
                if (targ == current->getTile()) {
                    continue;
                } else if (move == targ) {
                    col = CB_DKRED;
                    break;
                }
            }
            
            coloured[l.x][l.y] = Color4F(col.r, col.g, col.b, 0.9);
        }
        
        for (auto move : viableMoves) {
            auto v = move->getCoordinate();
            auto l = move->location;
            auto x = l.x;
            auto y = l.y;
            auto width = 4;
            auto col = CB_SKBLUE;
            auto vTL = v + Vec2(-tileSize/2, tileSize/2);
            auto vTR = v + Vec2(tileSize/2, tileSize/2);
            auto vBL = v + Vec2(-tileSize/2, -tileSize/2);
            auto vBR = v + Vec2(tileSize/2, -tileSize/2);
            
            if (x == 0 or !viableMovesTable[x-1][y]) {
                drawNodeBorder->drawSegment(vTL, vBL, width, col);
            }
            
            if (x == COLUMNS-1 or !viableMovesTable[x+1][y]) {
                drawNodeBorder->drawSegment(vTR, vBR, width, col);
            }
            
            if (y == 0 or !viableMovesTable[x][y-1]) {
                drawNodeBorder->drawSegment(vBL, vBR, width, col);
            }
            
            if (y == ROWS-1 or !viableMovesTable[x][y+1]) {
                drawNodeBorder->drawSegment(vTL, vTR, width, col);
            }
            
            if (coloured[l.x][l.y] == n) {
                coloured[l.x][l.y] = Color4F(col.r, col.g, col.b, 0.9);
            }
        }
        
        for (auto i = 0; i < COLUMNS; ++i) {
            for (auto j = 0; j < ROWS; ++j) {
                auto tile = graph->getTileAt(Vec(i, j));
                auto v = tile->getCoordinate();
                auto vTR = v + Vec2(tileSize/2, tileSize/2);
                auto vBL = v + Vec2(-tileSize/2, -tileSize/2);
                drawNodeAdd->drawSolidRect(vBL, vTR, coloured[i][j]);
            }
        }
        
    } else {
        if (!GameManager::getInstance()->isAnimationRunning()) {
            std::vector<Pawn *> ready;
            for (auto pawn : pawns) {
                if (pawn->tick()) {
                    ready.push_back(pawn);
                }
            }
            if (ready.size() > 0) {
                auto it = std::min_element(ready.begin(), ready.end(),compareMinWait);
                current = *it;
                current->selected = true;
                turnPointer->setVisible(true);
                CombatLayer::setTurnPointerPosition();
            }
        }
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

void CombatLayer::generateViable() {
    viableMoves = reachableTiles(distData, current->info.MVE);
    
    // Cull occupied squares
    viableMoves.erase(std::remove_if(viableMoves.begin(), viableMoves.end(), [this](const GridTile *x) {
        return x->occupied and x != current->getTile();
    }), viableMoves.end());
    
    for (auto i = 0; i < COLUMNS; ++i) {
        for (auto j = 0; j < ROWS; ++j) {
            viableMovesTable[i][j] = false;
        }
    }
    
    for (auto move : viableMoves) {
        auto l = move->location;
        viableMovesTable[l.x][l.y] = true;
    }
}

void CombatLayer::generatePaths() {
    path = pathToTile(distData, destTile, viableMoves);
    
    auto tt = current->selectedAbility->telegraphedTargets(graph, pawns, current->getTile(), destTile);
    
    telegraphed = tt.first;
    targeted = tt.second;
}

void CombatLayer::setLastViable(GridTile *tile) {
    if (std::find(viableMoves.begin(), viableMoves.end(), tile) != viableMoves.end()) {
        destTile = tile;
    }
}

bool CombatLayer::onTouchBegan(Touch* touch, Event* event) {
    if (current) {
        if (touch && isTouchingSprite(touch, current)) {
            dragging = true;
            auto tile = current->getTile();
            distData = dijkstra(graph, tile);
            generateViable();
            setLastViable(tile);
            turnPointer->setVisible(false);
            generatePaths();
            return true;
        }
    }
    return false;
}

void CombatLayer::onTouchMoved(Touch* touch, Event* event) {
    if (current and dragging) {
        auto gotoTile = CombatLayer::getTileAt(touchToPoint(touch));
        if (destTile != gotoTile) {
            setLastViable(gotoTile);
            generatePaths();
        }
    }
}

void CombatLayer::onTouchEnded(Touch* touch, Event* event) {
    if (current and dragging) {
        current->jumpToDest(destTile);
        current->activate(destTile, graph, pawns);
        current = NULL;
        destTile = NULL;
        dragging = false;
        path.clear();
        viableMoves.clear();
        telegraphed.clear();
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

