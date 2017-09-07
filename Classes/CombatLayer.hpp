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

USING_NS_CC;

class CombatLayer : public cocos2d::Layer
{
private:
    
    Pawn* selected;
    std::vector<Pawn *> pawns;
    GridGraph *graph;
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init() override;
    
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
