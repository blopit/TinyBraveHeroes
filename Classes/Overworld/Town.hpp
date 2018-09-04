//
//  Town.hpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-28.
//

#ifndef Town_hpp
#define Town_hpp

#include <cocos-ext.h>
#include <ui/CocosGUI.h>
#include <time.h>

class CharacterPortrait;
class CustomTimer;

class Building : public cocos2d::Node {
    
protected:
    Building(cocos2d::Sprite* image, cocos2d::Sprite* icon) : spriteImage(image), icon(icon) {};
    virtual bool init() override;
    int cycle = 0;
    virtual void step(float dt);
    
public:
    static Building* create(cocos2d::Sprite* image, cocos2d::Sprite* icon);
    virtual void process() {};
    virtual void getCapacity() {};
    virtual void reloadOccupancy(bool bounceLast = false);
    virtual int maxCapacity() { return 0; };
    virtual void addOccupant(CharacterPortrait* character);
    int level = 1;
    
    std::vector<CharacterPortrait *> characters;
    CC_SYNTHESIZE(cocos2d::Sprite*, spriteImage, SpriteImage);
    CC_SYNTHESIZE(cocos2d::Sprite*, icon, Icon);
    CC_SYNTHESIZE(CustomTimer*, timer, Timer);
    CC_SYNTHESIZE(cocos2d::Layer*, occLayer, OccLayer);
};

class Mine : public Building {
    float gold;
    Mine();
    void step(float dt) override;
public:
    void addOccupant(CharacterPortrait * character) override;
    int maxCapacity() override;
    float goldCap();
    float goldPerSec();
    void process() override;
    CREATE_FUNC(Mine);
    CC_SYNTHESIZE(cocos2d::Layer*, timerLayer, TimerLayer);
    CC_SYNTHESIZE(cocos2d::Label*, goldLabel, GoldLabel);
    CC_SYNTHESIZE(cocos2d::ProgressTimer* , progressBar, ProgressBar);
};

class CharacterPortrait : public cocos2d::Node {
    std::string filename;
    bool selected = false;
    cocos2d::Sprite* portraitPlaceholder;
    
    virtual bool init() override;
    CharacterPortrait(std::string filename);
    
public:
    cocos2d::Vec2 homePosition;
    
    void select();
    void deselect();
    static CharacterPortrait* create(std::string filename);
    CC_SYNTHESIZE(cocos2d::Sprite*, spriteImage, SpriteImage);
};

class CustomTimer : public cocos2d::Node {
    clock_t doneTime, startTime;
    long doneSteps;
    float pct;
    long lastTime, steps;
    CustomTimer(int time);
    void step(float dt);
    bool done = false;
    bool active = false;
    std::string str;
    long spdMult = 1;
    virtual bool init() override;
    CustomTimer(int ftime, Building* building);
public:
    static CustomTimer* create(int time, Building* building);
    void reset(int time);
    void activate();
    
    CC_SYNTHESIZE(cocos2d::Label*, timeLabel, TimeLabel);
    CC_SYNTHESIZE(cocos2d::ProgressTimer* , progressBar, ProgressBar);
    CC_SYNTHESIZE(Building* , building, Building);
};

class Account {
public:
    CC_SYNTHESIZE(long, gold, Gold);
    CC_SYNTHESIZE(long, keys, Keys);
};

class TownScene : public cocos2d::Layer {
    Account* account;
    std::vector<CharacterPortrait *> characters;
    std::vector<Building *> buildings;
    cocos2d::ui::ScrollView* scroll;
    CharacterPortrait* selected;
    bool detatched = false;
    
    void deselect();
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init() override;
    
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) override;
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) override;
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) override;
    CC_SYNTHESIZE(cocos2d::Sprite*, hologram, Hologram);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TownScene);
    
    void step(float dt);
};

#endif /* Town_hpp */
