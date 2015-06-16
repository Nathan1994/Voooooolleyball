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
#include "WelcomeScene.h"


USING_NS_CC;

static const int BALL_TAG = 0x00;
static const int PLAYER_TAG = 0x01;
static const int WALL_TAG = 0x11;
static const int GROUND_TAG = 0x10;


static bool isRight = false;
static bool isMove = false;
static bool isContactBall = false;

static Node *edgeNode = nullptr;

static float offsetScale = 0.87;


#pragma mark - Init Method


bool GamePlayerLayer::init(){



    return true;
}

void GamePlayerLayer::onEnter(){
    Layer::onEnter();
    configurePhysicsContactListener();
    configureTouchListener();
    
    configurePlayer();
    configureEnemy();
    configureEdge();
    configureObstacle();
    configureBall();
    configureButton();
    
    this->scheduleUpdate();

}

void GamePlayerLayer::update(float dt){
    if (isMove) {
        Vec2 position = player->getPosition();
        if (isRight) {
            player->setPosition(Vec2(position.x+7,position.y));
        }
        else{
            player->setPosition(Vec2(position.x-7,position.y));
        }
    }
}

#pragma mark - UI Method

void GamePlayerLayer::configureButton(){
    Size visibleSize = VisibleRect::getVisibleRect().size;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto restartButton = ui::Button::create("Game_Restart_Button.png");
    restartButton->setAnchorPoint(Vec2(1,1));
    Size buttonSize = restartButton->getCustomSize();
    restartButton->setScale(visibleSize.height/10/buttonSize.height);
    restartButton->setPosition(Vec2(visibleSize.width,visibleSize.height));
    restartButton->addClickEventListener(CC_CALLBACK_1(GamePlayerLayer::restartButtenTouchEvent, this));
    this->addChild(restartButton);
    
    auto homeButton = ui::Button::create("Game_Home_Button.png");
    homeButton->setAnchorPoint(Vec2(0,1));
    Size homeButtonSize = restartButton->getCustomSize();
    homeButton->setScale(visibleSize.height/10/homeButtonSize.height);
    homeButton->setPosition(Vec2(0,visibleSize.height));
    homeButton->addClickEventListener(CC_CALLBACK_1(GamePlayerLayer::homeButtenTouchEvent, this));
    this->addChild(homeButton);

}

void GamePlayerLayer::configurePhysicsContactListener(){
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GamePlayerLayer::onContactBegin, this);
    contactListener->onContactSeperate = CC_CALLBACK_1(GamePlayerLayer::onContactSeperate, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void GamePlayerLayer::configureTouchListener(){
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(GamePlayerLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GamePlayerLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GamePlayerLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
}

void GamePlayerLayer::configureObstacle(){
    auto obstacle = Node::create();
    obstacle->setAnchorPoint(Point(0.5,0));
    obstacle->setPosition(Point(VisibleRect::bottom().x,VisibleRect::bottom().y+ VisibleRect::getVisibleRect().size.height * (1-offsetScale)));
    obstacle->setPhysicsBody(PhysicsBody::createEdgeBox(Size(100,550)));
    
    this->addChild(obstacle);
    
}

void GamePlayerLayer::configureBall(){
    if (ball) {
        ball->removeFromParent();
    }
    
    ball = Sprite::create("Game_Ball.png");;
    float ballScale = (VisibleRect::getVisibleRect().size.height/6)/ball->getTextureRect().size.height;
    ball->setScale(ballScale);
    auto body = PhysicsBody::createCircle(VisibleRect::getVisibleRect().size.height/12);
    body->setContactTestBitmask(1);
    body->setTag(BALL_TAG);
    ball->setPhysicsBody(body);
    ball->setPosition(Point(VisibleRect::getVisibleRect().size.width/5,VisibleRect::getVisibleRect().size.height - VisibleRect::getVisibleRect().size.height/6 ));
    this->addChild(ball);


}

void GamePlayerLayer::configurePlayer(){
    if (player) {
        player->removeFromParent();
    }
    player = GamePlayerSprite::create("Game_Player.png");
    player->setPosition(Point(VisibleRect::getVisibleRect().size.width/5,VisibleRect::getVisibleRect().size.height*(1-offsetScale)+1));
    this->addChild(player);


}

void GamePlayerLayer::configureEnemy(){
    if (enemy) {
        enemy->removeFromParent();
    }
    enemy = GamePlayerSprite::create("Game_Enemy.png");
    enemy->setPosition(Point(4 * VisibleRect::getVisibleRect().size.width/5,VisibleRect::getVisibleRect().size.height*(1-offsetScale)+1));
    this->addChild(enemy);


}

void GamePlayerLayer::configureEdge(){

    
    auto wall = Node::create();
    wall->setPosition(Point(VisibleRect::center().x,VisibleRect::center().y + VisibleRect::getVisibleRect().size.height * (1-offsetScale)/2));
    auto body = PhysicsBody::createEdgeBox(Size(VisibleRect::getVisibleRect().size.width,VisibleRect::getVisibleRect().size.height * offsetScale), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    body->setContactTestBitmask(1);
    body->setTag(WALL_TAG);
    wall->setPhysicsBody(body);
    this->addChild(wall);
    
    auto ground = Node::create();
    ground->setPosition(Point(VisibleRect::center().x, VisibleRect::getVisibleRect().size.height * (1-offsetScale)));
    auto groundBody = PhysicsBody::createEdgeBox(Size(VisibleRect::getVisibleRect().size.width,2), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    groundBody->setContactTestBitmask(1);
    groundBody->setTag(GROUND_TAG);
    ground->setPhysicsBody(groundBody);
    this->addChild(ground);
    
    
    
}

#pragma mark - Action Method

void GamePlayerLayer::hitBall(){
    
    if ((VisibleRect::getVisibleRect().size.width/2 - player->getPosition().x > 0)) {
        ball->getPhysicsBody()->setVelocity(Vec2(1000,-1000));
    }
    else{
        ball->getPhysicsBody()->setVelocity(Vec2(-1000,-1000));
    }
}

void GamePlayerLayer::restart(){
    configurePlayer();
    configureEnemy();
    configureBall();
}

#pragma mark - Listener Call Back

void GamePlayerLayer::restartButtenTouchEvent(Ref* pSender){
    restart();
}

void GamePlayerLayer::homeButtenTouchEvent(Ref* pSender){
    Scene* welcomeScene = TransitionFade::create(1.0f, WelcomeScene::create());
    Director::getInstance()->replaceScene(welcomeScene);
}

bool GamePlayerLayer::onContactBegin(PhysicsContact& contact){
    CCLOG("Contact Begin...");
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    
    if (a->getTag() == GROUND_TAG || b->getTag() == GROUND_TAG) {
        if (a->getTag() == PLAYER_TAG || b->getTag() == PLAYER_TAG) {
            player->isJump = false;
            float playerRotation = player->getRotation();
            if (fabsf(playerRotation) > 5 && !player->isFall) {
                player->standup();
            }
        }
    }
    
    if (a->getTag() == BALL_TAG || b->getTag() == BALL_TAG) {
        if (a->getTag() == PLAYER_TAG || b->getTag() == PLAYER_TAG) {
            
            isContactBall = true;
            
            int boost = 700;
            Vec2 ballVelocity = ball->getPhysicsBody()->getVelocity();
            float sqrt = sqrtf(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
            ball->getPhysicsBody()->setVelocity(Vec2(-ballVelocity.x/sqrt * boost,-ballVelocity.y/sqrt * boost));
        }
    }
    
    
    if (a->getTag() == BALL_TAG || b->getTag() == BALL_TAG) {
        if (a->getTag() == GROUND_TAG || b->getTag() == GROUND_TAG) {
            this->runAction(Sequence::create(DelayTime::create(1),CallFuncN::create(CC_CALLBACK_0(GamePlayerLayer::restart,this)), NULL));
        }
    }

    return true;
}

void GamePlayerLayer::onContactSeperate(PhysicsContact& contact){
    CCLOG("Contact Seperate...");
    PhysicsBody* a = contact.getShapeA()->getBody();
    PhysicsBody* b = contact.getShapeB()->getBody();
    
    if (a->getTag() == BALL_TAG || b->getTag() == BALL_TAG) {
        if (a->getTag() == PLAYER_TAG || b->getTag() == PLAYER_TAG) {
            isContactBall = false;
            
        }
    }
    
}

bool GamePlayerLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    CCLOG("Touch Begin...");
    
    
    return true;
}

void GamePlayerLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    float deltaX,deltaY;
    deltaX = touch->getLocation().x - touch->getPreviousLocation().x;
    deltaY = touch->getLocation().y - touch->getPreviousLocation().y;
    if (!player->isJump) {
        isMove = true;
        if(deltaX > 0){
            isRight = true;
        }
        else{
            isRight = false;
        }
    }
    
    if (deltaY > 30) {
        player->jump();
    }
    
    if (deltaY < -30) {
        if (player->isJump) {
            if (isContactBall) {
                hitBall();
            }
        }
        else{
            player->fall();
        }
    }

}

void GamePlayerLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    CCLOG("Touch End...");
    
    isMove = false;
    
}