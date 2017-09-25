//
//  Pawn.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-05.
//
//

#ifndef Pawn_hpp
#define Pawn_hpp

#include "GridGraph.hpp"
#include "cocos2d.h"
#include "CombatLogic.hpp"
#include "Ability.hpp"
#include "Healthbar.hpp"

class Passive;

struct CharInfo {
    int HP, ATT, INT, DEF, RES, SPD, MVE;
    
    CharInfo(int HP, int ATT, int INT, int DEF, int RES, int SPD, int MVE) : HP(HP), ATT(ATT), INT(INT), DEF(DEF), RES(RES), SPD(SPD), MVE(MVE) {}
    CharInfo(string str) {
        std::vector<int> vec;
        std::stringstream ss(str);
        int i;
        while (ss >> i) {
            vec.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }
        assert(vec.size() == 7);
        HP = vec[0];
        ATT = vec[1];
        INT = vec[2];
        DEF = vec[3];
        RES = vec[4];
        SPD = vec[5];
        MVE = vec[6];
    }
    string to_string() {
        std::stringstream fmt;
        fmt << HP << "," << ATT << "," << INT << "," << DEF << "," << RES << "," << SPD << "," << MVE;
    }
};

class Pawn : public cocos2d::Node {
    virtual bool init() override;
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override;
    Pawn(GridTile *tile, CharInfo info);
    GridTile *tile;
    cocos2d::DrawNode *drawNode;
    Healthbar *healthbar;
    cocos2d::Label *waitLabel;

    double maxHP, HP;
    
public:
    cocos2d::Color4F highlight = cocos2d::Color4F::WHITE;
    float highlightLeveL = 0.5f;
    float highlightSpeed = 0.03f;
    
    static Pawn* create(GridTile *tile, CharInfo info);
    vector<Passive *> passives;
    
    CharInfo info;
    bool selected = false;
    
    double waitTime;
    double waitSpeed();
    int remainingWait();
    bool tick();
    
    Ability *selectedAbility;
    
    void setTile(GridTile* newTile, GridGraph* graph);
    GridTile* getTile();
    
    void setHP(double HP);
    void catchupDisplayHP();
    double getHP();
    void jumpToDest(GridTile* destTile);
    void activate(GridTile *location, GridGraph *graph, std::vector<Pawn *> pawns);
    
    void triggerPassives(Trigger t);
    
    CC_SYNTHESIZE(cocos2d::Sprite*, hero, Hero);
    CC_SYNTHESIZE(cocos2d::Sprite*, overlay, Overlay);
    
    void damage(Pawn *src, double amount, AttackType at);
    
};


#endif /* Pawn_hpp */
