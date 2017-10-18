#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180, 170, 160, 255));
    this->addChild(layerColorBG);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    createCardSprite(visibleSize);
    
    auto labelTTFCardNumberName = Label::createWithSystemFont("SCORE","Consolas",40);
    labelTTFCardNumberName->setPosition(Point(visibleSize.width-200, visibleSize.height-40));
    this->addChild(labelTTFCardNumberName);
    
    auto actionBy = ScaleBy::create(2.0f, 2, 2);
    labelTTFCardNumberName->runAction(Sequence::create(actionBy, actionBy->reverse(), NULL));
    
    labelTTFCardNumber = Label::createWithSystemFont("0", "Consolas-W6", 40);
    labelTTFCardNumber->setPosition(Point(visibleSize.width-70,visibleSize.height-40));
    this->addChild(labelTTFCardNumber);
    
    autoCreateCardNumber();
    autoCreateCardNumber();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Point touchPoint = touch->getLocation();
    firstX = touchPoint.x;
    firstY = touchPoint.y;
    
    return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    Point touchPoint = touch->getLocation();
    endX = firstX - touchPoint.x;
    endY = firstY - touchPoint.y;
    
    log("begin:%d, %d; end:%d, %d", firstX, firstY, int(touchPoint.x), int(touchPoint.y));
    
    if (abs(endX) > abs(endY)) {
        if (endX > 0 && abs(endX) > 20) {
            if(doLeft()) {
                if (canAddNewCardNumber()) {
                    autoCreateCardNumber();
                }
                doCheckGameOver();
            }
        }
        else if (endX < 0 && abs(endX) > 20) {
            if (doRight()) {
                if (canAddNewCardNumber()) {
                    autoCreateCardNumber();
                }
                doCheckGameOver();
            }
        }
    }
    else {
        if (endY > 0 && abs(endY) > 20) {
            if(doDown()) {
                if (canAddNewCardNumber()) {
                    autoCreateCardNumber();
                }
                doCheckGameOver();
            }
        }
        else if(endY < 0 && abs(endY) > 20){
            if(doUp()) {
                if (canAddNewCardNumber()) {
                    autoCreateCardNumber();
                }
                doCheckGameOver();
            }
        }
    }
    

}

bool HelloWorld::doLeft()
{
    log("doLeft");
    
    bool isdo = false;
    
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            
            for (int x1=x+1; x1<4; x1++) {
                if(cardArray[x1][y]->getNumber() > 0)
                {
                    if (cardArray[x][y]->getNumber() <= 0)
                    {
                        cardArray[x][y]->setNumber(cardArray[x1][y]->getNumber());
                        cardArray[x1][y]->setNumber(0);
                        
                        x--;
                        isdo = true;
                    }
                    else if(cardArray[x][y]->getNumber() == cardArray[x1][y]->getNumber()) {
                        cardArray[x][y]->setNumber(cardArray[x][y]->getNumber()*2);
                        cardArray[x1][y]->setNumber(0);
                        
                        //  缩放card
                        scaleCardSprite(1.1f, x, y);
                        
                        //  更新得分
                        updateScore(cardArray[x][y]->getNumber());
                        
                        isdo = true;
                    }
                    break;
                }
            }
            
        }
    }
    
    return isdo;
}

bool HelloWorld::doRight()
{
    log("doRight");

    bool isdo = false;
    for (int y=0; y<4; y++) {
        for (int x=3; x>=0; x--) {
            
            for (int x1=x-1; x1>=0; x1--) {
                if (cardArray[x1][y]->getNumber() > 0) {
                    if (cardArray[x][y]->getNumber() <= 0) {
                        cardArray[x][y]->setNumber(cardArray[x1][y]->getNumber());
                        cardArray[x1][y]->setNumber(0);
                        
                        x++;
                        isdo = true;
                    }
                    else if (cardArray[x][y]->getNumber() == cardArray[x1][y]->getNumber()) {
                        cardArray[x][y]->setNumber(cardArray[x][y]->getNumber()*2);
                        cardArray[x1][y]->setNumber(0);

                        //  缩放card
                        scaleCardSprite(1.1f, x, y);
                        
                        //  更新得分
                        updateScore(cardArray[x][y]->getNumber());
                        
                        isdo = true;
                    }
                    
                    break;
                }
            }
        }
    }
    
    return isdo;
}

bool HelloWorld::doUp()
{
    log("doUp");

    bool isdo = false;
    
    for (int x=0; x<4; x++) {
        for (int y=3; y>=0; y--) {
            
            for (int y1=y-1; y1>=0; y1--) {
                if (cardArray[x][y1]->getNumber() > 0) {
                    if (cardArray[x][y]->getNumber() <= 0) {
                        cardArray[x][y]->setNumber(cardArray[x][y1]->getNumber());
                        cardArray[x][y1]->setNumber(0);
                        
                        y++;
                        isdo = true;
                    }
                    else if (cardArray[x][y]->getNumber() == cardArray[x][y1]->getNumber()) {
                        cardArray[x][y]->setNumber(cardArray[x][y]->getNumber()*2);
                        cardArray[x][y1]->setNumber(0);
                        
                        //  缩放card
                        scaleCardSprite(1.1f, x, y);
                        
                        //  更新得分
                        updateScore(cardArray[x][y]->getNumber());
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isdo;
}

bool HelloWorld::doDown()
{
    log("doDown");

    bool isdo = false;
    
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            
            for (int y1=y+1; y1<4; y1++) {
                if (cardArray[x][y1]->getNumber() > 0) {
                    if (cardArray[x][y]->getNumber() <= 0) {
                        cardArray[x][y]->setNumber(cardArray[x][y1]->getNumber());
                        cardArray[x][y1]->setNumber(0);
                        
                        y--;
                        isdo = true;
                    }
                    else if(cardArray[x][y1]->getNumber() == cardArray[x][y]->getNumber()) {
                        cardArray[x][y]->setNumber(cardArray[x][y]->getNumber()*2);
                        cardArray[x][y1]->setNumber(0);
                        
                        //  缩放card
                        scaleCardSprite(1.1f, x, y);
                        
                        //  更新得分
                        updateScore(cardArray[x][y]->getNumber());
                        
                        isdo = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isdo;
}

void HelloWorld::createCardSprite(cocos2d::Size size)
{
    int unitSize = (size.width-48)/4;
    
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            CardSprite* card = CardSprite::createCardSprite(0, unitSize, unitSize);
            cardArray[i][j] = card;
            cardArray[i][j]->setPosition(Point(unitSize*i+30+unitSize*0.5, unitSize*j+180+unitSize*0.5));
            this->addChild(card);
        }
    }
    
}

void HelloWorld::autoCreateCardNumber()
{
    int i = arc4random()%4;
    int j = arc4random()%4;
    
    if(cardArray[i][j]->getNumber() > 0) {
        autoCreateCardNumber();
    }
    else {
        cardArray[i][j]->setNumber(arc4random()%10<5 ? 2 : 4);
    }
}

void HelloWorld::doCheckGameOver()
{
    bool isGameOver = true;
    
    for(int y=0; y<4; y++)
    {
        for (int x=0; x<4; x++) {
            if (cardArray[x][y]->getNumber() == 0 ||
                (x>0&&(cardArray[x][y]->getNumber() == cardArray[x-1][y]->getNumber())) ||
                (x<3&&(cardArray[x][y]->getNumber() == cardArray[x+1][y]->getNumber())) ||
                (y>0&&(cardArray[x][y]->getNumber() == cardArray[x][y-1]->getNumber())) ||
                (y<3&&(cardArray[x][y]->getNumber() == cardArray[x][y+1]->getNumber()))) {
                isGameOver = false;
                return;
            }
        }
    }
    
    if (isGameOver) {
        log("game over");
        Director::getInstance()->replaceScene(TransitionFade::create(1, HelloWorld::createScene()));
    }
}

bool HelloWorld::canAddNewCardNumber()
{
    for (int y=0; y<4; y++) {
        for (int x=0; x<4; x++) {
            if (cardArray[x][y]->getNumber() ==0) {
                return true;
            }
        }
    }
    return false;
}

void HelloWorld::updateScore(int newScore)
{
    score += newScore;
    labelTTFCardNumber->setString(String::createWithFormat("%i", score)->getCString());
}

void HelloWorld::scaleCardSprite(float s, int x, int y)
{
    auto actionBy = ScaleBy::create(0.1f, s, s);
    cardArray[x][y]->runAction(Sequence::create(actionBy, actionBy->reverse(), NULL));
    
    Point p = cardArray[0][0]->getPosition();
    Point ap = cardArray[0][0]->getAnchorPoint();
    log("point0.x = %f, point0.y = %f, anchor point0.x = %f, anchor point0.y = %f", p.x, p.y, ap.x, ap.y);

    p = cardArray[x][y]->getPosition();
    ap = cardArray[x][y]->getAnchorPoint();
    log("point.x = %f, point.y = %f, anchor point.x = %f, anchor point.y = %f", p.x, p.y, ap.x, ap.y);
}












