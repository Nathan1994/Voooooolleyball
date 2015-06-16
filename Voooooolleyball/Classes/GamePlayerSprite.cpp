//
//  GamePlayerSprite.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/16/15.
//
//

#include "GamePlayerSprite.h"
#include "VisibleRect.h"

USING_NS_CC;

static float offsetScale = 0.87;
static const int PLAYER_TAG = 0x01;




GamePlayerSprite* GamePlayerSprite::create(){
    
    
    auto player = (GamePlayerSprite *)Sprite::create("Game_Player.png");
    float playerScale = (VisibleRect::getVisibleRect().size.height/3)/player->getTextureRect().size.height;
    player->setScale(playerScale);
    player->setAnchorPoint(Point(0.5,0));
    
    auto body = PhysicsBody::createBox(Size(player->getTextureRect().size.width * playerScale, player->getTextureRect().size.height * playerScale));
    
    //    auto body = PhysicsBody::create();
    //    auto circleShape = PhysicsShapeCircle::create(10);
    //    body->addShape(circleShape);
    //    auto boxShape = PhysicsShapeBox::create(Size(10,10));
    //    body->addShape(boxShape);
    
    body->setContactTestBitmask(1);
    player->setPhysicsBody(body);
    player->getPhysicsBody()->setTag(PLAYER_TAG);
    
    player->setPosition(Point(VisibleRect::getVisibleRect().size.width/4,VisibleRect::getVisibleRect().size.height*(1-offsetScale)+1));
    
    player->isJump = false;
    
    return player;

}

void GamePlayerSprite::jump(){
    if (!isJump) {
        this->getPhysicsBody()->setVelocity(Vec2(0,700.0f));
        isJump = true;
    }
}

void GamePlayerSprite::fall(){
    auto fallAction = RotateTo::create( 0.5, 90);
    auto backAction = RotateTo::create( 0.5, 0);
    this->isFall = true;
        
    this->runAction(Sequence::create(fallAction,DelayTime::create(1),backAction,CallFuncN::create(CC_CALLBACK_0(GamePlayerSprite::fallDidFinished,this)), NULL));
}

void GamePlayerSprite::standup(){
    auto standAcion = RotateTo::create( 0.25, 0);
    this->runAction(standAcion);
}

void GamePlayerSprite::fallDidFinished(){
    this->isFall = false;
}

void GamePlayerSprite::update(float dt){

    
}