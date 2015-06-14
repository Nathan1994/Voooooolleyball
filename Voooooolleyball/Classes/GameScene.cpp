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
GamePlayerLayer* GameScene::playerLayer = nullptr;
GameBackgroundLayer* GameScene::backgroundLayer = nullptr;

Scene* GameScene::create()
{
    gameScene = Scene::createWithPhysics();
    gameScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    gameScene->getPhysicsWorld()->setGravity(Vec2(0,-980.0f));
    
    backgroundLayer = GameBackgroundLayer::create();
    gameScene->addChild(backgroundLayer);
    
    playerLayer = GamePlayerLayer::create();
    playerLayer->setPhyWorld(gameScene->getPhysicsWorld());
    gameScene->addChild(playerLayer);
    
    
    return gameScene;
}

