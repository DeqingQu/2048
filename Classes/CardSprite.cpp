//
//  CardSprite.cpp
//  2048
//
//  Created by Alex on 14-6-27.
//
//

#include "CardSprite.h"

USING_NS_CC;

CardSprite* CardSprite::createCardSprite(int numbers, int width, int height)
{
    CardSprite* enemy = new CardSprite();
    if(enemy && enemy->init())
    {
        enemy->autorelease();
        enemy->enemyInit(numbers, width, height);
        
        return enemy;
    }
    
    CC_SAFE_DELETE(enemy);
    return NULL;
}

bool CardSprite::init()
{
    if(!Sprite::init())
    {
        return false;
    }
    return true;
}

void CardSprite::enemyInit(int numbers, int width, int height)
{
    number = numbers;

    layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(200, 190, 180, 255), width-15, height-15);
    layerColorBG->ignoreAnchorPointForPosition(false);

    if (numbers > 0) {
        labelTTFCardNumber = Label::createWithSystemFont(String::createWithFormat("%i", numbers)->getCString(), "Consolas", 80);
        labelTTFCardNumber->setPosition(layerColorBG->getContentSize().width/2, layerColorBG->getContentSize().height/2);
        layerColorBG->addChild(labelTTFCardNumber);
    }
    else {
        labelTTFCardNumber = Label::createWithSystemFont("","Consolas",80);
        labelTTFCardNumber->setPosition(layerColorBG->getContentSize().width/2, layerColorBG->getContentSize().height/2);

        layerColorBG->addChild(labelTTFCardNumber);
    }
    
    Point p = layerColorBG->getPosition();
    Point ap = layerColorBG->getAnchorPoint();
    log("point.x = %f, point.y = %f, anchor point.x = %f, anchor point.y = %f", p.x, p.y, ap.x, ap.y);
    
    this->addChild(layerColorBG);
}

int CardSprite::getNumber()
{
    return number;
}

void CardSprite::setNumber(int num)
{
    number = num;
    
    if (num >= 0) {
        labelTTFCardNumber->setSystemFontSize(100);
    }
    if (num >= 16) {
        labelTTFCardNumber->setSystemFontSize(90);
    }
    if (num >= 128) {
        labelTTFCardNumber->setSystemFontSize(60);
    }
    if (num >= 1024) {
        labelTTFCardNumber->setSystemFontSize(40);
    }
    
    switch (num) {
        case 0:
            layerColorBG->setColor(cocos2d::Color3B(200, 190, 180));
            break;
        case 2:
            layerColorBG->setColor(cocos2d::Color3B(240,230,220));
            break;
        case 4:
            layerColorBG->setColor(cocos2d::Color3B(240,220,200));
            break;
        case 8:
            layerColorBG->setColor(cocos2d::Color3B(240,180,120));
            break;
        case 16:
            layerColorBG->setColor(cocos2d::Color3B(240,140,90));
            break;
        case 32:
            layerColorBG->setColor(cocos2d::Color3B(240,120,90));
            break;
        case 64:
            layerColorBG->setColor(cocos2d::Color3B(240,90,60));
            break;
        case 128:
            layerColorBG->setColor(cocos2d::Color3B(240,90,60));
            break;
        case 256:
            layerColorBG->setColor(cocos2d::Color3B(240,200,70));
            break;
        case 512:
            layerColorBG->setColor(cocos2d::Color3B(240,200,70));
            break;
        case 1024:
            layerColorBG->setColor(cocos2d::Color3B(0,130,0));
            break;
        case 2048:
            layerColorBG->setColor(cocos2d::Color3B(0,130,0));
            break;
        default:
            break;
    }
    
    
    
    if (num > 0) {
        labelTTFCardNumber->setString(String::createWithFormat("%i", num)->getCString());
    }
    else {
        labelTTFCardNumber->setString("");
    }
}

































