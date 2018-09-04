//
//  Pawn.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-05.
//
//

#include <iostream>
#include <string>
#include "Pawn.hpp"
#include "Utils.hpp"
#include "Passive.hpp"
#include "GameManager.hpp"

USING_NS_CC;

bool Pawn::init() {
    hero = Sprite::createWithSpriteFrameName("whitepawn.png");
    addChild(hero, 0);
    
    overlay = Sprite::createWithSpriteFrameName("whitepawn.png");
    addChild(overlay, 1);
    
    
    drawNode = DrawNode::create();
    addChild(drawNode, 1);
    BlendFunc brightnessBlend;
    brightnessBlend.src = GL_DST_ALPHA;
    brightnessBlend.dst = GL_ZERO;
    drawNode->setBlendFunc(brightnessBlend);
    
    waitLabel = Label::createWithTTF("wait", "fonts/dpcomic.ttf", 24);    waitLabel->setAnchorPoint(Vec2(0, 1));
    waitLabel->setTextColor(Color4B(Color4F(0.3, 1, 0, 1)));
    waitLabel->enableOutline(Color4B::BLACK, 3);
    addChild(waitLabel, 2);
    
    healthbar = Healthbar::create(maxHP);
    addChild(healthbar, 2);
    
    hero->setPosition(tile->getCoordinate());
    return true;
}

Pawn *Pawn::create(GridTile *tile, CharInfo info) {
    Pawn *pRet = new Pawn(tile, info);
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

Pawn::Pawn(GridTile *tile, CharInfo info): tile(tile), info(info){
    maxHP = HP = info.HP;
    tile->occupied = true;
    waitTime = 0.0;
    selectedAbility = new Ability(this); //TODO: fix
    
    //givePassive(new Bleed(this, this, 50, 1), this);
}

void Pawn::activate(GridTile *location, GridGraph *graph, std::vector<Pawn *> pawns) {
    selectedAbility->activate(location, graph, pawns);
    waitTime += selectedAbility->waitTime;
}

void Pawn::draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) {
    
    auto h = boundToRange(0.0f, highlightLeveL, 1.0f);
    if (h > 0) {
        drawNode->setVisible(true);
        drawNode->clear();
        drawNode->drawSolidRect(Vec2(0,0), Vec2(256,256), highlight);
        
        auto *renderTexture = RenderTexture::create(256, 256);
        renderTexture->setPosition(Vec2(0,0));
        renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
        auto mask = Sprite::createWithSpriteFrameName("whitepawn.png");
        mask->setPosition(Vec2(128, 128));
        mask->visit();
        drawNode->visit();
        renderTexture->end();
        
        overlay->setTexture(renderTexture->getSprite()->getTexture());
        overlay->setTextureRect(Rect(0, 0, 256, 256));
        
        auto b = h * 0.2f;
        overlay->setScale(1.0f + b, -1.0f - b);
        overlay->setOpacity(h * 255.0f);
        overlay->setPosition(hero->getPosition());
        drawNode->setVisible(false);
    }
    
    int tileSize = GameManager::getInstance()->getTileSize();
    
    if (!selected) {
        waitLabel->draw(renderer, transform, transformFlags);
        waitLabel->setVisible(true);
        waitLabel->setString(std::to_string(remainingWait()));
        waitLabel->setPosition(hero->getPosition() + Vec2(-tileSize/2 + 6, tileSize/2));
        waitLabel->draw(renderer, transform, transformFlags);
    } else {
        waitLabel->setVisible(false);
    }
    
    healthbar->setPosition(hero->getPosition() + Vec2(-tileSize/2, -tileSize/2));
    
    highlightLeveL = highlightLeveL - highlightSpeed < 0 ? 0 : highlightLeveL - highlightSpeed;
}
double Pawn::waitSpeed() {
    return cMULT(info.SPD);
}

int Pawn::remainingWait() {
    double waitSpeed = Pawn::waitSpeed();
    if (waitSpeed == 0) {
        return 999.0;
    }
    auto x = (int) ceil(waitTime / waitSpeed);
    
    return boundToRange(0, x, 999);
}

bool Pawn::tick() {
    double waitSpeed = Pawn::waitSpeed();
    waitTime -= waitSpeed;
    
    triggerPassives(Trigger::PAWN_TICK);
    hero->setPosition(tile->getCoordinate());
    
    return waitTime <= 0;
}

void Pawn::setHP(double HP_){
    HP = HP_;
    //healthbar->HP = HP;
}

void Pawn::catchupDisplayHP(){
    healthbar->HP = HP;
}

double Pawn::getHP(){
    return HP;
}
void Pawn::setTile(GridTile* newTile, GridGraph* graph) {
    tile = newTile;
}

GridTile* Pawn::getTile() {
    return tile;
}

void Pawn::jumpToDest(GridTile* destTile) {
    tile->occupied = false;
    tile = destTile;
    selected = false;
    tile->occupied = true;
}

void Pawn::triggerPassives(Trigger t) {
    for (auto p : passives) {
        if (std::find(p->triggers.begin(), p->triggers.end(), t) == p->triggers.end()) continue;
        p->tick(t);
    }
}

void Pawn::damage(Pawn *src, double amount, AttackType at) {
    double removal = amount;
    
    for (auto p : passives) {
        if (std::find(p->triggers.begin(), p->triggers.end(), Trigger::BEFORE_DAMAGE_MIT) == p->triggers.end()) continue;
        p->trigger_before_damage_mit(amount, at);
    }
    
    switch (at) {
        case PHYSICAL:
            removal *= (1-cMIT(info.DEF));
            break;
        case MAGICAL:
            removal *= (1-cMIT(info.RES));
            break;
        case MIXED:
            removal *= (1-cMIT((info.RES+info.DEF)/2));
            break;
        default:
            break;
    }
    
    triggerPassives(Trigger::AFTER_DAMAGE_MIT);
    
    setHP(getHP() - removal);
}
