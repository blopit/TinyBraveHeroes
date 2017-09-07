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

class Pawn : public cocos2d::Node {
    virtual bool init();
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override;
    Pawn(GridTile *tile): tile(tile){}
    
    GridTile *tile;
    
public:
    static Pawn* create(GridTile *tile);
    bool dragged = false;
    
    int MVE = 25;
    
    void setTile(GridTile* newTile, GridGraph* graph);
    GridTile* getTile();
    void jumpToDest(GridTile* destTile);
    
    CC_SYNTHESIZE(cocos2d::Sprite*, hero, Hero);
    
};


#endif /* Pawn_hpp */
