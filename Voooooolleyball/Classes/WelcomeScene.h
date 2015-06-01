//
//  WelcomeScene.h
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#ifndef __Voooooolleyball__WelcomeScene__
#define __Voooooolleyball__WelcomeScene__

#include "cocos2d.h"
#include "WelcomeBackgroundLayer.h"
#include "WelcomeButtonLayer.h"

class WelcomeScene : public cocos2d::Scene {
private:
    static Scene* welcomeScene;
    static WelcomeButtonLayer* welcomeButtonLayer;
    static WelcomeBackgroundLayer* welcomeBackgroundLayer;
    
public:
    static cocos2d::Scene* create();
    
};

#endif /* defined(__Voooooolleyball__WelcomeScene__) */
