//
//  AnimationBlock.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-09-13.
//
//

#ifndef AnimationBlock_hpp
#define AnimationBlock_hpp

#include "cocos2d.h"

enum Command {
    MOVE, SHAKE
};

class AnimationBlock: cocos2d::Node {
public:
    virtual bool init() override;
};

#endif /* AnimationBlock_hpp */
