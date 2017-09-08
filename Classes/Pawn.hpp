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

struct CharInfo {
    int HP, SPD, MVE;
    CharInfo(int HP, int SPD, int MVE) : HP(HP), SPD(SPD), MVE(MVE) {}
};

class Pawn : public cocos2d::Node {
    virtual bool init() override;
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override;
    Pawn(GridTile *tile, CharInfo info);
    GridTile *tile;
    cocos2d::DrawNode *drawNode;
    
    cocos2d::Label *waitLabel;
    
public:
    static Pawn* create(GridTile *tile, CharInfo info);
    CharInfo info;
    bool dragged = false;
    
    double waitTime;
    double waitSpeed();
    int remainingWait();
    
    void setTile(GridTile* newTile, GridGraph* graph);
    GridTile* getTile();
    void jumpToDest(GridTile* destTile);
    
    CC_SYNTHESIZE(cocos2d::Sprite*, hero, Hero);
    
};


#endif /* Pawn_hpp */
