//
//  WelcomeButtonLayer.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#include "WelcomeButtonLayer.h"
#include "GameScene.h"

USING_NS_CC;

bool WelcomeButtonLayer::init() {
    MenuItemSprite* startGameButtonItemSprite = MenuItemSprite::create(Sprite::create("Welcome_Start_Game_Button.png"), Sprite::create("Welcome_Start_Game_Button.png"), CC_CALLBACK_1(WelcomeButtonLayer::startGameButtonCallBack, this));
    Menu* startGameButton = Menu::create(startGameButtonItemSprite, nullptr);
    startGameButton->setAnchorPoint(Point(0.0f, 1.0f));
    startGameButton->setPosition(Director::getInstance()->getWinSize().width/2, 200);
    this->addChild(startGameButton);
    return true;
}

void WelcomeButtonLayer::startGameButtonCallBack(Ref* pSender) {
    CCLOG("Start Button Did Select...");
    Scene* gameScene = TransitionFade::create(2.0f, GameScene::create());
    Director::getInstance()->replaceScene(gameScene);
}
