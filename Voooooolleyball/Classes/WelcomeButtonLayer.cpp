//
//  WelcomeButtonLayer.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#include "WelcomeButtonLayer.h"
#include "GameScene.h"
#include "VisibleRect.h"

USING_NS_CC;

bool WelcomeButtonLayer::init() {
    Size visibleSize = VisibleRect::getVisibleRect().size;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    MenuItemSprite* startGameButtonItemSprite = MenuItemSprite::create(Sprite::create("Welcome_Start_Button.png"), Sprite::create("Welcome_Start_Button.png"), CC_CALLBACK_1(WelcomeButtonLayer::startGameButtonCallBack, this));
    Size startButtonSize = startGameButtonItemSprite->rect().size;
    startGameButtonItemSprite->setScale(visibleSize.height/6/startButtonSize.height);
    
    MenuItemSprite* helpButtonItemSprite = MenuItemSprite::create(Sprite::create("Welcome_Help_Button.png"), Sprite::create("Welcome_Help_Button.png"), CC_CALLBACK_1(WelcomeButtonLayer::helpButtonCallBack, this));
    Size helpButtonSize = helpButtonItemSprite->rect().size;
    helpButtonItemSprite->setScale(visibleSize.height/6/helpButtonSize.height);
    
    Menu* startGameButton = Menu::create(startGameButtonItemSprite, helpButtonItemSprite, nullptr);
    startGameButton->setAnchorPoint(Point(0.0f, 1.0f));
    startGameButton->setPosition(Director::getInstance()->getWinSize().width/2, 200);
    startGameButton->alignItemsVerticallyWithPadding(40);
    this->addChild(startGameButton);
    return true;
}

void WelcomeButtonLayer::startGameButtonCallBack(Ref* pSender) {
    CCLOG("Start Button Did Select...");
    Scene* gameScene = TransitionFade::create(2.0f, GameScene::create());
    Director::getInstance()->replaceScene(gameScene);
}

void WelcomeButtonLayer::helpButtonCallBack(Ref* pSender){
    CCLOG("Help Button Did Select...");
    
}
