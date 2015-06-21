//
//  GamePlayerLayer.h
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#ifndef __Voooooolleyball__GamePlayerLayer__
#define __Voooooolleyball__GamePlayerLayer__

#include "cocos2d.h"
#include "GamePlayerSprite.h"


class GamePlayerLayer : public cocos2d::Layer{
public:
    CREATE_FUNC(GamePlayerLayer);
	virtual bool init();
    void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}
    
private:
    GamePlayerSprite *player;
    GamePlayerSprite *enemy;
    cocos2d::Sprite *ball;
    cocos2d::Vec2 beginTouchLocation;
    void configureTouchListener();
    void configurePlayer();
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    void playerMoveLeft();
    void playerMoveRight();
    void update(float dt) override;
    cocos2d::PhysicsWorld* m_world;
    void configurePhysicsContactListener();
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    void onContactSeperate(cocos2d::PhysicsContact& contact);
    virtual void onEnter() override;
    void configureEdge();
    void configureObstacle();
    void configureBall();
    void configureEnemy();
    void configureButton();
    void hitBall();
    void restart();
    void restartButtenTouchEvent(cocos2d::Ref* pSender);
    void homeButtenTouchEvent(Ref* pSender);
    void updateEnemy();
    void showReady();
    void start();
    void updateWinCount();
    void configureWinCountLabel();
};

#endif /* defined(__Voooooolleyball__GamePlayerLayer__) */
