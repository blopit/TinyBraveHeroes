//
//  CombatLogic.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-07.
//
//

#ifndef CombatLogic_hpp
#define CombatLogic_hpp

#define MID_CONST 50

enum Faction {
    ALLY,
    ENEMY,
    THIRD_PARTY_ENEMY,
    THIRD_PARTY_ALLY
};

enum Trigger {
    EMPTY,
    PAWN_TICK,
    BEFORE_DAMAGE_MIT,
    AFTER_DAMAGE_MIT
};

enum AttackType {
    PHYSICAL,
    MAGICAL,
    PURE,
    MIXED
};

cocos2d::Color4F factionColour(const Faction f);
double cMULT(double X);
double cMIT(double X);

#endif /* CombatLogic_hpp */
