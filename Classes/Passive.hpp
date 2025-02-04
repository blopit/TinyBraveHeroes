//
//  Passive.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-13.
//
//

#ifndef Passive_hpp
#define Passive_hpp

#include "CombatLogic.hpp"

#define DEFAULT_MAX_TRIGGERS 16
#define INFINITE_DURATION -1

class Pawn;

typedef enum {
    HIGHEST = 0,
    HIGH = 1,
    NORMAL = 2,
    LOW = 3,
    LOWEST = 4
}Priority;

enum Type {
    BUFF, DEBUFF, NEUTRAL, AILMENT
};

class Passive;

void givePassive(Passive *passive, Pawn *target);

class Passive {
    virtual void tickDown();
protected:
    Pawn *src;
    Pawn *target;
    int duration;
    int timer;
    int triggerCount = 0;
    int maxTriggers = DEFAULT_MAX_TRIGGERS;
    bool infinite;
    double stacks;
    std::string name;
public:
    Passive(std::string name, Pawn *src, Pawn *target, int duration, int stacks, std::vector<Trigger> triggers, Priority priority, Type type) : name(name), src(src), target(target), duration(duration), stacks(stacks), triggers(triggers), priority(priority), type(type), infinite(false) {
        if (duration == INFINITE_DURATION) {
            infinite = true;
        }
        givePassive(this, target);
    }
    Passive(std::string name, Pawn *src, Pawn *target, int stacks, std::vector<Trigger> triggers, Priority priority, Type type) : name(name), src(src), target(target), duration(0), stacks(stacks), triggers(triggers), priority(priority), type(type), infinite(true) {
        givePassive(this, target);
    }
    virtual void purge();
    virtual void expire();
    virtual void stack(int duration, double amount);
    virtual void tick(Trigger t);
    std::vector<Trigger> triggers;
    Priority priority;
    Type type;
    friend bool operator< (const Passive &i, const Passive &j) { return (i.priority < j.priority);}
    
    bool trigger();
    virtual void trigger_pawn_tick() { triggerCount++; };
    virtual void trigger_before_damage_mit(double &damage, AttackType &at) {};
};

// PASSIVES

class Bleed : public Passive {
public:
    void trigger_pawn_tick() override;
    Bleed(Pawn *src, Pawn *target, int duration, int stacks) : Passive("Bleed", src, target, duration, stacks, std::vector<Trigger> {PAWN_TICK}, Priority::NORMAL, Type::DEBUFF) {}
};

class Protection30 : public Passive {
    
public:
    void trigger_before_damage_mit(double &damage, AttackType &at) override;
    Protection30(Pawn *src, Pawn *target, int duration, double amount) : Passive("Protection", src, target, duration, amount, std::vector<Trigger> {BEFORE_DAMAGE_MIT}, Priority::NORMAL, Type::BUFF) {}
};

//TODO: remove
/*enum class PassiveBadgeIndex {
    NONE,
    BLEED,
    PROTECT
};

Passive *passiveFromIndex(PassiveBadgeIndex ai, Pawn *owner) {
    switch (ai) {
        case PassiveBadgeIndex::NONE:
            return NULL;
            break;
        case PassiveBadgeIndex::BLEED:
            return new Protection30(owner, owner, INFINITE_DURATION, 30);
            break;
        default:
            return NULL;
            break;
    }
}*/

#endif /* Passive_hpp */
