#include"Game.h"
#include"HelloWorldScene.h"
Scene* GameScene::createScene()//创建场景
{
    auto scene = Scene::create();
    auto layer = GameScene::create();//创建一个层
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //绘制游戏背景
    auto background = LayerColor::create(Color4B(96, 96, 96, 180));
    this->addChild(background);
    //绘制游戏地图
    auto map = DrawNode::create();//运用drawnode来画地图方框
    map->setTag(10);
    for (int i = 0; i <= 20; i++)
    {
        //绘制21条横线，21条竖线
        map->drawSegment(Vec2(0, i * 30), Vec2(600, i * 30), 0.7, Color4F::GRAY);
        map->drawSegment(Vec2(i * 30, 0), Vec2(i * 30, 600), 0.7, Color4F::GRAY);
    }
    map->setPosition(280, 20);
    this->addChild(map);
    //绘制蛇头
    this->snakeHead = SNode::create();
    this->snakeHead->setColor(Color3B::RED);
    this->addChild(snakeHead);
    //初始化蛇头位置
    int rowSnakeHead = rand() % 10;
    int columnSnakeHead = rand() % 10;
    snakeHead->moveTo(rowSnakeHead * 30+280, columnSnakeHead * 30+20);
    //snakeHead->dir = SNAKE_DIR::DOWN;
    //绘制食物
    food = SNode::create();
    food->setColor(Color3B::ORANGE);
    addChild(food);
    int rowFood = 0, columnFood = 0;
    //初始化食物位置，且要防止食物的位置和蛇头位置重叠
    while (1)
    {
        srand(time(NULL));
        int rowFood = rand() % 20;
        int columnFood = rand() % 20;
        this->food->moveTo(rowFood * 30+280, columnFood * 30+20);
        if (rowFood != rowSnakeHead || columnFood != columnSnakeHead)
            break;
    }
    this->speed = 5;//设定初始速度
    //显示分数;
    this->score = 0;//设定初始分数
    auto labelScore = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 50);
    labelScore->setPosition(40, 320);
    labelScore->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    labelScore->setTag(1);
    this->addChild(labelScore);
    labelScore->setString(StringUtils::format("Score: % d", score));
    //让蛇头运动
    schedule(CC_SCHEDULE_SELECTOR(GameScene::gameLogc), 1/speed);
    //改变蛇头方向
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    //键盘被按下时响应
    keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    //键盘按键被弹回时响应
    keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
    return true;
}

bool SNode::init()
{
    if (!Node::init())
    {
        return false;
    }
    //初始化为一个红色矩形
    this->sprite = LayerColor::create(Color4B::RED);
    this->sprite->setContentSize(Size(30, 30));
    this->addChild(sprite);
    return true;
}

void SNode::setColor(Color3B color)
{
    this->sprite->setColor(color);
}

void SNode::moveTo(int px, int py)
{
    this->x = px;
    this->y = py;
    this->sprite->setPosition(Vec2(px, py));
}

void GameScene::gameLogc(float t) //游戏逻辑的实现
{
    //移动蛇头
    switch (snakeHead->dir)
    {
    case SNAKE_DIR::DOWN:
        if (snakeHead->y != 20)//边界检测，下同
            snakeHead->moveTo(snakeHead->x, snakeHead->y - 30);
        else
            snakeHead->moveTo(snakeHead->x, 590);
        break;
    case SNAKE_DIR::UP:
        if (snakeHead->y != 590)
            snakeHead->moveTo(snakeHead->x, snakeHead->y + 30);
        else
            snakeHead->moveTo(snakeHead->x, 20);
        break;
    case SNAKE_DIR::LEFT:
        if (snakeHead->x != 280)
            snakeHead->moveTo(snakeHead->x - 30, snakeHead->y);
        else
            snakeHead->moveTo(850, snakeHead->y);
        break;
    case SNAKE_DIR::RIGHT:
        if (snakeHead->x != 850)
            snakeHead->moveTo(snakeHead->x + 30, snakeHead->y);
        else
            snakeHead->moveTo(280, snakeHead->y);
        break;
    }
    //移动身体
    for (int i = allBody.size() - 1; i >= 0; i--)
    {
        SNode* nowbody = allBody.at(i);
        switch (nowbody->dir)
        {
        case SNAKE_DIR::DOWN:
            if (nowbody->y != 20)//边界检测，下同
                nowbody->moveTo(nowbody->x, nowbody->y - 30);
            else
                nowbody->moveTo(nowbody->x, 590);
            break;
        case SNAKE_DIR::UP:
            if (nowbody->y != 590)
                nowbody->moveTo(nowbody->x, nowbody->y + 30);
            else
                nowbody->moveTo(nowbody->x, 20);
            break;
        case SNAKE_DIR::LEFT:
            if (nowbody->x != 280)
                nowbody->moveTo(nowbody->x - 30, nowbody->y);
            else
                nowbody->moveTo(850, nowbody->y);
            break;
        case SNAKE_DIR::RIGHT:
            if (nowbody->x != 850)
                nowbody->moveTo(nowbody->x + 30, nowbody->y);
            else
                nowbody->moveTo(280, nowbody->y);
            break;
        }

        if (i == 0) 
        {
            allBody.at(0)->dir = snakeHead->dir;
        }
        else
        {
            nowbody->dir = allBody.at(i - 1)->dir;//等于上一个方向
        }
    }

    //碰撞判断
    if (snakeHead->x == food->x && snakeHead->y == food->y)
    {
        //分数+1并显示分数
        auto labelScore = (Label*)this->getChildByTag(1);
        score++;
        labelScore->setString(StringUtils::format("Score: % d", score));
        if (score % 4 == 0&&score<=20)//每4分加一次速，最高不超过5次
        {
            Scheduler* pSchedule = Director::getInstance()->getScheduler();//获取全局时间管理者
            pSchedule->setTimeScale(1.3f);
        }
        //新生成食物
        while (1)
        {
            srand(time(NULL));
            int rowFood = rand() % 20;
            int columnFood = rand() % 20;
            bool repeat = false;
            //防止食物和身体重复
            for (int i = allBody.size() - 1; i >= 0; i--)
            {
                if ((rowFood*30+280) == allBody.at(i)->x && (columnFood*30+20) == allBody.at(i)->y)
                {
                    repeat = true;
                }
            }
            if ((rowFood * 30 + 280) == snakeHead->x && (columnFood * 30 + 20) == snakeHead->y)
            {
                repeat = true;
            }
            if (repeat == false)
            {
                this->food->moveTo(rowFood * 30 + 280, columnFood * 30 + 20);
                break;
            }
        }
        SNode* newBody = SNode::create();
        newBody->setColor(Color3B::RED);
        //新的身体在蛇的尾部
        if (allBody.size() == 0)
        {
            switch (snakeHead->dir)
            {
            case SNAKE_DIR::DOWN:
                newBody->moveTo(snakeHead->x, snakeHead->y + 30);
                break;
            case SNAKE_DIR::UP:
                newBody->moveTo(snakeHead->x, snakeHead->y - 30);
                break;
            case SNAKE_DIR::LEFT:
                newBody->moveTo(snakeHead->x + 30, snakeHead->y);
                break;
            case SNAKE_DIR::RIGHT:
                newBody->moveTo(snakeHead->x - 30, snakeHead->y);
                break;
            }
            allBody.pushBack(newBody);
            newBody->dir = snakeHead->dir;
        }
        else
        {
            SNode* lastBody = allBody.at(allBody.size() - 1);
            switch (lastBody->dir)
            {
            case SNAKE_DIR::DOWN:
                newBody->moveTo(lastBody->x, lastBody->y + 30);
                break;
            case SNAKE_DIR::UP:
                newBody->moveTo(lastBody->x, lastBody->y - 30);
                break;
            case SNAKE_DIR::LEFT:
                newBody->moveTo(lastBody->x + 30, lastBody->y);
                break;
            case SNAKE_DIR::RIGHT:
                newBody->moveTo(lastBody->x - 30, lastBody->y);
                break;
            }
            allBody.pushBack(newBody);
            newBody->dir = lastBody->dir;
        }
        this->addChild(newBody);
    }
    //游戏结束判断
    for (int i = allBody.size() - 1; i >= 0; i--)
    {
        if (allBody.at(i)->x == snakeHead->x && allBody.at(i)->y == snakeHead->y)
            this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::gameLogc));
        //如果蛇头碰到身体就gameover
    }
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
    if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW)
    {
        if(allBody.size()==0||(allBody.size()!=0&&this->snakeHead->dir!=SNAKE_DIR::DOWN))
            this->snakeHead->dir = SNAKE_DIR::UP;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) 
    {
        if (allBody.size() == 0 || (allBody.size() != 0 && this->snakeHead->dir != SNAKE_DIR::UP))
            this->snakeHead->dir = SNAKE_DIR::DOWN;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
    {
        if (allBody.size() == 0 || (allBody.size() != 0 && this->snakeHead->dir != SNAKE_DIR::RIGHT))
            this->snakeHead->dir = SNAKE_DIR::LEFT;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
    {
        if (allBody.size() == 0 || (allBody.size() != 0 && this->snakeHead->dir != SNAKE_DIR::LEFT))
            this->snakeHead->dir = SNAKE_DIR::RIGHT;
    }
}