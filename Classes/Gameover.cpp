#include"Menu.h"
#include"Game.h"
#include"Gameover.h"
#include"HelloWorldScene.h"

USING_NS_CC;

Scene* GameoverScene::createScene()
{
    return GameoverScene::create();
}

bool GameoverScene::init()
{

    if (!Scene::init())
    {
        return false;
    }
    //获取界面大小
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto title = Label::createWithTTF("Gameover!", "fonts/Marker Felt.ttf", 70);
    title->setPosition(visibleSize.width / 2, visibleSize.height * 0.8);
    this->addChild(title);

    auto scoreLabel = Label::createWithTTF("Your score is", "fonts/Marker Felt.ttf", 70);
    scoreLabel->setString(StringUtils::format("Your score is % d", score));
    scoreLabel->setPosition(visibleSize.width / 2, visibleSize.height * 0.65);
    this->addChild(scoreLabel);

    auto menuLabel = Label::createWithTTF("Back to Menu", "fonts/Marker Felt.ttf", 50);
    menuLabel->enableGlow(Color4B::BLUE);//设置荧光效果
    auto menuItem = MenuItemLabel::create(menuLabel, CC_CALLBACK_1(GameoverScene::menuMenuCallback, this));
    menuItem->setPosition(visibleSize.width / 2, visibleSize.height * 0.4);

    auto exitLabel = Label::createWithTTF("Exit", "fonts/Marker Felt.ttf", 50);
    exitLabel->enableGlow(Color4B::BLUE);//设置荧光效果
    auto exitItem = MenuItemLabel::create(exitLabel, CC_CALLBACK_1(GameoverScene::menuExitCallback, this));
    exitItem->setPosition(visibleSize.width / 2, visibleSize.height * 0.25);

    auto menu = Menu::create(menuItem,exitItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void GameoverScene::menuMenuCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.2, MainMenu::createScene()));
}

void GameoverScene::menuExitCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->end();
}