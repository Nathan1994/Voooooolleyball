//
//  WelcomeButtonLayer.h
//  Voooooolleyball
//
//  Created by Nathan on 6/1/15.
//
//

#ifndef __Voooooolleyball__WelcomeButtonLayer__
#define __Voooooolleyball__WelcomeButtonLayer__

#include "cocos2d.h"

class WelcomeButtonLayer : public cocos2d::Layer {
private:
    void startGameButtonCallBack(Ref* pSender);
    void helpButtonCallBack(Ref* pSender);
    virtual bool init() override;
    
public:
    CREATE_FUNC(WelcomeButtonLayer);
};

#endif /* defined(__Voooooolleyball__WelcomeButtonLayer__) */
