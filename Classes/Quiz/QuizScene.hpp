//
//  QuizScene.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-22.
//

#ifndef QuizScene_hpp
#define QuizScene_hpp

class QuizButton {
    std::string description;
    float fire, water, earth, air;
    QuizButton(std::string description, float fire, float water, float earth, float air) : description(description), fire(fire), water(water), earth(earth), air(air) {}
};

class QuizScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene(int s);
    static QuizScene* create(int s);
    QuizScene(int s);
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    void step(float dt);
    
private:
    int s;
};


#endif /* QuizScene_hpp */
