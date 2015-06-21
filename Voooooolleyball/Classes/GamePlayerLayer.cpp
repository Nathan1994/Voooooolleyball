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

static const int BALL_TAG = 0x000;
static const int PLAYER_TAG = 0x001;
static const int WALL_TAG = 0x011;
static const int GROUND_TAG = 0x010;
static const int ENEMY_TAG = 0x100;

static bool isRight = false;
static bool isMove = false;
static bool isContactBall = false;

static bool isEnemyRight = false;
static bool isEnemyMove = false;
static bool isEnemyContactBall = false;

static float offsetScale = 0.87;

static int leftWins = 0;
static int rightWins = 0;

Label *leftWinLabel = nullptr;
Label *rightWinLabel = nullptr;

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
    configureWinCountLabel();
    
    this->scheduleUpdate();
    
    showReady();
}

void GamePlayerLayer::update(float dt){
    updateEnemy();
    
    
    if (isMove) {
        Vec2 position = player->getPosition();
        if (isRight) {
            player->setPosition(Vec2(position.x+7,position.y));
        }
        else{
            player->setPosition(Vec2(position.x-7,position.y));
        }
    }
    
    if(isEnemyMove){
        Vec2 position = enemy->getPosition();
        if (isEnemyRight) {
            enemy->setPosition(Vec2(position.x+7,position.y));
        }
        else{
            enemy->setPosition(Vec2(position.x-7,position.y));
        }
    }
    
}

#pragma mark - UI Method

void GamePlayerLayer::configureWinCountLabel(){
    leftWinLabel = Label::createWithSystemFont("Score: 0", "Arial", 40);
    leftWinLabel->setAnchorPoint(Vec2(0,1));
    leftWinLabel->setColor(Color3B::BLACK);
    leftWinLabel->setPosition(Point(VisibleRect::leftTop().x+20,VisibleRect::leftTop().y-20));
    this->addChild(leftWinLabel);
    
    rightWinLabel = Label::createWithSystemFont("Score: 0", "Arial", 40);
    rightWinLabel->setAnchorPoint(Vec2(1,1));
    rightWinLabel->setColor(Color3B::BLACK);
    rightWinLabel->setPosition(Point(VisibleRect::rightTop().x-20,VisibleRect::rightTop().y-20));
    this->addChild(rightWinLabel);
}

void GamePlayerLayer::configureButton(){
    Size visibleSize = VisibleRect::getVisibleRect().size;
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto restartButton = ui::Button::create("Game_Restart_Button.png");
    restartButton->setAnchorPoint(Vec2(1,1));
    Size buttonSize = restartButton->getCustomSize();
    restartButton->setScale(visibleSize.height/10/buttonSize.height);
    restartButton->setPosition(Point(VisibleRect::top().x+80,VisibleRect::top().y-5));
    restartButton->addClickEventListener(CC_CALLBACK_1(GamePlayerLayer::restartButtenTouchEvent, this));
    this->addChild(restartButton);
    
    auto homeButton = ui::Button::create("Game_Home_Button.png");
    homeButton->setAnchorPoint(Vec2(0,1));
    Size homeButtonSize = restartButton->getCustomSize();
    homeButton->setScale(visibleSize.height/10/homeButtonSize.height);
    homeButton->setPosition(Point(VisibleRect::top().x-80,VisibleRect::top().y-5));
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
    obstacle->setPhysicsBody(PhysicsBody::createEdgeBox(Size(100,500)));
    
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
    body->setGravityEnable(false);
    ball->setPhysicsBody(body);
//    ball->setPosition(Point(4*VisibleRect::getVisibleRect().size.width/5,VisibleRect::getVisibleRect().size.height - VisibleRect::getVisibleRect().size.height/6 ));
    ball->setPosition(Point(VisibleRect::getVisibleRect().size.width/5,VisibleRect::getVisibleRect().size.height - VisibleRect::getVisibleRect().size.height/6 ));

    this->addChild(ball);


}

void GamePlayerLayer::configurePlayer(){
    if (player) {
        player->removeFromParent();
    }
    player = GamePlayerSprite::create("Game_Player.png");
//    player->setPosition(Point(VisibleRect::getVisibleRect().size.width/5,VisibleRect::getVisibleRect().size.height*(1-offsetScale)+1));
    player->getPhysicsBody()->setTag(PLAYER_TAG);
    player->setPosition(Point(VisibleRect::getVisibleRect().size.width/5,VisibleRect::center().y));

    this->addChild(player);


}

void GamePlayerLayer::configureEnemy(){
    if (enemy) {
        enemy->removeFromParent();
    }
    enemy = GamePlayerSprite::create("Game_Enemy.png");
    enemy->getPhysicsBody()->setTag(ENEMY_TAG);
    enemy->setPosition(Point(4 * VisibleRect::getVisibleRect().size.width/5,VisibleRect::center().y));
    this->addChild(enemy);

}

void GamePlayerLayer::configureEdge(){

    
    auto wall = Node::create();
    wall->setPosition(Point(VisibleRect::center().x,VisibleRect::center().y + VisibleRect::getVisibleRect().size.height * (1-offsetScale)/2));
    auto body = PhysicsBody::createEdgeBox(Size(VisibleRect::getVisibleRect().size.width,VisibleRect::getVisibleRect().size.height * offsetScale), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    body->setContactTestBitmask(1);
    body->setTag(WALL_TAG);
    body->getShape(0)->setRestitution(0);
    wall->setPhysicsBody(body);
    this->addChild(wall);
    
    auto ground = Node::create();
    ground->setPosition(Point(VisibleRect::center().x, VisibleRect::getVisibleRect().size.height * (1-offsetScale)));
    auto groundBody = PhysicsBody::createEdgeBox(Size(VisibleRect::getVisibleRect().size.width,2), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    groundBody->setContactTestBitmask(1);
    groundBody->setTag(GROUND_TAG);
    groundBody->getShape(0)->setRestitution(0);
    ground->setPhysicsBody(groundBody);
    this->addChild(ground);
    
    
    
}

#pragma mark - Action Method

void GamePlayerLayer::hitBall(){
    
    if ((VisibleRect::getVisibleRect().size.width/2 - player->getPosition().x > 0)) {
        ball->getPhysicsBody()->setVelocity(Vec2(1000,-300));
    }
    else{
        ball->getPhysicsBody()->setVelocity(Vec2(-1000,300));
    }
}

void GamePlayerLayer::restart(){
    configurePlayer();
    configureEnemy();
    configureBall();
    updateWinCount();
    showReady();
}

void GamePlayerLayer::start(){
    ball->getPhysicsBody()->setGravityEnable(true);
}

void GamePlayerLayer::showReady(){
    auto readyLabel = Label::createWithSystemFont("Ready!", "Arial", 180);
    readyLabel->setPosition(VisibleRect::center());
    readyLabel->setColor(Color3B::BLACK);
    this->addChild(readyLabel);
    
    auto fadeOut = FadeOut::create(0.5);
//    readyLabel->runAction(fadeOut);
    readyLabel->runAction(Sequence::create(DelayTime::create(0.5),fadeOut,CallFuncN::create(CC_CALLBACK_0(GamePlayerLayer::start,this)), NULL));
    
}

#pragma mark - Listener Call Back

void GamePlayerLayer::restartButtenTouchEvent(Ref* pSender){
    leftWins = 0;
    rightWins = 0;
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
    
    if (a->getTag() == GROUND_TAG || b->getTag() == GROUND_TAG) {
        if (a->getTag() == ENEMY_TAG || b->getTag() == ENEMY_TAG) {
            enemy->isJump = false;
            float playerRotation = enemy->getRotation();
            if (fabsf(playerRotation) > 5 && !enemy->isFall) {
                enemy->standup();
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
        if (a->getTag() == ENEMY_TAG || b->getTag() == ENEMY_TAG) {
            isEnemyContactBall = true;
            
            int boost = 700;
            Vec2 ballVelocity = ball->getPhysicsBody()->getVelocity();
            float sqrt = sqrtf(ballVelocity.x * ballVelocity.x + ballVelocity.y * ballVelocity.y);
            ball->getPhysicsBody()->setVelocity(Vec2(-ballVelocity.x/sqrt * boost,-ballVelocity.y/sqrt * boost));
            
            if (enemy->isJump) {
                hitBall();
            }
        }
    }
    
    
    if (a->getTag() == BALL_TAG || b->getTag() == BALL_TAG) {
        if (a->getTag() == GROUND_TAG || b->getTag() == GROUND_TAG) {
            if (ball->getPosition().x - VisibleRect::center().x < 0) {
                rightWins++;
            }
            else{
                leftWins++;
            }
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

#pragma mark - Util

void GamePlayerLayer::updateEnemy(){
    

    if (fabsf(ball->getPosition().x - enemy->getPosition().x) < 50) {
        enemy->jump();
    }
    else if (ball->getPosition().x < VisibleRect::center().x){
        isEnemyMove = false;
    }
    else if (ball->getPosition().x > VisibleRect::center().x){
        isEnemyMove = true;
    }
    ball->getPosition().x < enemy->getPosition().x ? isEnemyRight = false : true;
    
}

void GamePlayerLayer::updateWinCount(){
    leftWinLabel->setString(StringUtils::format("Score: %d",leftWins));
    rightWinLabel->setString(StringUtils::format("Score: %d",rightWins));
    
}