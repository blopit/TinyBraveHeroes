//
//  Tooltip.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-03.
//
#include <regex>
#include <iostream>

#include "GameManager.hpp"
#include "Tooltip.hpp"

USING_NS_CC;

void Tooltip::update(float dt) {
    
}

bool Tooltip::init() {
    setCascadeOpacityEnabled(true);
    this->setOpacity(0);
    auto pos = this->getPosition() + Vec2(10, 10);
    
    drawNode = DrawNode::create();
    drawNode->setAnchorPoint(pos);
    
    description = "Deal <mag>100 magical<> damage to the target every <h>5 ticks<>";
    auto desc = Label::createWithTTF(description, "fonts/dpcomic.ttf", 24);
    desc->enableWrap(true);
    desc->setDimensions(TTW - 20, 0);
    desc->setColor(Color3B(CB_TEXT));
    vector<pair<pair<int, int>, Color4F>> ranges;
    
    std::smatch match;
    std::regex phys ("<phys>(.*?)<>");
    while (std::regex_search (description, match, phys)) {
        auto start = match.position();
        auto end = start + match.length() - 8;
        ranges.push_back(make_pair(make_pair(start, end), CB_ORANGE));
        description = std::regex_replace(description, phys, "$1", std::regex_constants::format_first_only);
    }
    std::regex mag ("<mag>(.*?)<>");
    while (std::regex_search (description, match, mag)) {
        auto start = match.position();
        auto end = start + match.length() - 7;
        ranges.push_back(make_pair(make_pair(start, end), CB_BLUE));
        description = std::regex_replace(description, mag, "$1", std::regex_constants::format_first_only);
    }
    std::regex h ("<h>(.*?)<>");
    while (std::regex_search (description, match, h)) {
        auto start = match.position();
        auto end = start + match.length() - 5;
        ranges.push_back(make_pair(make_pair(start, end), CB_WHITE));
        description = std::regex_replace(description, h, "$1", std::regex_constants::format_first_only);
    }
    
    desc->setString(description);
    
    for (auto m : ranges) {
        auto p = m.first;
        for(int i = p.first; i < p.second; i++) {
            auto letter = desc->getLetter(i);
            if (letter) {
                letter->setColor(Color3B(m.second));
                letter->setScale(1.1f);
            }
        }
    }
    auto TTH = 100 + desc->getLineHeight() * desc->getStringNumLines();
    
    auto nameLabel = Label::createWithTTF(name, "fonts/dpcomic.ttf", 36);
    nameLabel->setAnchorPoint(Vec2(0, 1));
    nameLabel->setPosition(pos + Vec2(10, TTH - 10));
    nameLabel->setColor(Color3B(CB_YELLOW));
    
    drawNode->drawSolidRect(pos, pos + Vec2(TTW, TTH), CB_BLACK_A(0.85));
    drawNode->drawRect(pos, pos + Vec2(TTW, TTH), CB_WHITE_A(0.85));
    
    ////////
    
    auto right = Label::createWithTTF("# 3   % 10   @ 20", "fonts/dpcomic.ttf", 24);
    right->setAnchorPoint(Vec2(0, 1));
    right->setPosition(pos + Vec2(20, TTH - 20 - nameLabel->getLineHeight()));
    right->setColor(Color3B(CB_WHITE));
    right->setCascadeOpacityEnabled(true);
    
    for (auto i = 0; i < right->getStringLength(); i++) {
        char c = right->getString()[i];
        if (c == '%') {
            auto wait = Sprite::createWithSpriteFrameName("wait.png");
            auto l = right->getLetter(i);
            wait->setPosition(Vec2(l->getPosition().x-2,12));
            right->addChild(wait);
            l->setVisible(false);
        } else if (c == '@') {
            auto wait = Sprite::createWithSpriteFrameName("cooldown.png");
            auto l = right->getLetter(i);
            wait->setPosition(Vec2(l->getPosition().x-2,12));
            right->addChild(wait);
            l->setVisible(false);
        } else if (c == '#') {
            auto wait = Sprite::createWithSpriteFrameName("cast.png");
            auto l = right->getLetter(i);
            wait->setPosition(Vec2(l->getPosition().x-2,12));
            right->addChild(wait);
            l->setVisible(false);
        }
        
    }
    
    
    //////
    
    desc->setAnchorPoint(Vec2(0, 1));
    desc->setPosition(pos + Vec2(10, TTH - 30 - nameLabel->getLineHeight() - right->getLineHeight()));
    
    /////////
    
    auto t = line_50();
    auto spos = pos + Vec2(TTW - 40, TTH - 40);
    for (auto i = 0; i < TELE_SIZE; i++) {
        for (auto j = 0; j < TELE_SIZE; j++) {
            if (t[i][j] != 0) {
                auto col = CB_WHITE;
                auto skip = false;
                auto v1 = Vec2(spos + Vec2((i-TELE_CENT) * 7, (j-TELE_CENT) * 7));
                
                switch (t[i][j]) {
                    case 1:
                        col = CB_RED;
                        break;
                    case 2:
                        col = CB_SKBLUE;
                        drawNode->drawSolidCircle(v1 + Vec2(2.5f, 2.5f), 2.5, 0, 8, 1, 1, col);
                        skip = true;
                        break;
                    case 3:
                        col = CB_LTGREEN;
                        break;
                    default:
                        break;
                }
                
                if (!skip) {
                    drawNode->drawSolidRect(v1, v1 + Vec2(5, 5), col);
                }
            }
        }
    }
    
    
    addChild(drawNode, 0);
    addChild(nameLabel, 1);
    addChild(right, 1);
    addChild(desc, 1);
    return true;
}

Tooltip *Tooltip::create(std::string name, std::string right, std::string description) {
    Tooltip *pRet = new Tooltip(name, right, description);
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
