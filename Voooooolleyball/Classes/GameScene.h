//
//  GameScene.h
//  Voooooolleyball
//
//  Created by Nathan on 5/25/15.
//
//

#ifndef __Voooooolleyball__GameScene__
#define __Voooooolleyball__GameScene__

#include "cocos2d.h"
#include "GamePlayerLayer.h"
#include "GameBackgroundLayer.h"

class GameScene : public cocos2d::Scene
{
    
public:
    static cocos2d::Scene* create();

    
private:
    static cocos2d::Scene* gameScene;
    static GamePlayerLayer* playerLayer;
    static GameBackgroundLayer* backgroundLayer;


    
};

#endif // __HELLOWORLD_SCENE_H__
