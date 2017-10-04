//
//  Tooltip.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-03.
//

#ifndef Tooltip_hpp
#define Tooltip_hpp

#include "cocos2d.h"

#define TTW 400
#define TTH 200

class Tooltip : public cocos2d::Node {
    virtual bool init() override;
    std::string name, right, description;
    cocos2d::DrawNode *drawNode;
    Tooltip(std::string name, std::string right, std::string description) : name(name), right(right), description(description) {};
    //cocos2d::Label *hpLabel;
    
public:
    
    static Tooltip* create(std::string name, std::string right, std::string description);
    //virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override;
};

#endif /* Tooltip_hpp */
