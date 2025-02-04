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
#include "Tooltip.hpp"

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
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/blood.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/cut.plist");
    
    auto bk = Sprite::create("res/IMG_1341.jpg");
    bk->setAnchorPoint(Vec(0,0));
    addChild(bk);
    
    turnPointer = Sprite::createWithSpriteFrameName("turnpointer.png");
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
    lastTile = NULL;
    drawNode = DrawNode::create();
    drawNodeAdd = DrawNode::create();
    drawNodeTele = DrawNode::create();
    drawNodeBorder = DrawNode::create();
    
    auto effectLayer = DrawNode::create();
    GameManager::getInstance()->setEffectLayer(effectLayer);
    auto particleLayer = DrawNode::create();
    GameManager::getInstance()->setParticleLayer(particleLayer);
    auto backLayer = DrawNode::create();
    GameManager::getInstance()->setBackLayer(backLayer);
    
    addChild(drawNode, 10);
    addChild(drawNodeAdd, 11);
    addChild(drawNodeTele, 11);
    addChild(drawNodeBorder, 13);
    addChild(backLayer, 14);
    addChild(particleLayer, 21);
    addChild(effectLayer, 22);
    
    auto tt = Tooltip::create("Thunderbolt", "ccc", "shoot thunder n shit");
    addChild(tt, 23);
    
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
    
    pawn = Pawn::create(graph->getTileAt(Vec(4, 4)), CharInfo("50,100,0,40,50,40,30"));
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

float rotateToTarget(float cur, float tar, float speed) {
    auto a = (tar - cur);
    float angleDiff = (int(a + 180) % 360) - 180;
    if (abs(angleDiff) < speed) {
        return tar;
    } else {
        return cur + (angleDiff < 0 ? -1 : 1) * speed;
    }
}

float rotateToTargetFactor(float cur, float tar, float factor) {
    auto a = (tar - cur);
    float angleDiff = fmod(a + 180, 360) - 180;
    float speed = abs(angleDiff) * factor;
    
    if (abs(angleDiff) <= speed) {
        return tar;
    } else {
        return cur + (angleDiff < 0 ? -1 : 1) * speed;
    }
}

void CombatLayer::update(float dt) {
    timedRotate = (timedRotate+1) % 360;
    
    int tileSize = GameManager::getInstance()->getTileSize();
    drawNode->clear();
    drawNodeAdd->clear();
    drawNodeAdd->setBlendFunc(BlendFunc::ADDITIVE);
    drawNodeTele->clear();
    drawNodeTele->setBlendFunc(BlendFunc::ADDITIVE);
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
            //auto l = move->location;
            auto v = move->getCoordinate();
            
            auto col = CB_WHITE;
            auto a = 0.45;
            for (auto targ : targeted) {
                if (targ == current->getTile()) {
                    continue;
                } else if (move == targ) {
                    col = CB_DKRED;
                    a = 0.9;
                    
                    auto vTR = v + Vec2(tileSize/2, tileSize/2);
                    auto vBL = v + Vec2(-tileSize/2, -tileSize/2);
                    drawNodeBorder->drawSolidRect(vBL, vTR, CB_DKRED_A(0.65));
                    
                    break;
                }
            }
            
            //coloured[l.x][l.y] = Color4F(col.r, col.g, col.b, a);
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
        
        if (dragging) {
            for (auto i = 0; i < TELE_SIZE; ++i) {
                for (auto j = 0; j < TELE_SIZE; ++j) {
                    auto t = current->selectedAbility->teleo[i][j];
                    if (t != 0 and t != 2) {
                        auto d = Vec2(tileSize * (i-TELE_CENT), tileSize * (j-TELE_CENT));
                        auto vTR = d + Vec2(tileSize/2, tileSize/2);
                        auto vBL = d + Vec2(-tileSize/2, -tileSize/2);
                        drawNodeTele->drawSolidRect(vBL, vTR, CB_ORANGE_A(0.95));
                    }
                }
            }
            
            drawNodeTele->setRotation(rotateToTargetFactor(drawNodeTele->getRotation(), current->selectedAbility->rotation, 0.3));
            
            if (mouse.distance(prevMouse) < 10) {
                idle++;
            } else {
                idle = 0;
            }
            
            if (idle > 30) {
                auto dest = destTile->getCoordinate();
                auto current = drawNodeTele->getPosition();
                drawNodeTele->setPosition(current + (dest - current) * 0.3);
            } else {
                drawNodeTele->setPosition(mouse);
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
    
    auto tt = current->selectedAbility->telegraphedTargets(graph, pawns, destTile, deltaMouse);
    
    telegraphed = tt.first;
    targeted = tt.second;
}

void CombatLayer::setLastViable(GridTile *tile) {
    if (std::find(viableMoves.begin(), viableMoves.end(), tile) != viableMoves.end()) {
        destTile = tile;
    }
}

bool CombatLayer::onTouchBegan(Touch* touch, Event* event) {
    prevMouse = Vec(0, 0);
    mouse = touch->getLocation();
    if (current) {
        if (touch && isTouchingSprite(touch, current)) {
            dragging = true;
            auto tile = current->getTile();
            distData = dijkstra(graph, tile);
            generateViable();
            setLastViable(tile);
            turnPointer->setVisible(false);
            generatePaths();
            lastTile = NULL;
            return true;
        }
    }
    return false;
}

void CombatLayer::onTouchMoved(Touch* touch, Event* event) {
    prevMouse = mouse;
    mouse = touch->getLocation();
    
    if (mouse.distance(prevMouse) > 5 and idle >= 30) {
        idle = 0;
    }
    
    if (current and dragging) {
        auto gotoTile = CombatLayer::getTileAt(touchToPoint(touch));
        
        if (destTile != gotoTile) {
            
            deltaMouse = gotoTile->getCoordinate() - destTile->getCoordinate();
            
            if (std::find(viableMoves.begin(), viableMoves.end(), gotoTile) != viableMoves.end()) {
                
                vector<GridTile*> adjmoves;
                copy_if(begin(viableMoves), end(viableMoves), back_inserter(adjmoves), [=] (const GridTile *p1) -> bool {
                    return Vec2(p1->location).distance(gotoTile->location) == 1;
                });
                
                if (adjmoves.size() > 0) {
                    lastTile = *min_element(adjmoves.begin(), adjmoves.end(), [=] (const GridTile *p1, const GridTile *p2) -> bool {
                        return Vec2(p1->location).distance(destTile->location) < Vec2(p2->location).distance(destTile->location);
                    });
                } else {
                    lastTile = NULL;
                }
                
                destTile = gotoTile;
            }
            
            generatePaths();
        }
    }
}

void CombatLayer::onTouchEnded(Touch* touch, Event* event) {
    prevMouse = Vec(0, 0);
    mouse = touch->getLocation();
    if (current and dragging) {
        current->jumpToDest(destTile);
        current->activate(destTile, graph, pawns);
        current = NULL;
        destTile = NULL;
        dragging = false;
        setangle = false;
        idle = 0;
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

