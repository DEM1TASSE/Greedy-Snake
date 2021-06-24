#include"Menu.h"
#include"Game.h"
#include"HelloWorldScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

bool MainMenu::init()
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
    auto title = Label::createWithTTF("Greedy Snake", "fonts/Marker Felt.ttf", 70);
    title->setPosition(visibleSize.width/2,visibleSize.height*0.8);
    title->setTextColor(Color4B::BLACK);
    this->addChild(title);
    //开始键
    auto startLabel = Label::createWithTTF("Start", "fonts/Marker Felt.ttf", 50);
    startLabel->enableGlow(Color4B::BLUE);//设置荧光效果
    auto startItem = MenuItemLabel::create(startLabel, CC_CALLBACK_1(MainMenu::menuStartCallback, this));
    startItem->setPosition(visibleSize.width/2,visibleSize.height*0.55);
    //退出键
    auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 50);
    exitLabel->enableGlow(Color4B::BLUE);//设置荧光效果
    auto exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(MainMenu::menuExitCallback, this));
    exitItem->setPosition(visibleSize.width / 2, visibleSize.height * 0.25);
    //排行榜
    auto rankingLabel = Label::createWithTTF("RankingList", "fonts/Marker Felt.ttf", 50);
    rankingLabel->enableGlow(Color4B::BLUE);//设置荧光效果
    auto rankingItem = MenuItemLabel::create(rankingLabel, CC_CALLBACK_1(MainMenu::menuExitCallback, this));
    rankingItem->setPosition(visibleSize.width / 2, visibleSize.height * 0.4);
    auto menu = Menu::create(startItem,exitItem,rankingItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void MainMenu::menuStartCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.2, GameScene::createScene()));
}

void MainMenu::menuExitCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->end();
}