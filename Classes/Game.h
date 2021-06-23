#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;
using namespace ui;
//枚举定义蛇运动方向
enum class SNAKE_DIR
{
    UP,
    LEFT,
    RIGHT,
    DOWN
};
class SNode :public Node//一个节点类，包含各种属性
{
public:
    LayerColor* sprite;
    int x, y;//坐标
    SNAKE_DIR dir;//方向
    CREATE_FUNC(SNode);
    bool init();//初始化
    void setColor(Color3B color);
    void moveTo(int x, int y);
};

class GameScene :public Layer
{
public:
    SNode* snakeHead;//蛇头
    SNode* food;//食物
    Vector<SNode*> allBody;//用vector组成的节点代表身体
    int mapx;
    int mapy;
    CREATE_FUNC(GameScene);
    bool init();
    static Scene* createScene();
    void gameLogc(float t);//逻辑
    virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);//监听键盘
    //virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
};