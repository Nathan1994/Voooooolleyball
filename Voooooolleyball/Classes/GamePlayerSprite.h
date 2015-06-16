//
//  GamePlayerSprite.h
//  Voooooolleyball
//
//  Created by Nathan on 6/16/15.
//
//

#ifndef __Voooooolleyball__GamePlayerSprite__
#define __Voooooolleyball__GamePlayerSprite__

#include "cocos2d.h"
class GamePlayerSprite: public cocos2d::Sprite{
public:
    void jump();
    void fall();
    static GamePlayerSprite* create(const std::string& filename);
    bool isJump;
    void standup();
    bool isFall;
    
private:
    void update(float dt) override;
    void fallDidFinished();
};

#endif /* defined(__Voooooolleyball__GamePlayerSprite__) */
