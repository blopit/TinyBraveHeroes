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
    
    hpLabel = Label::createWithSystemFont("100", "arial", 20);
    hpLabel->setAnchorPoint(Vec2(0, 0));
    hpLabel->setTextColor(Color4B::WHITE);
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
    
    double width = hpLabel->getBoundingBox().size.width;
    double tileSize = GameManager::getInstance()->getTileSize() - 8 - width;
    double displaySize = width + 4 + tileSize * HP / maxHP;
    
    //hpLabel->setPosition(Vec2(5, 0));
    drawNode->drawSolidRect(Vec2(4 + width, 4), Vec2(displaySize, 12), Color4F::GREEN);
    
}
