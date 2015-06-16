//
//  GameBackgroundLayer.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/14/15.
//
//

#include "GameBackgroundLayer.h"
#include "VisibleRect.h"
USING_NS_CC;

void GameBackgroundLayer::onEnter(){
    Size visibleSize = VisibleRect::getVisibleRect().size;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto sprite = Sprite::create("Game_Background.png");
    auto background = Sprite::create("Game_Background_Tint.png");
    Size spriteSize = sprite->getTextureRect().size;
    Size backgroundSize = background->getTextureRect().size;
    sprite->setScale(visibleSize.width/spriteSize.width, visibleSize.height/spriteSize.height);
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    background->setScale(visibleSize.width/backgroundSize.width, visibleSize.height/backgroundSize.height);
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background);
    this->addChild(sprite);
}