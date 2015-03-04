//
//  RicherGameController.cpp
//  richer
//
//  Created by Li Jun on 2/28/15.
//
//

#include "RicherGameController.h"
#include "GameBaseLayer.h"

RicherGameController* RicherGameController::_instance = NULL;

RicherGameController::RicherGameController()
{
    
}

RicherGameController::~RicherGameController()
{
    CC_SAFE_RELEASE(_endGoCallFunc);
}

RicherGameController* RicherGameController::getInstance()
{
    if (!_instance) {
        _instance = RicherGameController::create();
    }
    _instance->retain();
    return _instance;
}

bool RicherGameController::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    _endGoCallFunc = CallFunc::create(CC_CALLBACK_0(RicherGameController::endGo, this));
    _endGoCallFunc->retain();
    
    return true;
}

void RicherGameController::startRealGo(std::vector<int> rowVector, std::vector<int> colVector, RicherPlayer *player)
{
    _currentRow = rowVector[0];
    _currentCol = colVector[0];
    
    _nextRow = 0;
    _nextCol = 0;
    
    _rowVector = rowVector;
    _colVector = colVector;
    _player = player;
    
    _stepHasGone = 0;
    _stepsCount = _rowVector.size() - 1;
    
    moveOneStep(_player);
}

void RicherGameController::moveOneStep(RicherPlayer *player)
{
    _nextRow = _rowVector[_stepHasGone + 1];
    _nextCol = _colVector[_stepHasGone + 1];
    int distanceRow = _nextRow - _currentRow;
    int distanceCol = _nextCol - _currentCol;
    
    MoveBy *moveBy;
    Repeat *repeat;
    
    if (distanceRow > 0) {
        moveBy = MoveBy::create(kPlayerGoTotalTime, Vec2(0, kTiledHeight));
        repeat = Repeat::create(player->getUpAnimate(), 1);
    }
    if (distanceRow < 0) {
        moveBy = MoveBy::create(kPlayerGoTotalTime, Vec2(0, -1 * kTiledHeight));
        repeat = Repeat::create(player->getDownAnimate(), 1);
    }
    if (distanceCol > 0) {
        moveBy = MoveBy::create(kPlayerGoTotalTime, Vec2(kTiledWidth, 0));
        repeat = Repeat::create(player->getRightAnimate(), 1);
    }
    if (distanceCol < 0) {
        moveBy = MoveBy::create(kPlayerGoTotalTime, Vec2(-1 * kTiledWidth, 0));
        repeat = Repeat::create(player->getLeftAnimate(), 1);
    }
    
    auto spawnAction = Sequence::create(Spawn::create(moveBy, repeat, NULL), _endGoCallFunc, NULL);
    player->runAction(spawnAction);
}

void RicherGameController::endGo()
{
    _stepHasGone ++;
    
    if (_stepHasGone >= _stepsCount) {
        return;
    }
    
    _currentRow = _nextRow;
    _currentCol = _nextCol;
    
    moveOneStep(_player);
}
