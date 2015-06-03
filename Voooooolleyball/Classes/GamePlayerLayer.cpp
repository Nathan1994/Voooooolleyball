//
//  GamePlayerLayer.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#include "GamePlayerLayer.h"
USING_NS_CC;

#pragma mark - Init Method


bool GamePlayerLayer::init(){
    configureTouchListener();
    configurePlayer();
    return true;
}

#pragma mark - UI Method
void GamePlayerLayer::configureTouchListener(){
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GamePlayerLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GamePlayerLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GamePlayerLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void GamePlayerLayer::configurePlayer(){
    Size winSize = Director::getInstance()->getWinSize();
    player = Sprite::create("Game_Player.png");
    player->setPosition(winSize.width/2,0);
    this->addChild(player);
}



#pragma mark - Touch Listener Call Back
bool GamePlayerLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    beginTouchLocation = touch->getLocation();
    return true;
}
void GamePlayerLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    CCLOG("Begin Touch:%f,%f",touch->getLocation().x,touch->getLocation().y);
    CCLOG("Previous Touch:%f,%f",touch->getPreviousLocation().x,touch->getPreviousLocation().y);

    
    float deltaX,deltaY;
    deltaX = touch->getLocation().x - touch->getPreviousLocation().x;
    deltaY = touch->getLocation().y - touch->getPreviousLocation().y;
    
#warning Control move left and right only now.
    

    Point playerLocation = player->getPosition();
    player->setPositionX(playerLocation.x+deltaX);
}
void GamePlayerLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    //TODO: Stop Move
}


