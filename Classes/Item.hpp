//
//  Item.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-17.
//

#ifndef Item_hpp
#define Item_hpp

#include "Utils.hpp"
#include "Ability.hpp"
#include "Passive.hpp"

class Item {
public:
    ItemRarity rarity;
    string name;
};

class ItemWeapon : Item {
public:
    WeaponIndex weaponidx;
};

class ItemAbility : Item {
public:
    AbilityIndex ablityidx;
};

enum class PassiveItemType {
    OFFENSE,
    DEFENSE,
    UTILITY
};

class ItemPassive : Item {
public:
    PassiveItemType type;
    PassiveBadgeIndex passiveidx;
};
#endif /* Item_hpp */
