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

bool Tooltip::init() {
    auto pos = this->getPosition() + Vec2(10, 10);
    
    drawNode = DrawNode::create();
    drawNode->setAnchorPoint(pos);
    
    auto nameLabel = Label::createWithTTF(name, "fonts/dpcomic.ttf", 36);
    nameLabel->setAnchorPoint(Vec2(0, 1));
    nameLabel->setPosition(pos + Vec2(10, TTH - 10));
    nameLabel->setColor(Color3B(CB_YELLOW));
    
    drawNode->drawSolidRect(pos, pos + Vec2(TTW, TTH), CB_BLACK_A(0.85));
    drawNode->drawRect(pos, pos + Vec2(TTW, TTH), CB_BLACK);
    
    description = "deal <phys>100<> damage to the enemy and then deal <mag>100<> damage after <h>1.25<> seconds";
    
    auto desc = Label::createWithTTF(description, "fonts/dpcomic.ttf", 24);
    desc->setAnchorPoint(Vec2(0, 1));
    desc->setPosition(pos + Vec2(10, TTH - 16 - nameLabel->getLineHeight()));
    desc->setColor(Color3B(CB_WHITE));
    desc->enableWrap(true);
    desc->setDimensions(TTW, 0);
    
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
        ranges.push_back(make_pair(make_pair(start, end), CB_SKBLUE));
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
                letter->setScale(1.3f);
            }
        }
    }
    
    addChild(drawNode, 0);
    addChild(nameLabel, 1);
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
