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
    
    std::vector<GridTile *> path;
    
    GridTile *destTile;
    GridTile *tile;
    
    cocos2d::CustomCommand _drawLines;
    void onDrawPrimitives(const cocos2d::Mat4 &transform, uint32_t flags);
    
public:
    static Pawn* create(GridTile *tile);
    
    void setTile(GridTile* newTile, GridGraph* graph);
    GridTile* getTile();
    void setDestTile(GridTile* newTile, GridGraph* graph);
    GridTile* getDestTile();
    void jumpToDest();
    
    CC_SYNTHESIZE(cocos2d::Sprite*, hero, Hero);
    CC_SYNTHESIZE(cocos2d::Sprite*, marker, Marker);
    
};


#endif /* Pawn_hpp */
