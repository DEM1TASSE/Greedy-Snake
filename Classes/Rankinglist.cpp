#include"Menu.h"
#include"HelloWorldScene.h"
#include"Rankinglist.h"
#include<algorithm>
using namespace std;
USING_NS_CC;

Scene* Rankinglist::createScene()
{
    return Rankinglist::create();
}

bool Rankinglist::init()
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
    //创建标题
    auto title = Label::createWithTTF("Ranking List", "fonts/Marker Felt.ttf", 70);
    title->setTextColor(Color4B::GRAY);
    title->setPosition(visibleSize.width / 2, visibleSize.height * 0.85);
    this->addChild(title);

    //读取原有排行榜
    int score[5];
    score[0] = UserDefault::getInstance()->getIntegerForKey("bestScore1");
    score[1] = UserDefault::getInstance()->getIntegerForKey("bestScore2");
    score[2] = UserDefault::getInstance()->getIntegerForKey("bestScore3");
    score[3] = UserDefault::getInstance()->getIntegerForKey("bestScore4");
    score[4] = UserDefault::getInstance()->getIntegerForKey("bestScore5");

    //打印排行榜
    auto scoreLabel1 = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 40);
    scoreLabel1->setTextColor(Color4B::GRAY);
    scoreLabel1->setString(StringUtils::format("1. % d", score[0]));
    scoreLabel1->setPosition(visibleSize.width / 2, visibleSize.height * 0.7);
    this->addChild(scoreLabel1);
    auto scoreLabel2 = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 40);
    scoreLabel2->setTextColor(Color4B::GRAY);
    scoreLabel2->setString(StringUtils::format("2. % d", score[1]));
    scoreLabel2->setPosition(visibleSize.width / 2, visibleSize.height * 0.6);
    this->addChild(scoreLabel2);
    auto scoreLabel3 = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 40);
    scoreLabel3->setTextColor(Color4B::GRAY);
    scoreLabel3->setString(StringUtils::format("3. % d", score[2]));
    scoreLabel3->setPosition(visibleSize.width / 2, visibleSize.height * 0.5);
    this->addChild(scoreLabel3);
    auto scoreLabel4 = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 40);
    scoreLabel4->setTextColor(Color4B::GRAY);
    scoreLabel4->setString(StringUtils::format("4. % d", score[3]));
    scoreLabel4->setPosition(visibleSize.width / 2, visibleSize.height * 0.4);
    this->addChild(scoreLabel4);
    auto scoreLabel5 = Label::createWithTTF(" ", "fonts/Marker Felt.ttf", 40);
    scoreLabel5->setTextColor(Color4B::GRAY);
    scoreLabel5->setString(StringUtils::format("5. % d", score[4]));
    scoreLabel5->setPosition(visibleSize.width / 2, visibleSize.height * 0.3);
    this->addChild(scoreLabel5);

    //返回主界面的按钮
    auto menuLabel = Label::createWithTTF("Back to Menu", "fonts/Marker Felt.ttf", 50);
    menuLabel->setTextColor(Color4B::GRAY);
    auto menuItem = MenuItemLabel::create(menuLabel, CC_CALLBACK_1(Rankinglist::menuMenuCallback, this));
    menuItem->setPosition(visibleSize.width / 2, visibleSize.height * 0.15);
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    return true;
}

void Rankinglist::menuMenuCallback(cocos2d::Ref* pSender)
{
    Director::getInstance()->replaceScene(TransitionFade::create(1.2, MainMenu::createScene()));
}