//
//  RichGameController.h
//  richer
//
//  Created by Li Jun on 2/28/15.
//
//

#ifndef __richer__RichGameController__
#define __richer__RichGameController__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"
#include "RichPlayer.h"

USING_NS_CC;
USING_NS_CC_EXT;

const float kPlayerGoTotalTime = 0.28f;
const float kPlayerGoPerFrame = 0.07f;

class RichGameController : public Layer
{
public:
    static RichGameController* getInstance();
    virtual bool init();
    CREATE_FUNC(RichGameController);
    
    void startRealGo(std::vector<int> rowVector, std::vector<int> colVector, RichPlayer *player);
    void endGo();
    
private:
    RichGameController();
    ~RichGameController();
    
    void moveOneStep(RichPlayer *player);
    
    static RichGameController* _instance;
    
    int     _stepHasGone;
    int     _stepsCount;
    
    int     _currentRow;
    int     _currentCol;
    int     _nextRow;
    int     _nextCol;
    
    std::vector<int>    _rowVector;
    std::vector<int>    _colVector;
    RichPlayer          *_player;
    
    CallFunc            *_endGoCallFunc;
};

#endif /* defined(__richer__RichGameController__) */
