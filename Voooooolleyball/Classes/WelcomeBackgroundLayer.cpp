//
//  WelcomeBackgroundLayer.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#include "WelcomeBackgroundLayer.h"
#include "VisibleRect.h"

USING_NS_CC;

void WelcomeBackgroundLayer::onEnter(){
    Size visibleSize = VisibleRect::getVisibleRect().size;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("Welcome_Background.png");

    Size backgroundSize = background->getTextureRect().size;
    background->setScale(visibleSize.width/backgroundSize.width, visibleSize.height/backgroundSize.height);
    background->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(background);
}
