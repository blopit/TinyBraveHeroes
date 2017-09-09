//
//  CombatLayer.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-05.
//
//

#ifndef CombatLayer_hpp
#define CombatLayer_hpp

#include "cocos2d.h"
#include "GridGraph.hpp"
#include "Pawn.hpp"
#include "Dijkstra.hpp"

USING_NS_CC;

class CombatLayer : public cocos2d::Layer
{
private:
    
    Pawn* current;
    bool dragging = false;
    
    std::vector<Pawn *> pawns;
    GridGraph *graph;
    std::vector<GridTile *> path;
    std::vector<GridTile *> viableMoves;
    bool viableMovesTable[COLUMNS][ROWS] = {
        {false,false,false,false,false,false,false,false},
        {false,false,false,false,false,false,false,false},
        {false,false,false,false,false,false,false,false},
        {false,false,false,false,false,false,false,false},
        {false,false,false,false,false,false,false,false},
        {false,false,false,false,false,false,false,false}
    };
    
    std::vector<GridTile *> telegraphed;
    GridTile *destTile;
    DrawNode *drawNode;
    DrawNode *drawNodeAdd;
    DrawNode *drawNodeBorder;
    DistData distData;
    
    void generatePaths(GridTile * dest);
    void generateViable();
    
public:
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    virtual void update(float dt);
    
    Point touchToPoint(Touch* touch);
    bool isTouchingSprite(Touch* touch, Pawn *pawn);
    
    bool onTouchBegan(Touch* touch, Event* event) override;
    void onTouchMoved(Touch* touch, Event* event) override;
    void onTouchEnded(Touch* touch, Event* event) override;
    
    Vec2 getClosestTile(Vec2 p);
    GridTile *getTileAt(Vec2 p);
    
    // implement the "static create()" method manually
    CREATE_FUNC(CombatLayer);
};

#endif /* CombatLayer_hpp */
