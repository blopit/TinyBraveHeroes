//
//  Utils.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-17.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <cocos2d.h>

#define CB_BLACK cocos2d::Color4F(0.0, 0.0, 0.0, 1.0)
#define CB_SKBLUE cocos2d::Color4F(0.35, 0.7, 0.9, 1.0)     // #59B3E6
#define CB_BLUE cocos2d::Color4F(0, 0.45, 0.7, 1.0)         // #0070B0
#define CB_GREEN cocos2d::Color4F(0.0, 0.6, 0.5, 1.0)
#define CB_LTGREEN cocos2d::Color4F(0.4, 1.0, 0.6, 1.0)
#define CB_YELLOW cocos2d::Color4F(0.95, 0.9, 0.25, 1.0)    // #F3E63F
#define CB_ORANGE cocos2d::Color4F(0.9, 0.6, 0.0, 1.0)      // #E69900
#define CB_RED cocos2d::Color4F(0.8, 0.4, 0.0, 1.0)
#define CB_DKRED cocos2d::Color4F(0.85, 0.0, 0.0, 1.0)
#define CB_PINK cocos2d::Color4F(0.8, 0.6, 0.7, 1.0)
#define CB_WHITE cocos2d::Color4F(1.0, 1.0, 1.0, 1.0)
#define CB_PURPLE cocos2d::Color4F(0.6, 0.0, 1.0, 1.0)
#define CB_TEXT cocos2d::Color4F(0.7, 0.8, 1.0, 1.0)

#define CB_BLACK_A(A) cocos2d::Color4F(0.0, 0.0, 0.0, A)
#define CB_SKBLUE_A(A) cocos2d::Color4F(0.35, 0.7, 0.9, A)
#define CB_BLUE_A(A) cocos2d::Color4F(0, 0.45, 0.7, A)
#define CB_GREEN_A(A) cocos2d::Color4F(0.0, 0.6, 0.5, A)
#define CB_LTGREEN_A(A) cocos2d::Color4F(0.4, 1.0, 0.6, A)
#define CB_YELLOW_A(A) cocos2d::Color4F(0.95, 0.9, 0.25, A)
#define CB_ORANGE_A(A) cocos2d::Color4F(0.9, 0.6, 0.0, A)
#define CB_RED_A(A) cocos2d::Color4F(0.8, 0.4, 0.0, A)
#define CB_DKRED_A(A) cocos2d::Color4F(0.85, 0.0, 0.0, A)
#define CB_PINK_A(A) cocos2d::Color4F(0.8, 0.6, 0.7, A)
#define CB_WHITE_A(A) cocos2d::Color4F(1.0, 1.0, 1.0, A)
#define CB_PURPLE_A(A) cocos2d::Color4F(0.6, 0.0, 1.0, A)

#define PHI 1.61803398875f

#define MAXLEVEL 30

struct ItemRarityStruct {
    int value;
    cocos2d::Color4F color;
    std::string name;
    float powerMult;
    int minLevel;
    int maxLevel;
    ItemRarityStruct(std::string name, int value, cocos2d::Color4F color, float powerMult, int minLevel, int maxLevel): name(name), value(value), color(color), powerMult(powerMult), minLevel(minLevel), maxLevel(maxLevel) {};
};

enum class ItemRarity {
    COMMON,
    UNCOMMON,
    RARE,
    EPIC,
    ELITE,
    LEGENDARY,
    MYTHIC
};

//TODO: fix this
static std::map<ItemRarity, ItemRarityStruct> ItemRarityMap = {
    {ItemRarity::COMMON, ItemRarityStruct("Common", 1, CB_WHITE, 0.65f, 5, 15)},
    {ItemRarity::UNCOMMON, ItemRarityStruct("Uncommon", 1, CB_GREEN, 0.90f, 10, 20)},
    {ItemRarity::RARE, ItemRarityStruct("Rare", 1, CB_BLUE, 0.95f, 15, 25)},
    {ItemRarity::EPIC, ItemRarityStruct("Epic", 1, CB_PURPLE, 1.00f, 20, 30)},
    {ItemRarity::ELITE, ItemRarityStruct("Elite", 1, CB_YELLOW, 1.05f, 25, 30)},
    {ItemRarity::LEGENDARY, ItemRarityStruct("Legendary", 1, CB_ORANGE, 1.15f, 30, 30)},
    {ItemRarity::MYTHIC, ItemRarityStruct("Mythic", 1, CB_PINK, 1.20f, 30, 30)},
};

template <class T>
T boundToRange(T lower, T value, T upper) {
    return value < lower ? lower : value > upper ? upper : value;
}

std::string formatString(const char* format, ...);
cocos2d::Point touchToPoint(cocos2d::Touch * touch);
bool isTouching(cocos2d::Touch* touch, cocos2d::Rect rect);

#endif /* Utils_hpp */
