#pragma once

#include "cocos2d.h"
USING_NS_CC;

class MainMenu : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(MainMenu);

    void menuStartCallback(cocos2d::Ref* pSender);
    void menuExitCallback(cocos2d::Ref* pSender);
    void menuRankinglistCallback(cocos2d::Ref* pSender);
};