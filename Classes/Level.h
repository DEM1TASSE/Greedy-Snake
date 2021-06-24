#pragma once
#pragma once

#include "cocos2d.h"
USING_NS_CC;

class LevelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(LevelScene);

    void menuEasyCallback(cocos2d::Ref* pSender);
    void menuNormalCallback(cocos2d::Ref* pSender);
    void menuDifficultCallback(cocos2d::Ref* pSender);
};