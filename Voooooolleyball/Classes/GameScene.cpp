//
//  GameScene.cpp
//  Voooooolleyball
//
//  Created by Nathan on 5/25/15.
//
//

#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::gameScene = nullptr;

Scene* GameScene::create()
{
    gameScene = Scene::create();
    
    
    return gameScene;
}

