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
#include "RicherPlayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int kPlayerNumber = 2;
const int kTableWidth = 50;
const int kTableHeight = 40;
const int kTableStartPositionX = 650;
const int kTableStartPositionY = 450;

const int kTiledWidth = 32;
const int kTiledHeight = 32;

class GameBaseLayer : public Layer
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameBaseLayer);
    void onExit();
    
    RicherPlayer        *_player1;
    RicherPlayer        *_player2;
    
protected:
    virtual void addMap();
    virtual void initTiledGrid();
    
    TMXTiledMap         *_map;
    int                 _tiledColsCount;
    int                 _tiledRowsCount;
    bool                **_canPassGrid;
    
    std::vector<Vec2>   _wayLayerPassVector;
    
private:
    void drawTable();
    void addPlayer();
    void addPlayerInfo();
    void addRightBanner();
    void setWayPassToGrid();
    void addGoButton();
    
    void goButtonCallback(Ref* pSender);
};

#endif /* defined(__richer__GameBaseLayer__) */
