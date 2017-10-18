//
//  CombatLogic.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-07.
//
//

#include "CombatLogic.hpp"
#include "Utils.hpp"

USING_NS_CC;

double cMULT(double X) {
    return (X + MID_CONST) / MID_CONST;
}

double cMIT(double X) {
    return X / (X + MID_CONST);
}

cocos2d::Color4F factionColour(const Faction f){
    switch (f) {
        case ALLY:
            return CB_SKBLUE;
            break;
        case ENEMY:
            return CB_RED;
            break;
        default:
            return CB_BLACK;
            break;
    }
}
