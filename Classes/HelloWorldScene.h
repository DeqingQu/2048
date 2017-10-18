#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "CardSprite.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
//    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    //  手势识别的检测
    virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
    
    //  上下左右滑动的方法
    bool doUp();
    bool doDown();
    bool doLeft();
    bool doRight();
    
    //  创建卡片
    void createCardSprite(cocos2d::Size size);
    //  自动生成卡片
    void autoCreateCardNumber();
    //  判断游戏能否继续
    void doCheckGameOver();
    //  判断能否增加新的卡片
    bool canAddNewCardNumber();
    
private:
    int firstX, firstY, endX, endY;
    CardSprite* cardArray[4][4];
    int score;
    cocos2d::Label* labelTTFCardNumber;
    
    void updateScore(int newScore);
    void scaleCardSprite(float s, int x, int y);
};

#endif // __HELLOWORLD_SCENE_H__
