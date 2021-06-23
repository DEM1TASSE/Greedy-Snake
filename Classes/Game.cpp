#include"Game.h"
#include"HelloWorldScene.h"
Scene* GameScene::createScene()//��������
{
    auto scene = Scene::create();
    auto layer = GameScene::create();//����һ����
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //������Ϸ����
    auto background = LayerColor::create(Color4B(96, 96, 96, 180));
    this->addChild(background);
    //������Ϸ��ͼ
    auto map = DrawNode::create();//����drawnode������ͼ����
    map->setTag(10);
    for (int i = 0; i <= 20; i++)
    {
        //����21�����ߣ�21������
        map->drawSegment(Vec2(0, i * 30), Vec2(600, i * 30), 0.7, Color4F::GRAY);
        map->drawSegment(Vec2(i * 30, 0), Vec2(i * 30, 600), 0.7, Color4F::GRAY);
    }
    map->setPosition(280, 20);
    this->addChild(map);
    //������ͷ
    this->snakeHead = SNode::create();
    this->snakeHead->setColor(Color3B::RED);
    this->addChild(snakeHead);
    //��ʼ����ͷλ��
    int rowSnakeHead = rand() % 10;
    int columnSnakeHead = rand() % 10;
    snakeHead->moveTo(rowSnakeHead * 30+280, columnSnakeHead * 30+20);
    //snakeHead->dir = SNAKE_DIR::DOWN;
    //����ʳ��
    food = SNode::create();
    food->setColor(Color3B::ORANGE);
    addChild(food);
    int rowFood = 0, columnFood = 0;
    //��ʼ��ʳ��λ�ã���Ҫ��ֹʳ���λ�ú���ͷλ���ص�
    while (1)
    {
        srand(time(NULL));
        int rowFood = rand() % 20;
        int columnFood = rand() % 20;
        this->food->moveTo(rowFood * 30+280, columnFood * 30+20);
        if (rowFood != rowSnakeHead || columnFood != columnSnakeHead)
            break;
    }
    this->speed = 5;//�趨��ʼ�ٶ�
    //��ʾ����;
    this->score = 0;//�趨��ʼ����
    auto labelScore = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 50);
    labelScore->setPosition(40, 320);
    labelScore->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    labelScore->setTag(1);
    this->addChild(labelScore);
    labelScore->setString(StringUtils::format("Score: % d", score));
    //����ͷ�˶�
    schedule(CC_SCHEDULE_SELECTOR(GameScene::gameLogc), 1/speed);
    //�ı���ͷ����
    auto* dispatcher = Director::getInstance()->getEventDispatcher();
    auto* keyListener = EventListenerKeyboard::create();
    //���̱�����ʱ��Ӧ
    keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    //���̰���������ʱ��Ӧ
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
    //��ʼ��Ϊһ����ɫ����
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

void GameScene::gameLogc(float t) //��Ϸ�߼���ʵ��
{
    //�ƶ���ͷ
    switch (snakeHead->dir)
    {
    case SNAKE_DIR::DOWN:
        if (snakeHead->y != 20)//�߽��⣬��ͬ
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
    //�ƶ�����
    for (int i = allBody.size() - 1; i >= 0; i--)
    {
        SNode* nowbody = allBody.at(i);
        switch (nowbody->dir)
        {
        case SNAKE_DIR::DOWN:
            if (nowbody->y != 20)//�߽��⣬��ͬ
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
            nowbody->dir = allBody.at(i - 1)->dir;//������һ������
        }
    }

    //��ײ�ж�
    if (snakeHead->x == food->x && snakeHead->y == food->y)
    {
        //����+1����ʾ����
        auto labelScore = (Label*)this->getChildByTag(1);
        score++;
        labelScore->setString(StringUtils::format("Score: % d", score));
        if (score % 4 == 0&&score<=20)//ÿ4�ּ�һ���٣���߲�����5��
        {
            Scheduler* pSchedule = Director::getInstance()->getScheduler();//��ȡȫ��ʱ�������
            pSchedule->setTimeScale(1.3f);
        }
        //������ʳ��
        while (1)
        {
            srand(time(NULL));
            int rowFood = rand() % 20;
            int columnFood = rand() % 20;
            bool repeat = false;
            //��ֹʳ��������ظ�
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
        //�µ��������ߵ�β��
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
    //��Ϸ�����ж�
    for (int i = allBody.size() - 1; i >= 0; i--)
    {
        if (allBody.at(i)->x == snakeHead->x && allBody.at(i)->y == snakeHead->y)
            this->unschedule(CC_SCHEDULE_SELECTOR(GameScene::gameLogc));
        //�����ͷ���������gameover
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