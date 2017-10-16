//
//  Tooltip.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-03.
//

#ifndef Tooltip_hpp
#define Tooltip_hpp

#include "cocos2d.h"

class Tooltip : public cocos2d::Node {
    virtual bool init() override;
    virtual void update(float dt) override;
    cocos2d::DrawNode *drawNode;
    float TTW;
    
    Tooltip(std::string name, std::string right, std::string description) : name(name), right(right), description(description), TTW(500), hidden(false) {};
    Tooltip(float width, std::string name, std::string right, std::string description) : name(name), right(right), description(description), TTW(width), hidden(false) {};
    
public:
    std::string name, right, description;
    static Tooltip* create(std::string name, std::string right, std::string description);
    
    CC_SYNTHESIZE(bool, hidden, Hidden);
};

#endif /* Tooltip_hpp */
