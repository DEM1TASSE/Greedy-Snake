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
	auto background = LayerColor::create(Color4B(96,96,96, 180));
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
	map->setPosition(280,20);
	this->addChild(map);
	//������ͷ
    this->snakeHead = SNode::create();
	this->snakeHead->setColor(Color3B::RED);
	map->addChild(snakeHead);
	//��ʼ����ͷλ��
	int rowSnakeHead = rand() % 10;
	int columnSnakeHead = rand() % 10;
	this->snakeHead->moveTo(rowSnakeHead*30,columnSnakeHead*30);
	snakeHead->dir = SNAKE_DIR::DOWN;
	//����ʳ��
	this->food = SNode::create();
	this->snakeHead->setColor(Color3B::ORANGE);
    mapx = map->getPositionX();
    mapy = map->getPositionY();
	map->addChild(food);
	int rowFood = 0, columnFood = 0;
	//��ʼ��ʳ��λ�ã���Ҫ��ֹʳ���λ�ú���ͷλ���ص�
	while (1)
	{
		srand(time(NULL));
		int rowFood = rand() % 20;
		int columnFood = rand() % 20;
		this->food->moveTo(rowFood * 30, columnFood * 30);
		if (rowFood != rowSnakeHead || columnFood != columnSnakeHead)
			break;
	}
	//����ͷ�˶�
    //this->snakeHead->schedule(CC_SCHEDULE_SELECTOR(GameScene::gameLogc), 0.2);
    //�ı���ͷ����
    //auto* dispatcher = Director::getInstance()->getEventDispatcher();
    //auto* keyListener = EventListenerKeyboard::create();
    //���̱�����ʱ��Ӧ
    /*keyListener->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
    //���̰���������ʱ��Ӧ
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
    //�ƶ�����
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
            nowbody->dir = allBody.at(i - 1)->dir;//������һ������
        }
    }

    //��ײ�ж�
    if (snakeHead->x == food->x && snakeHead->y == food->y)
    {
        //������ʳ��
        int row = rand() % 20;
        int col = rand() % 20;
        this->food->moveTo(col * 30, row * 30);
        SNode* newBody = SNode::create();
        newBody->setColor(Color3B::BLUE);
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