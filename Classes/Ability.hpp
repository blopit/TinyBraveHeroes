//
//  Ability.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-08.
//
//

#ifndef Ability_hpp
#define Ability_hpp

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
    Direction getDirection(GridTile *src, GridTile *dest);
    Direction getDirectionSimp1(GridTile *src, GridTile *dest);
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
    virtual pair<vector<GridTile *>, vector<GridTile *>> telegraphedTargets(GridGraph *graph, vector<Pawn *> pawns, GridTile *src, GridTile *dest);
    
    Ability(Pawn *owner) : owner(owner) {
        tele = teleo = claw_20();
    }
};

#endif /* Ability_hpp */
