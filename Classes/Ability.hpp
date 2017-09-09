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
    void setTelegraph(const telegraph t);
    
public:
    double damage = 50;
    double waitTime = 20;
    telegraph tele;
    Pawn *owner;
    
    void activate(GridTile *location, GridGraph *graph, std::vector<Pawn *> pawns);
    void trigger(Pawn *pawn);
    
    Ability(Pawn *owner) : owner(owner) {
        setTelegraph(cross_30);
    }
};

#endif /* Ability_hpp */
