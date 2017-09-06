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
    
    currentSprite = Sprite::create("res/whitepawn.png");
    currentSprite->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    addChild(currentSprite, 2);
    
    landingSprite = Sprite::create("res/marker0.png");
    landingSprite->setPosition(Vec2(0,0));
    addChild(landingSprite, 0);
    
    dragging = false;
    
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(CombatLayer::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(CombatLayer::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(CombatLayer::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto winWidth = Director::getInstance()->getWinSize().width;
    auto winHeight = Director::getInstance()->getWinSize().height;
    tileSize = Director::getInstance()->getWinSize().width / 6;

    auto node = DrawNode::create();
    
    std::cout << "BEGAN" << std::endl;
    
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
    
    return true;
}

Point CombatLayer::touchToPoint(Touch * touch) {
    return Director::getInstance()->convertToGL(touch->getLocationInView());
}

bool CombatLayer::isTouchingSprite(Touch* touch) {
    return (currentSprite->getPosition().getDistance(touchToPoint(touch)) < 100.0f);
}

Vec2 CombatLayer::getClosestTile(Vec2 p) {
    auto winWidth = Director::getInstance()->getWinSize().width;
    auto winHeight = Director::getInstance()->getWinSize().height;
    auto offsetx = (tileSize + winWidth) / 2;
    auto offsety = (tileSize + winHeight) / 2;
    
    int x = round((p.x - offsetx) / ((float) tileSize)) * tileSize + offsetx;
    int y = round((p.y - offsety) / ((float) tileSize)) * tileSize + offsety;
    
    if (x > offsetx + tileSize * 2) {
        x = offsetx + tileSize * 2;
    } else if (x < offsetx - tileSize * 3) {
        x = offsetx - tileSize * 3;
    }
    
    if (y > offsety + tileSize * 3) {
        y = offsety + tileSize * 3;
    } else if (y < offsety - tileSize * 4) {
        y = offsety - tileSize * 4;
    }
    
    return Vec2(x, y);
}

void CombatLayer::onTouchesBegan(const std::vector<Touch*>& touches, Event* event) {
    touchOffset = Point::ZERO;
    for (auto touch : touches) {
        if (touch && isTouchingSprite(touch)) {
            currentSprite->setPosition(touchToPoint(touch) + touchOffset);
            dragging = true;
        }
    }
}

void CombatLayer::onTouchesMoved(const std::vector<Touch*>& touches, Event* event) {
    //std::cout << "MOVED" << std::endl;
    for (auto touch : touches) {
        if (dragging) {
            currentSprite->setPosition(touchToPoint(touch) + touchOffset);
            auto landing = CombatLayer::getClosestTile(touchToPoint(touch));
            landingSprite->setPosition(landing);
        }
    }
}

void CombatLayer::onTouchesEnded(const std::vector<Touch*>& touches, Event* event) {
    dragging = false;
}
