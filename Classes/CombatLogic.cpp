//
//  CombatLogic.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-07.
//
//

#include "CombatLogic.hpp"

double cMULT(double X) {
    return (X + MID_CONST) / MID_CONST;
}

double cMIT(double X) {
    return X / (X + MID_CONST);
}
