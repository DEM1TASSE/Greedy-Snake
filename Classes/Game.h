#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
using namespace ui;
//ö�ٶ������˶�����
enum class SNAKE_DIR
{
    UP,
    LEFT,
    RIGHT,
    DOWN
};
class SNode :public Node//һ���ڵ��࣬������������
{
public:
    LayerColor* sprite;
    int x, y;//����
    SNAKE_DIR dir;//����
    CREATE_FUNC(SNode);
    bool init();//��ʼ��
    void setColor(Color3B color);
    void moveTo(int x, int y);
};

class GameScene :public Layer
{
public:
    SNode* snakeHead;//��ͷ
    SNode* food;//ʳ��
    Vector<SNode*> allBody;//��vector��ɵĽڵ��������
    int mapx;
    int mapy;
    CREATE_FUNC(GameScene);
    bool init();
    static Scene* createScene();
    void gameLogc(float t);//�߼�
    virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//��������
    //virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
};