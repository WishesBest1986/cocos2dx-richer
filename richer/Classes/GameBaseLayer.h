//
//  GameBaseLayer.h
//  richer
//
//  Created by Li Jun on 2/26/15.
//
//

#ifndef __richer__GameBaseLayer__
#define __richer__GameBaseLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int kTableWidth = 50;
const int kTableHeight = 40;
const int kTableStartPositionX = 650;
const int kTableStartPositionY = 450;

class GameBaseLayer : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameBaseLayer);
    
    
protected:
    virtual void addMap();

    TMXTiledMap     *_map;
    
private:
    void drawTable(int playerNumber);
    void addPlayer();
    void addRightBanner();
};

#endif /* defined(__richer__GameBaseLayer__) */
