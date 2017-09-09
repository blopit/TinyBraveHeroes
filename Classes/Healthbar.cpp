//
//  Healthbar.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-08.
//
//

#include "Healthbar.hpp"
#include "GameManager.hpp"

USING_NS_CC;

bool Healthbar::init() {
    
    drawNode = DrawNode::create();
    drawNode->setAnchorPoint(Vec2(0, 0));
    addChild(drawNode);
    
    hpLabel =  Label::createWithTTF("100", "fonts/dpcomic.ttf", 24);
    hpLabel->setAnchorPoint(Vec2(0, 0));
    hpLabel->setTextColor(Color4B::WHITE);
    hpLabel->enableOutline(Color4B::BLACK, 3);
    hpLabel->setPosition(Vec2(6, 0));
    addChild(hpLabel);
    
    return true;
}

Healthbar::Healthbar() {
    maxHP = HP = simHP = dispHP = 100;
}

Healthbar *Healthbar::create() {
    Healthbar *pRet = new Healthbar();
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

void Healthbar::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) {
    
    drawNode->clear();
    
    auto width = hpLabel->getBoundingBox().size.width;
    auto tileSize = GameManager::getInstance()->getTileSize();
    auto displaySize = (tileSize - 16 - width) * HP / maxHP;
    auto start = 10 + width;
    auto v1 = Vec2(start, 8);
    auto v2 = Vec2(start + displaySize, 16);
    
    drawNode->drawSegment(v1, Vec2(v1.x,v2.y), 3, Color4F::BLACK);
    drawNode->drawSegment(v2, Vec2(v1.x,v2.y), 3, Color4F::BLACK);
    drawNode->drawSegment(v1, Vec2(v2.x,v1.y), 3, Color4F::BLACK);
    drawNode->drawSegment(v2, Vec2(v2.x,v1.y), 3, Color4F::BLACK);
    drawNode->drawSolidRect(v1, v2, Color4F::GREEN);
    
}
