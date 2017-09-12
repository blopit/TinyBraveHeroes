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

class Ability {
    vector<GridTile *> addAllTargets(vector<Pawn *> pawns, vector<GridTile *> telegraphed);
    vector<GridTile *> addAllTelegraphed(GridGraph *graph, GridTile *dest, telegraph t);
    Direction getDirection(GridTile *src, GridTile *dest);
    
    vector<GridTile *> targeted;
    vector<GridTile *> telegraphed;
    
public:
    double damage = 50;
    double waitTime = 20;
    telegraph tele;
    Pawn *owner;
    
    void activate(GridTile *location, GridGraph *graph, std::vector<Pawn *> pawns);
    void trigger(Pawn *pawn);
    pair<vector<GridTile *>, vector<GridTile *>> telegraphedTargets(GridGraph *graph, vector<Pawn *> pawns, GridTile *src, GridTile *dest);
    
    Ability(Pawn *owner) : owner(owner) {
        tele = line_50();
    }
};

#endif /* Ability_hpp */
