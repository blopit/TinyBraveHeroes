//
//  Character.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-17.
//

#ifndef Character_hpp
#define Character_hpp

#include "Ability.hpp"
#include "Item.hpp"

enum class CharRarity {
    NORMAL = 1,
    BRONZE = 2,
    SILVER = 3,
    GOLD = 4,
    PURPLE = 5
};

struct Attributes {
    int HP, ATT, INT, DEF, RES, SPD;
    
    Attributes(int HP, int ATT, int INT, int DEF, int RES, int SPD)
    : HP(HP), INT(INT), ATT(ATT), DEF(DEF), RES(RES), SPD(SPD) {}
    
    Attributes(const Attributes& a): HP(a.HP), INT(a.INT), ATT(a.ATT), DEF(a.DEF), RES(a.RES), SPD(a.SPD) {}
    
    Attributes operator+(const Attributes& a) const {
        return Attributes(a.HP+HP, a.ATT+ATT, a.INT+INT, a.DEF+DEF, a.RES+RES, a.SPD+SPD);
    }
    
    Attributes operator+(const float& a) const {
        return Attributes(a+HP, a+ATT, a+INT, a+DEF, a+RES, a+SPD);
    }
    
    Attributes operator*(const float& a) const {
        return Attributes(a*HP, a*ATT, a*INT, a*DEF, a*RES, a*SPD);
    }
    
    Attributes operator-(const Attributes& a) const {
        return Attributes(-a.HP+HP, -a.ATT+ATT, -a.INT+INT, -a.DEF+DEF, -a.RES+RES, -a.SPD+SPD);
    }
};

class Character {
    long exp;
    bool isMain = false;
    Attributes baseAttr;
    Attributes finalAttr;
    Attributes individualAttr;
    Attributes setLevel(int level);
    vector<ItemAbility *> abilities;     // 3 of these
    vector<ItemWeapon *> weapons;                 // 1 of these
    vector<ItemPassive *> passives; // 4 of these
    
public:
    Attributes attr;
    CharRarity rarity;
    int level;
    
    void giveExp(long amount);
    Character(Attributes baseAttr, Attributes finalAttr, Attributes individualAttr, int level, CharRarity rarity) : baseAttr(baseAttr), finalAttr(finalAttr), individualAttr(individualAttr), level(level), attr(baseAttr), rarity(rarity) {
        setLevel(level);
    }
    void setMain() {
        isMain = true;
    }
};

#endif /* Character_hpp */
