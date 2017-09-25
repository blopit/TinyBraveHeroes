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
    
    hpLabel =  Label::createWithTTF("HP", "fonts/dpcomic.ttf", 24);
    hpLabel->setAnchorPoint(Vec2(1, 0));
    hpLabel->setTextColor(Color4B::WHITE);
    hpLabel->enableOutline(Color4B::BLACK, 3);
    hpLabel->setPosition(Vec2(28, 0));
    addChild(hpLabel);
    
    this->scheduleUpdate();
    
    return true;
}

Healthbar::Healthbar(int hp) {
    maxHP = HP = simHP = dispHP = hp;
}

void Healthbar::update(float dt) {
    if (dispHP - HP > 0.5) {
        dispHP += (HP - dispHP) * 0.05;
    } else {
        dispHP = HP;
    }
}

Healthbar *Healthbar::create(int hp) {
    Healthbar *pRet = new Healthbar(hp);
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
    
    int dhp = boundToRange(0, (int)ceil(dispHP), 999) ;
    hpLabel->setString(std::to_string(dhp));
    auto width = 22; //hpLabel->getBoundingBox().size.width;
    
    auto tileSize = GameManager::getInstance()->getTileSize();
    auto totSize = (tileSize - 16 - width);
    auto dispSize = totSize * dispHP / maxHP;
    auto hpSize = totSize * HP / maxHP;
    auto start = 10 + width;
    auto v1 = Vec2(start, 8);
    auto v2 = Vec2(start + hpSize, 16);
    auto v3 = Vec2(start + dispSize, 16);
    auto v4 = Vec2(start + totSize, 16);
    
    drawNode->drawSolidRect(v1 + Vec2(-3, -3), v4 + Vec2(3, 3), CB_BLACK);
    drawNode->drawSolidRect(v1, v3, CB_DKRED);
    drawNode->drawSolidRect(v1, v2, CB_SKBLUE); //TODO: dynamic
    
}
