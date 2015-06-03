//
//  GamePlayerLayer.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#include "GamePlayerLayer.h"
USING_NS_CC;

bool GamePlayerLayer::init(){
    configureTouchListener();
    return true;
}

#pragma mark - UI Configure
void GamePlayerLayer::configureTouchListener(){
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GamePlayerLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GamePlayerLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GamePlayerLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}



#pragma mark - Touch Listener Call Back
bool GamePlayerLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
    return true;
}
void GamePlayerLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    CCLOG("Touch Location:%f,%f",touch->getLocation().x,touch->getLocation().y);
}
void GamePlayerLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    
}


