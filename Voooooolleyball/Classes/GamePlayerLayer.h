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
class GamePlayerLayer : public cocos2d::Layer{
public:
    CREATE_FUNC(GamePlayerLayer);
	virtual bool init();
    void setPhyWorld(cocos2d::PhysicsWorld* world){m_world = world;}
    
private:
    cocos2d::Sprite *player;
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
    virtual void onEnter() override;
    void configureEdge();
    void configureObstacle();
    
};

#endif /* defined(__Voooooolleyball__GamePlayerLayer__) */
