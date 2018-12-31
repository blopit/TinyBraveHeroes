//
//  Item.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-17.
//

#ifndef Item_hpp
#define Item_hpp

#include <string>

#include "Utils.hpp"
#include "Ability.hpp"
#include "Passive.hpp"

class Item {
    string description;
public:
    ItemRarity rarity;
    string name, sprite;
    float w1, w2, powerMult, level;
    cocos2d::Sprite *image;
    
    Item(string name, string description, ItemRarity rarity, float level, string sprite) : name(name), description(description), rarity(rarity), sprite(sprite), level(level) {
        powerMult = ItemRarityMap.at(rarity).powerMult * level/MAXLEVEL;
    }
    cocos2d::Sprite *generateSprite();
    void generateSpin(double angle, float scale = 1.0f);
    string getDescription();
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
    UTILITY,
    OFF_DEF,
    OFF_UTIL,
    DEF_UTIL,
    ALL,
    SPECIAL
};

string runePrefixFromItemRarity(ItemRarity rarity);

class ItemPassive : public Item {
public:
    PassiveItemType type;
    ItemPassive(string name, string description, PassiveItemType type, ItemRarity rarity, float level, string sprite) : Item(name, description, rarity, level, sprite), type(type) {
        std::ostringstream stringStream;
        stringStream << runePrefixFromItemRarity(rarity) << "Rune of " << name;
        this->name = stringStream.str();
    }
};

enum class PassiveItemIndex {
    ELEPHANT,   //HP
    CROCODILE,  //ATT
    DOLPHIN,    //INT
    CLAM,       //DEF
    CHAMELEON,  //RES
    SNAKE,      //SPD
    BEAR,       //HP + ATT
    PIG,        //HP + INT
    GORILLA,    //
    POLAR_BEAR, //
    BOAR,
    HORSE,
    SPIDER,
    LION,
    TIGER,
    WOLF,
    EAGLE,
    CRAB,
    OCTOPUS,
    MANTIS,
    OWL,
    TURTLE,
    GOAT,
    RHINO,
    FROG,
    STAG,
    FALCON,
    SHARPNESS,
    TALENT,
    POWER,
    FURY,
    PRESERVATION,
    REMORSELESSNESS,
    REBIRTH,
    BLOODTHIRST,
    STUNNING,
    DAZING,
    UNDERDOG,
    SHIELDING,
    DODGING,
    STAGGERING,
    COUNTERING,
    METASTATIS,
    HEARTSEEKER,
    PENETRATION,
    FOCUS,
    REFLEX,
    MEDITATION,
    ATTACK_SPEED,
    SNIPER,
    ASSASSIN,
    CLOCK_CLEANER,
    PREDATOR,
    EXPLOITATION,
    PRESSURE,
    DISCIPLINE,
    POLISHING,
    IMPALING,
    PHALANX,
    HEALING,
    CARRION,
    BRAWLER,
    WEAKNESS,
    REGENERATION,
    VAMPIRE,
    DOOMSAYER,
    PYROMANCER,
    CONFUSION,
    VIGILANTE,
    VULNERABILITY,
    WILLPOWER,
    SHREDDING,
    LOOT,
    PRODIGY,
    MERCHANT,
    ENCHANTER,
    DEBILITATION,
    TITANIUM,
    KILLER,
    CORPSE_EATER,
    BLOOD_RUSH,
    REVENGE,
    WARRIOR,
    IMPATIENCE,
    PREEMPTION,
    WONDER,
    STABILITY,
    HIT_STUN,
    TRUE_LOVE,
    NEAR_SIGHTEDNESS,
    CALCULATION,
    SUPER_ARMOR,
    SMITE,
    CLEAVING,
    TRAILBLAZER,
    GIANT_SLAYER,
    DEATH,
    LIGHTNING,
    VICIOUSNESS,
    REAPER,
    SAFETY,
    SAVAGERY,
    DOUBLE_EDGED_SWORD,
    GLASS_CANNON,
    GROWTH,
    OVERHEATING,
    ENERGY,
    MARTYR,
    VENGENCE,
    QUICKSHOT,
    LAST_WORDS,
    ACCELERATION,
    COOLING,
    GIVING,
    SECURITY,
    POISON,
    BLEEDING,
    BURNING,
    SLOWING,
    PIERCING,
    COMBOING,
    HAZING,
    SURGING,
    REJUVINATION,
    ATTACKING,
    MAGIC,
    HEALTH,
    DEFENSE,
    RESISTANCE,
    CHARISMA,
    LONE_WOLF,
    THORNS,
    LEECHING,
    GREAT_ELEPHANT,
    GREAT_CROCODILE,
    GREAT_DOLPHIN,
    GREAT_CLAM,
    GREAT_CHAMELEON,
    GREAT_SNAKE,
};

class InvItem {
    PassiveItemIndex pii;
    ItemRarity rarity;
    float level;
};

/*
 Elephant Rune
 */
class ElephantRune: public ItemPassive {
public:
    ElephantRune(ItemRarity rarity, float level): ItemPassive("the Elephant", "Grants %d HP", PassiveItemType::DEFENSE, rarity, level, "passives/elephant.png") {
        w1 = floor(20.0f * powerMult);
    }
};

/*
 Crocodile Rune
 */
class CrocodileRune: public ItemPassive {
public:
    CrocodileRune(ItemRarity rarity, float level): ItemPassive("the Crocodile", "Grants %d ATT", PassiveItemType::OFFENSE, rarity, level, "passives/elephant.png") {
        w1 = floor(20.0f * powerMult);
    }
};



ItemPassive *getItemPassive(PassiveItemIndex pii, ItemRarity rarity, float level);

#endif /* Item_hpp */
