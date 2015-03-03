//
//  RicherGameController.h
//  richer
//
//  Created by Li Jun on 2/28/15.
//
//

#ifndef __richer__RicherGameController__
#define __richer__RicherGameController__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include "RicherPlayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

const float kPlayerGoTotalTime = 0.28f;
const float kPlayerGoPerFrame = 0.07f;

class RicherGameController : public Layer
{
public:
    static RicherGameController* getInstance();
    virtual bool init();
    CREATE_FUNC(RicherGameController);
    
    void startRealGo(std::vector<int> rowVector, std::vector<int> colVector, RicherPlayer *player);
    void endGo();
    
private:
    RicherGameController();
    ~RicherGameController();
    
    void moveOneStep(RicherPlayer *player);
    
    static RicherGameController* _instance;
    
    int     _stepHasGone;
    int     _stepsCount;
    
    int     _currentRow;
    int     _currentCol;
    int     _nextRow;
    int     _nextCol;
    
    std::vector<int>    _rowVector;
    std::vector<int>    _colVector;
    RicherPlayer        *_player;
    
    CallFunc            *_endGoCallFunc;
};

#endif /* defined(__richer__RicherGameController__) */
