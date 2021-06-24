#include"Level.h"
#include"Game.h"
#include"HelloWorldScene.h"
USING_NS_CC;

Scene* LevelScene::createScene()
{
    return LevelScene::create();
}

bool LevelScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    //获取界面大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background = LayerColor::create(Color4B(248, 246, 231, 255));
    this->addChild(background);
    auto title = Label::createWithTTF("Level", "fonts/Marker Felt.ttf", 70);
    title->setPosition(visibleSize.width / 2, visibleSize.height * 0.8);
    title->setTextColor(Color4B::ORANGE);
    this->addChild(title);
    //简单难度
    auto easyLabel = Label::createWithTTF("Easy", "fonts/Marker Felt.ttf", 50);
    easyLabel->enableOutline(Color4B::ORANGE,3);//设置描边
    auto easyItem = MenuItemLabel::create(easyLabel, CC_CALLBACK_1(LevelScene::menuEasyCallback, this));
    easyItem->setPosition(visibleSize.width / 2, visibleSize.height * 0.55);
    //中等难度
    auto normalLabel = Label::createWithTTF("Normal", "fonts/Marker Felt.ttf", 50);
    normalLabel->enableOutline(Color4B::ORANGE,3);
    auto normalItem = MenuItemLabel::create(normalLabel, CC_CALLBACK_1(LevelScene::menuNormalCallback, this));
    normalItem->setPosition(visibleSize.width / 2, visibleSize.height * 0.4);
    //复杂难度
    auto difficultLabel = Label::createWithTTF("Difficult", "fonts/Marker Felt.ttf", 50);
    difficultLabel->enableOutline(Color4B::ORANGE,3);
    auto difficultItem = MenuItemLabel::create(difficultLabel, CC_CALLBACK_1(LevelScene::menuDifficultCallback, this));
    difficultItem->setPosition(visibleSize.width / 2, visibleSize.height * 0.25);
    auto menu = Menu::create(easyItem, normalItem, difficultItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void LevelScene::menuEasyCallback(cocos2d::Ref* pSender)
{
    UserDefault::getInstance()->setFloatForKey("speed", 0.3);
    Director::getInstance()->replaceScene(TransitionFade::create(1.2, GameScene::createScene()));
}

void LevelScene::menuNormalCallback(cocos2d::Ref* pSender)
{
    UserDefault::getInstance()->setFloatForKey("speed", 0.2);
    Director::getInstance()->replaceScene(TransitionFade::create(1.2, GameScene::createScene()));
}

void LevelScene::menuDifficultCallback(cocos2d::Ref* pSender)
{
    UserDefault::getInstance()->setFloatForKey("speed", 0.1);
    Director::getInstance()->replaceScene(TransitionFade::create(1.2, GameScene::createScene()));
}