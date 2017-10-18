//
//  Character.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-17.
//

#include "Character.hpp"
#include <iostream>
using namespace std;

Attributes Character::setLevel(int lvl){
    level = lvl;
    auto raritymult = 1 + ((static_cast<int>(rarity) - 3) * 0.1);
    float levelMult = float(level)/float(MAXLEVEL);
    
    auto hp = int(round(raritymult * (baseAttr.HP + levelMult * (finalAttr.HP + individualAttr.HP - baseAttr.HP))));
    auto att = int(round(raritymult * (baseAttr.ATT + levelMult * (finalAttr.ATT + individualAttr.ATT - baseAttr.ATT))));
    auto intt = int(round(raritymult * (baseAttr.INT + levelMult * (finalAttr.INT + individualAttr.INT - baseAttr.INT))));
    auto def = int(round(raritymult * (baseAttr.DEF + levelMult * (finalAttr.DEF + individualAttr.DEF - baseAttr.DEF))));
    auto res = int(round(raritymult * (baseAttr.RES + levelMult * (finalAttr.RES + individualAttr.RES - baseAttr.RES))));
    auto spd = int(round(raritymult * (baseAttr.SPD + levelMult * (finalAttr.SPD + individualAttr.SPD - baseAttr.SPD))));

    attr = Attributes(hp, att, intt, def, res, spd);
    
    cout << "LEVEL: " << level << endl;
    cout << "HP: " << hp << endl;
    cout << "ATT: " << att << endl;
    cout << "INT: " << intt << endl;
    cout << "DEF: " << def << endl;
    cout << "RES: " << res << endl;
    cout << "SPD: " << spd << endl;

    return attr;
}

long expFunctionSlow(int lvl, int rarity) {
    return (2 + rarity) * pow(lvl, 3) / 5;
}

void Character::giveExp(long amount) {
    cout << "giving: " << amount << endl;
    auto checkLevel = level+1;
    auto rare = static_cast<int>(rarity);
    exp += amount;
    
    if (exp >= expFunctionSlow(checkLevel, rare)) {
        //level up
        cout << "LEVEL UP" << endl;
        setLevel(checkLevel);
        checkLevel++;
        
        while (exp >= expFunctionSlow(checkLevel, rare)) {
            setLevel(checkLevel);
            checkLevel++;
        }
        
    }
    
}
