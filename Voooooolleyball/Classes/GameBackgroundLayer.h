//
//  GameBackgroundLayer.h
//  Voooooolleyball
//
//  Created by Nathan on 6/14/15.
//
//

#ifndef __Voooooolleyball__GameBackgroundLayer__
#define __Voooooolleyball__GameBackgroundLayer__

#include "cocos2d.h"
class GameBackgroundLayer: public cocos2d::Layer{
public:
    CREATE_FUNC(GameBackgroundLayer);
    
private:
    virtual void onEnter() override;
    
};

#endif /* defined(__Voooooolleyball__GameBackgroundLayer__) */
