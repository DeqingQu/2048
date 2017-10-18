//
//  CardSprite.h
//  2048
//
//  Created by Alex on 14-6-27.
//
//

#ifndef _2048_CardSprite_h
#define _2048_CardSprite_h

#include "cocos2d.h"

class CardSprite : public cocos2d::Sprite
{
public:
    static CardSprite* createCardSprite(int numbers,int width,int height);
    virtual bool init();
    CREATE_FUNC(CardSprite);
    
    int getNumber();
    void setNumber(int num);

private:
    int number;
    cocos2d::Label* labelTTFCardNumber;
    cocos2d::LayerColor* layerColorBG;
    
    void enemyInit(int numbers, int width, int height);
};


#endif
