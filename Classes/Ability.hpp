//
//  Ability.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-08.
//
//

#ifndef Ability_hpp
#define Ability_hpp

#include "Utils.hpp"
#include "Telegraph.hpp"
#include "GridGraph.hpp"

class Pawn;

enum class MoveModifier {
    ADDTIVE,
    SET,
    NONE
};

class Ability {
    vector<GridTile *> addAllTargets(vector<Pawn *> pawns, vector<GridTile *> telegraphed);
    vector<GridTile *> addAllTelegraphed(GridGraph *graph, GridTile *dest, telegraph t);
    Direction getDirection(cocos2d::Vec2 delta);
    Direction getDirectionSimp1(cocos2d::Vec2 delta);
    vector<GridTile *> targeted;
    vector<GridTile *> telegraphed;
    
public:
    double weight = 20; // Ai stuff???
    
    double waitTime = 20;
    double castTime = 0;
    double cooldownTime = 0;
    MoveModifier moveModType = MoveModifier::SET;
    double moveMod = 20;
    float rotation = 0;
    
    telegraph tele;
    telegraph teleo;
    Pawn *owner;
    
    virtual void activate(GridTile *location, GridGraph *graph, std::vector<Pawn *> pawns);
    virtual void trigger(Pawn *pawn);
    virtual pair<vector<GridTile *>, vector<GridTile *>> telegraphedTargets(GridGraph *graph, vector<Pawn *> pawns, GridTile *dest, cocos2d::Vec2 delta);
    
    Ability(Pawn *owner) : owner(owner) {
        tele = teleo = claw_20();
    }
};

enum class AbilityIndex {
    NONE,
    CLAW,
};

Ability *abilityFromIndex(AbilityIndex ai, Pawn *owner, ItemRarity rarity) {
    switch (ai) {
        case AbilityIndex::NONE:
            return NULL;
            break;
        case AbilityIndex::CLAW:
            return new Ability(owner);
            break;
        default:
            return NULL;
            break;
    }
}

enum class WeaponIndex {
    NONE,
    CLAW,
};

Ability *weaponFromIndex(WeaponIndex ai, Pawn *owner, ItemRarity rarity) {
    switch (ai) {
        case WeaponIndex::NONE:
            return NULL;
            break;
        case WeaponIndex::CLAW:
            return new Ability(owner);
            break;
        default:
            return NULL;
            break;
    }
}

#endif /* Ability_hpp */
