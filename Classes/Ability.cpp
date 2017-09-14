//
//  Ability.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-08.
//
//

#include "Ability.hpp"
#include "Pawn.hpp"

void Ability::activate(GridTile *location, GridGraph *graph, std::vector<Pawn *> pawns) {
    
    for (auto pawn : pawns) {
        if (pawn == owner) continue;
        if (std::find(targeted.begin(), targeted.end(), pawn->getTile()) != targeted.end()) {
            trigger(pawn);
        }
    }
}

void Ability::trigger(Pawn *pawn) {
    pawn->damage(owner, weight, PHYSICAL);
}

vector<GridTile *> Ability::addAllTelegraphed(GridGraph *graph, GridTile *dest, telegraph t) {
    vector<GridTile *> telegraphed;
    Vec v = dest->location;
    for (auto i = 0; i < COLUMNS; ++i) {
        for (auto j = 0; j < ROWS; ++j) {
            int x = v.x-i+TELE_CENT;
            int y = j-v.y+TELE_CENT;
            if (t[x][y] == 1) {
                telegraphed.push_back(graph->getTileAt(Vec(i,j)));
            }
        }
    }
    return telegraphed;
}

vector<GridTile *> Ability::addAllTargets(vector<Pawn *> pawns, vector<GridTile *> telegraphed) {
    vector<GridTile *> targets;
    for (auto p : pawns) {
        auto x = p->getTile();
        if(std::find(telegraphed.begin(), telegraphed.end(), x) != telegraphed.end()) {
            targets.push_back(x);
        }
    }
    return targets;
}

Direction Ability::getDirection(GridTile *src, GridTile *dest) {
    auto x1 = src->location.x;
    auto y1 = src->location.y;
    auto x2 = dest->location.x;
    auto y2 = dest->location.y;
    
    float dy = y2-y1;
    float dx = x2-x1;
    float slope = 1.0;
    if (dx != 0) {
        slope = abs(dy/dx);
    }
    
    if (y2 > y1) {
        if (x2 > x1) {
            if (slope > 1) {
                return Direction::N;
            } else if (slope < 1) {
                return Direction::E;
            } else {
                return Direction::NE;
            }
        } else if (x1 > x2) {
            if (slope > 1) {
                return Direction::N;
            } else if (slope < 1) {
                return Direction::W;
            } else {
                return Direction::NW;
            }
        } else {
            return Direction::N;
        }
    } else if (y1 > y2) {
        if (x2 > x1) {
            if (slope > 1) {
                return Direction::S;
            } else if (slope < 1) {
                return Direction::E;
            } else {
                return Direction::SE;
            }
        } else if (x1 > x2) {
            if (slope > 1) {
                return Direction::S;
            } else if (slope < 1) {
                return Direction::W;
            } else {
                return Direction::SW;
            }
        } else {
            return Direction::S;
        }
    } else {
        if (x2 > x1) {
            return Direction::E;
        } else if (x1 > x2) {
            return Direction::W;
        } else {
            return Direction::NONE;
        }
    }
}

pair<vector<GridTile *>, vector<GridTile *>> Ability::telegraphedTargets(GridGraph *graph, vector<Pawn *> pawns, GridTile *src, GridTile *dest) {

    
    tele = line_50();
    tele = tele_direction(tele, getDirection(src, dest));
    tele = tele_subtract(tele, circfill_0());
    
    telegraphed = addAllTelegraphed(graph, dest, tele);
    targeted = addAllTargets(pawns, telegraphed);
    
    return make_pair(telegraphed, targeted);
}
