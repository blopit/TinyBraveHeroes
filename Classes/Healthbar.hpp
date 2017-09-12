//
//  Healthbar.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-08.
//
//

#ifndef Healthbar_hpp
#define Healthbar_hpp

#import "cocos2d.h"

class Healthbar : public cocos2d::Node {
    virtual bool init() override;
    Healthbar(int hp);
    cocos2d::DrawNode *drawNode;
    cocos2d::Label *hpLabel;
    virtual void update(float dt) override;
    
public:
    double maxHP, HP, simHP, dispHP;
    static Healthbar* create(int hp);
    virtual void draw(cocos2d::Renderer* renderer, const cocos2d::Mat4& transform, uint32_t transformFlags) override;
};

#endif /* Healthbar_hpp */
