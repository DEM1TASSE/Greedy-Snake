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
	auto background = LayerColor::create(Color4B(96,96,96, 180));
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
	map->setPosition(280,20);
	this->addChild(map);
	//绘制蛇头
    this->snakeHead = SNode::create();
	this->snakeHead->setColor(Color3B::RED);
	map->addChild(snakeHead);
	//初始化蛇头位置
	int rowSnakeHead = rand() % 10;
	int columnSnakeHead = rand() % 10;
	this->snakeHead->moveTo(rowSnakeHead*30,columnSnakeHead*30);
	snakeHead->dir = SNAKE_DIR::DOWN;
	//绘制食物
	this->food = SNode::create();
	this->snakeHead->setColor(Color3B::ORANGE);
    mapx = map->getPositionX();
    mapy = map->getPositionY();
	map->addChild(food);
	int rowFood = 0, columnFood = 0;
	//初始化食物位置，且要防止食物的位置和蛇头位置重叠
	while (1)
	{
		srand(time(NULL));
		int rowFood = rand() % 20;
		int columnFood = rand() % 20;
		this->food->moveTo(rowFood * 30, columnFood * 30);
		if (rowFood != rowSnakeHead || columnFood != columnSnakeHead)
			break;
	}
	//让蛇头运动
    //this->snakeHead->schedule(CC_SCHEDULE_SELECTOR(GameScene::gameLogc), 0.2);
    //改变蛇头方向
    //auto* dispatcher = Director::getInstance()->getEventDispatcher();
    //auto* keyListener = EventListenerKeyboard::create();
    //键盘被按下时响应
    /*keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    //键盘按键被弹回时响应
    keyListener->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
    dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);*/
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
        snakeHead->moveTo(snakeHead->x, snakeHead->y - 30);
        break;
    case SNAKE_DIR::UP:
        snakeHead->moveTo(snakeHead->x, snakeHead->y + 30);
        break;
    case SNAKE_DIR::LEFT:
        snakeHead->moveTo(snakeHead->x - 30, snakeHead->y);
        break;
    case SNAKE_DIR::RIGHT:
        snakeHead->moveTo(snakeHead->x + 30, snakeHead->y);
        break;
    }
    //移动身体
    for (int i = allBody.size() - 1; i >= 0; i--)
    {
        SNode* nowbody = allBody.at(i);
        switch (nowbody->dir) 
        {
        case SNAKE_DIR::DOWN:
            nowbody->moveTo(nowbody->x, nowbody->y - 30);
            break;
        case SNAKE_DIR::UP:
            nowbody->moveTo(nowbody->x, nowbody->y + 30);
            break;
        case SNAKE_DIR::LEFT:
            nowbody->moveTo(nowbody->x - 30, nowbody->y);
            break;
        case SNAKE_DIR::RIGHT:
            nowbody->moveTo(nowbody->x + 30, nowbody->y);
            break;
        }

        if (i == 0) {
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
        //新生成食物
        int row = rand() % 20;
        int col = rand() % 20;
        this->food->moveTo(col * 30, row * 30);
        SNode* newBody = SNode::create();
        newBody->setColor(Color3B::BLUE);
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
        this->getChildByTag(10)->addChild(newBody);
    }
}

void GameScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
    if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
        this->snakeHead->dir= SNAKE_DIR::UP;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
        this->snakeHead->dir = SNAKE_DIR::DOWN;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
        this->snakeHead->dir = SNAKE_DIR::LEFT;
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
        this->snakeHead->dir = SNAKE_DIR::RIGHT;
    }
}