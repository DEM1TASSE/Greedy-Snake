#pragma once

#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameoverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(GameoverScene);

    int score;

    void menuMenuCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
};
