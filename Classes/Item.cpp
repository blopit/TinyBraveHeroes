//
//  Item.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-17.
//

#include "Item.hpp"

USING_NS_CC;

string Item::getDescription() {
    auto i = formatString(description.c_str(), int(w1));
    return i;
}

void Item::generateSpin(double angle, float scale) {
    
    auto rot = sin(MATH_DEG_TO_RAD(angle)) * 15;
    image->setRotation(rot);
}

Sprite *Item::generateSprite() {
    image = Sprite::create();
    auto rune = cocos2d::Sprite::createWithSpriteFrameName(sprite);
    
    auto plate = cocos2d::Sprite::createWithSpriteFrameName("runes/commonRune.png");
    
    switch (rarity) {
        case ItemRarity::UNCOMMON:
            plate = cocos2d::Sprite::createWithSpriteFrameName("runes/uncommonRune.png");
            break;
        case ItemRarity::RARE:
            plate = cocos2d::Sprite::createWithSpriteFrameName("runes/rareRune.png");
            break;
        case ItemRarity::EPIC:
            plate = cocos2d::Sprite::createWithSpriteFrameName("runes/epicRune.png");
            break;
        case ItemRarity::ELITE:
            plate = cocos2d::Sprite::createWithSpriteFrameName("runes/eliteRune.png");
            break;
        case ItemRarity::LEGENDARY:
            plate = cocos2d::Sprite::createWithSpriteFrameName("runes/legendaryRune.png");
            break;
        case ItemRarity::MYTHIC:
            plate = cocos2d::Sprite::createWithSpriteFrameName("runes/mythicRune.png");
            break;
        default:
            break;
    }

    image->addChild(rune, 2);
    image->addChild(plate, 1);
    
    return image;
}

std::string runePrefixFromItemRarity(ItemRarity rarity) {
    switch (rarity) {
        case ItemRarity::COMMON:
            return "Lesser ";
            break;
        case ItemRarity::UNCOMMON:
            return "Minor ";
            break;
        case ItemRarity::RARE:
            return "";
            break;
        case ItemRarity::EPIC:
            return "Greater ";
            break;
        case ItemRarity::ELITE:
            return "Major ";
            break;
        case ItemRarity::LEGENDARY:
            return "Superior ";
            break;
        case ItemRarity::MYTHIC:
            return "Ultimate ";
            break;
        default:
            break;
    }
    return "";
};

ItemPassive *getItemPassive(PassiveItemIndex pii, ItemRarity rarity, float level) {
    switch (pii) {
        case PassiveItemIndex::ELEPHANT:
            return new ElephantRune(rarity, level);
            break;
        case PassiveItemIndex::CROCODILE:
            return new CrocodileRune(rarity, level);
            break;
        default:
            assert(false);
            break;
    }
}
