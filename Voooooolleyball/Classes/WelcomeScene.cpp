//
//  WelcomeScene.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#include "WelcomeScene.h"


USING_NS_CC;

Scene* WelcomeScene::welcomeScene = nullptr;
WelcomeButtonLayer* WelcomeScene::welcomeButtonLayer = nullptr;
WelcomeBackgroundLayer* WelcomeScene::welcomeBackgroundLayer = nullptr;

Scene* WelcomeScene::create() {
    Scene* welcomeScene = Scene::create();
    
    welcomeBackgroundLayer = WelcomeBackgroundLayer::create();
    welcomeScene->addChild(welcomeBackgroundLayer);
    
    welcomeButtonLayer = WelcomeButtonLayer::create();
    welcomeScene->addChild(welcomeButtonLayer);
    
    return welcomeScene;
}