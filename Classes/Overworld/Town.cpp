//
//  Town.cpp
//  TinyBraveHeroes
//
//  Created by Shrenil Patel on 2017-10-28.
//

#include "Town.hpp"
#include "Utils.hpp"


#include <iostream>
#include <sstream>

USING_NS_CC;
using namespace std;

Building* Building::create(cocos2d::Sprite* image, cocos2d::Sprite* icon) {
    Building *pRet = new Building(image, icon);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool Building::init() {
    timer = CustomTimer::create(cycle, this);
    timer->setPosition(Vec2(0, -90));
    addChild(timer, 1);
    addChild(spriteImage, 0);
    
    occLayer = Layer::create();
    this->addChild(occLayer, 6);
    reloadOccupancy();
    
    this->schedule(schedule_selector(Building::step));
    return true;
}

void Building::step(float dt) {
    
}

void Building::addOccupant(CharacterPortrait * character) {
    if (characters.size() < maxCapacity()) {
        timer->activate();
    }
}

void Building::reloadOccupancy(bool bounceLast) {
    occLayer->removeAllChildren();
    auto mc = maxCapacity();
    auto cx = (-(mc - 1) * 32) / 2;
    for (auto i = 0; i < mc; i++) {
        string nm = characters.size() > i ? "occupied.png" : "occAvailable.png";
        auto spr = Sprite::createWithSpriteFrameName(nm);
        spr->setPosition(cx + i * 32, 96);
        
        if (bounceLast and i == characters.size() - 1) {
            spr->setScale(0);
            auto scaleTo = EaseBackOut::create(ScaleTo::create(0.3, 1.0));
            spr->runAction(scaleTo);
        }
        
        occLayer->addChild(spr);
    }
}

Mine::Mine() : Building(Sprite::createWithSpriteFrameName("buildings/mine.png"), Sprite::createWithSpriteFrameName("buildings/mine.png")) {
    cycle = 1;
    gold = 0;
    
    auto sprite = cocos2d::Sprite::createWithSpriteFrameName("goldProgressBar.png");
    progressBar = ProgressTimer::create(sprite);
    progressBar->setType(cocos2d::ProgressTimerType::BAR);
    progressBar->setMidpoint(Vec2(0, 0.5f));
    progressBar->setBarChangeRate(Vec2(1, 0));
    
    auto progressBarBk = cocos2d::Sprite::createWithSpriteFrameName("goldProgressBarBk.png");
    
    goldLabel = Label::createWithTTF("0g", "fonts/dpcomic.ttf", 18);
    goldLabel->setAnchorPoint(Vec2(0.5, 0.5));
    goldLabel->setTextColor(Color4B::WHITE);
    goldLabel->enableOutline(Color4B::BLACK, 3);
    
    timerLayer = Layer::create();
    timerLayer->setAnchorPoint(this->getPosition());
    timerLayer->setPosition(Vec2(0, -48));
    
    timerLayer->addChild(goldLabel, 2);
    timerLayer->addChild(progressBar, 1);
    timerLayer->addChild(progressBarBk, 0);
    this->addChild(timerLayer, 5);
    timerLayer->setScale(0);
}

float Mine::goldPerSec() {
    return 12;
}

float Mine::goldCap() {
    return 1000;
}

int Mine::maxCapacity() {
    return 4;
}

void Mine::process() {
    auto add = goldPerSec();
    
    gold = ((gold + add) <= goldCap() ? (gold + add) : goldCap());
    getTimer()->reset(cycle);
    
    stringstream ss;
    ss << int(gold) << "g";
    
    auto amount = ceil(100 * float(gold)/float(goldCap()));
    progressBar->setPercentage(amount);
    goldLabel->setString(ss.str());
 
}

void Mine::step(float dt) {
}

void Mine::addOccupant(CharacterPortrait * character) {
    if (characters.size() < maxCapacity()) {
        timer->activate();
        timer->setVisible(false);
        characters.push_back(character);
        
        if (timerLayer->getScale() == 0) {
            auto scale = EaseBackOut::create(ScaleTo::create(0.3, 1.0f));
            timerLayer->runAction(scale);
        }
        
        reloadOccupancy(true);
    }
}

//-----------------------------------------------

CharacterPortrait::CharacterPortrait(string filename) : filename(filename) {
    spriteImage = cocos2d::Sprite::createWithSpriteFrameName(filename);
    portraitPlaceholder = Sprite::createWithSpriteFrameName("portraits/placeholder.png");
    portraitPlaceholder->setVisible(false);
}

bool CharacterPortrait::init() {
    
    addChild(spriteImage);
    addChild(portraitPlaceholder);
    
    return true;
}

CharacterPortrait* CharacterPortrait::create(string filename) {
    CharacterPortrait *pRet = new CharacterPortrait(filename);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

void CharacterPortrait::select() {
    selected = true;
    spriteImage->setVisible(false);
    portraitPlaceholder->setVisible(true);
}

void CharacterPortrait::deselect() {
    selected = false;
    spriteImage->setVisible(true);
    portraitPlaceholder->setVisible(false);
}

//--------------------------------------------//

CustomTimer::CustomTimer(int ftime, Building* building) : startTime(time(0)), doneTime(time(0) + ftime), doneSteps(ftime * 60), building(building) {
    lastTime = 0;
    steps = 0;
    pct = 0;
    str = "0s";
}

void CustomTimer::reset(int ftime) {
    startTime = time(0);
    doneTime = (time(0) + ftime);
    doneSteps = (ftime * 60);
    lastTime = 0;
    steps = 0;
    pct = 0;
    str = "0s";
    done = false;
    progressBar->setPercentage(0.0f);
    this->runAction(EaseOut::create(ScaleTo::create(0.1f, 1.0f), 1.5f));
}

void CustomTimer::step(float dt) {
    if (!active) return;
    steps++;
    long current = (doneTime - (startTime + (time(0) - startTime) * spdMult) );
    if (current != lastTime) {
        steps = (time(0) - startTime) * 60 * spdMult;
        lastTime = current;
        auto t = boundToRange(0l, current, 3596400l);
        
        if (current < 0) {
            if (!done) {
                done = true;
                this->runAction(EaseIn::create(ScaleTo::create(0.1f, 0.0f, 1.0f), 1.5f));
                building->process();
            }
        }
        
        int d = int(t / 86400);
        int h = int(t / 3600) % 24;
        int m = int(t / 60) % 60;
        int s = int(t) % 60;
        
        stringstream ss;
        
        if (d > 0) {
            ss << d << "d ";
        }
        if (h > 0) {
            ss << h << "h ";
        }
        if (m > 0) {
            ss << m << "m ";
        }
        
        ss << s << "s";
        
        timeLabel->setString(ss.str());
        
        /*pct = (float(steps)/float(doneSteps));
        progressBar->runAction(EaseElasticOut::create(ProgressTo::create(0.5f, pct)));*/
        
    } /* current != lastTime */
    
    pct = (float(steps)/float(doneSteps))*100;
    progressBar->setPercentage(pct);
}

void CustomTimer::activate() {
    active = true;
    this->setVisible(true);
    reset(int(doneSteps/60));
}

bool CustomTimer::init() {
    auto sprite = cocos2d::Sprite::createWithSpriteFrameName("progressBar.png");
    progressBar = ProgressTimer::create(sprite);
    progressBar->setType(cocos2d::ProgressTimerType::BAR);
    progressBar->setMidpoint(Vec2(0, 0.5f));
    progressBar->setBarChangeRate(Vec2(1, 0));
    
    auto progressBarBk = cocos2d::Sprite::createWithSpriteFrameName("progressBarBk.png");
    
    timeLabel = Label::createWithTTF("0s", "fonts/dpcomic.ttf", 24);
    timeLabel->setAnchorPoint(Vec2(0.5, 0.5));
    timeLabel->setTextColor(Color4B::WHITE);
    timeLabel->enableOutline(Color4B::BLACK, 3);
    
    this->addChild(timeLabel, 2);
    this->addChild(progressBar, 1);
    this->addChild(progressBarBk, 0);
    
    this->schedule(schedule_selector(CustomTimer::step));
    
    this->setVisible(false);
    
    return true;
}

CustomTimer *CustomTimer::create(int time, Building* building) {
    CustomTimer *pRet = new CustomTimer(time, building);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

//----------------------------------------///////////////////////////////

Scene* TownScene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TownScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TownScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Director::getInstance()->setClearColor(Color4F::WHITE);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/misc.plist");
    selected = NULL;
    hologram = Sprite::createWithSpriteFrameName("nothing.png");
    /////////////////////////////
    // 3. add your codes below...
    
    /*auto timer = CustomTimer::create(3600);
    this->addChild(timer, 1);
    timer->setPosition(Vec2(origin.x + visibleSize.width/2,
                          origin.y + visibleSize.height/2));*/
    
    auto mine = Mine::create();
    this->addChild(mine, 1);
    mine->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height/2));
    buildings.push_back(mine);
    
    auto win_size = Director::getInstance()->getWinSize();
    auto scroll_size = Size(win_size.width - 32, 106);
    auto container_size = Size(boundToRange(608, int(characters.size() * 106), 640000), 106);
    scroll = ui::ScrollView::create();
    scroll->setContentSize(scroll_size);
    scroll->setInnerContainerSize(container_size);
    scroll->setBackGroundColorType(cocos2d::ui::Layout::BackGroundColorType::SOLID);
    scroll->setBackGroundColor(Color3B(200, 200, 200));
    scroll->setTouchEnabled(true);
    scroll->setScrollBarEnabled(false);
    scroll->setSwallowTouches(false);
    
    scroll->setPosition(Vec2(16,16));
    scroll->setDirection(ui::ScrollView::Direction::HORIZONTAL);
    
    auto chr = CharacterPortrait::create("portraits/Alee.png");
    characters.push_back(chr);
    
    //DEPTH
    auto ix = 53;
    for (auto c : characters) {
        c->setPosition(Vec2(ix, 53));
        c->homePosition = Vec2(ix, 53);
        scroll->addChild(chr);
        ix += 106;
    }
    
    this->addChild(hologram, 20);
    this->addChild(scroll, 0);
    
    // listen for touch events
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(TownScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(TownScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(TownScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(TownScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->schedule(schedule_selector(TownScene::step));
    
    return true;
}



void TownScene::step(float dt) {
    
}

void TownScene::deselect() {
    auto callbackComplete = CallFunc::create([=](){
        selected->deselect();
        selected = NULL;
        hologram->setVisible(false);
        detatched = false;
    });
    
    auto move = EaseOut::create(MoveTo::create(0.1, selected->homePosition), 1.5);
    auto seq = Sequence::create(move, callbackComplete, nullptr);
    hologram->runAction(seq);
}

bool TownScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
    
    for (auto c : characters) {
        auto v = c->getPosition();
        Rect rect = Rect(v.x - 50, v.y - 50, 100, 100);
        if (isTouching(touch, rect)) {
            selected = c;
            hologram->setScale(1.0f);
            hologram->setPosition(touchToPoint(touch));
            hologram->setTexture(c->getSpriteImage()->getTexture());
            hologram->setTextureRect(c->getSpriteImage()->getTextureRect());
            detatched = true;
            return true;
        }
    }
    if (selected != NULL) deselect();
    return false;
}

void TownScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
    auto p = touchToPoint(touch);
    if (!selected) return;
    
    if (p.distance(selected->getPosition()) > 50.0f or detatched) {
        selected->select();
        detatched = true;
        hologram->setVisible(true);
        hologram->setPosition(p.x, p.y);
    }
}

void TownScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {
    if (!selected) return;
    
    for (auto b : buildings) {
        auto p = b->getPosition();
        auto s = b->getSpriteImage()->getTextureRect();
        
        Rect rect1 = Rect(p.x - s.size.width/2, p.y - s.size.height/2, s.size.width, s.size.height);
        auto q = hologram->getPosition();
        Rect rect2 = Rect(q.x - 50, q.y - 50, 100, 100);
        
        if (rect1.intersectsRect(rect2)) {
            
            auto callbackComplete = CallFunc::create([=](){
                b->addOccupant(selected);
                selected->deselect();
                selected = NULL;
                hologram->setVisible(false);
                detatched = false;
            });
            
            auto scale = EaseBackIn::create(ScaleTo::create(0.1, 0));
            auto seq = Sequence::create(scale, callbackComplete, nullptr);
            hologram->runAction(seq);
            
            return;
        }
    }
    
    deselect();
}
