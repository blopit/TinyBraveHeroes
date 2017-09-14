//
//  Passive.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-13.
//
//

#include "Passive.hpp"
#include "Pawn.hpp"

void givePassive(Passive *passive, Pawn *target) {
    target->passives.push_back(passive);
    std::sort(target->passives.begin(), target->passives.end());
}

void Passive::purge() {
    expire();
}

void Passive::expire() {
    
}

void Passive::stack(int duration, double amount) {
    stacks += amount;
}

void Passive::tickDown() {
    timer++;
    duration--;
    if (duration <= 0) {
        expire();
    }
}

void Passive::tick(Trigger t) {
    tickDown();
    switch (t) {
        case PAWN_TICK:
            trigger_pawn_tick();
            break;
        default:
            break;
    }
}

void Bleed::trigger_pawn_tick() {
    if (timer % 5 == 0) {
        target->damage(src, 10, MAGICAL);
    }
}

void Protection30::trigger_before_damage_mit(double &damage, AttackType &at) {
    damage *= 1-stacks;
}
