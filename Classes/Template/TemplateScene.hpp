//
//  TemplateScene.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-22.
//

#ifndef TemplateScene_hpp
#define TemplateScene_hpp

class TemplateScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TemplateScene);
    
    void step(float dt);
    
private:
};


#endif /* TemplateScene_hpp */
