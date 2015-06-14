//
//  GamePlayerLayer.cpp
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#include "GamePlayerLayer.h"
#include "ui/CocosGUI.h"
#include "VisibleRect.h"

USING_NS_CC;

static const int DRAG_BODYS_TAG = 0x80;

static bool isMove = false;
static bool isRight = false;
static bool isJump = false;
static Node *edgeNode = nullptr;

#pragma mark - Init Method


bool GamePlayerLayer::init(){



    return true;
}

void GamePlayerLayer::onEnter(){
    Layer::onEnter();
    configurePhysicsContactListener();
    configureTouchListener();
    
    configurePlayer();
    configureEdge();
    
    this->scheduleUpdate();

}

void GamePlayerLayer::update(float dt){
    if (isMove) {
        Vec2 position = player->getPosition();
        if (isRight) {
            player->setPosition(Vec2(position.x+1,position.y));
        }
        else{
            player->setPosition(Vec2(position.x-1,position.y));
        }
    }
}

#pragma mark - UI Method
void GamePlayerLayer::configurePhysicsContactListener(){
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GamePlayerLayer::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GamePlayerLayer::configureTouchListener(){
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GamePlayerLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GamePlayerLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GamePlayerLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void GamePlayerLayer::configurePlayer(){

    player = Sprite::create("Game_Player.png");
    float playerScale = (VisibleRect::getVisibleRect().size.height/3)/player->getTextureRect().size.height;
    player->setScale(playerScale);
    player->setTag(100);
    auto body = PhysicsBody::createBox(Size(player->getTextureRect().size.width * playerScale, player->getTextureRect().size.height * playerScale));
    body->setContactTestBitmask(1);
    player->setPhysicsBody(body);
    player->getPhysicsBody()->setTag(DRAG_BODYS_TAG);
    player->setAnchorPoint(Point(0.5,0));
    player->setPosition(VisibleRect::center());
    this->addChild(player);
}

void GamePlayerLayer::configureEdge(){
    auto wall = Node::create();
    wall->setPosition(VisibleRect::center());
    auto body = PhysicsBody::createEdgeBox(VisibleRect::getVisibleRect().size, PHYSICSBODY_MATERIAL_DEFAULT, 3);
//    body->setCategoryBitmask(0);
//    body->setCollisionBitmask(1);
    body->setContactTestBitmask(1);
    body->getShape(0)->setRestitution(0);
    wall->setPhysicsBody(body);
    this->addChild(wall);
    
}

#pragma mark - Action Method
void GamePlayerLayer::playerMoveLeft(){
    auto moveBy = MoveBy::create(1, Vec2(1, 0));
    player->runAction(moveBy);
}

void GamePlayerLayer::playerMoveRight(){
    auto moveBy = MoveBy::create(1,Vec2(10,0));
    player->runAction(moveBy);
}

#pragma mark - Listener Call Back
bool GamePlayerLayer::onContactBegin(PhysicsContact& contact){
    CCLOG("Contact Begin...");
//    PhysicsBody* a = contact.getShapeA()->getBody();
//    PhysicsBody* b = contact.getShapeB()->getBody();
    isJump = false;
    
    
    return true;
}
bool GamePlayerLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    CCLOG("Touch Begin...");
    return true;
}


void GamePlayerLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    float deltaX,deltaY;
    deltaX = touch->getLocation().x - touch->getPreviousLocation().x;
    deltaY = touch->getLocation().y - touch->getPreviousLocation().y;
    if (fabsf(deltaX) > 30) {
        isMove = true;
        if(deltaX > 0){
            isRight = true;
        }
        else{
            isRight = false;
        }
    }
    
    if (fabsf(deltaY) > 30) {
        if (!isJump) {
            player->getPhysicsBody()->setVelocity(Vec2(0,250.0f));
            isJump = true;
        }
    }

}
void GamePlayerLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    CCLOG("Touch End...");
    isMove = false;
    
}




