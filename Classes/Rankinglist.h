#pragma once

#include "cocos2d.h"
#include<algorithm>
USING_NS_CC;

class Rankinglist : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Rankinglist);

    int score;

    void menuMenuCallback(cocos2d::Ref* pSender);
};

