//
//  Ability.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-08.
//
//

#include "Ability.hpp"
#include "Pawn.hpp"

void Ability::setTelegraph(const telegraph t) {
    memcpy(&tele[0][0], &t[0][0], sizeof(int)*(COLUMNS*2-1)*(ROWS*2-1));
    
}

void Ability::activate(GridTile *location, GridGraph *graph, std::vector<Pawn *> pawns) {
    
    for (auto pawn : pawns) {
        if (pawn == owner) continue;
        trigger(pawn);
    }
}

void Ability::trigger(Pawn *pawn) {
    pawn->setHP(pawn->getHP() - damage);
}
