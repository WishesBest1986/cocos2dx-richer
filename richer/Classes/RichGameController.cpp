//
//  RichGameController.cpp
//  richer
//
//  Created by Li Jun on 2/28/15.
//
//

#include "RichGameController.h"
#include "GameBaseLayer.h"

RichGameController* RichGameController::_instance = NULL;

RichGameController::RichGameController()
{
    
}

RichGameController::~RichGameController()
{
    
}

RichGameController* RichGameController::getInstance()
{
    if (!_instance) {
        _instance = RichGameController::create();
    }
    _instance->retain();
    return _instance;
}

bool RichGameController::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    _endGoCallFunc = CallFunc::create(CC_CALLBACK_0(RichGameController::endGo, this));
    
    return true;
}

void RichGameController::startRealGo(std::vector<int> rowVector, std::vector<int> colVector, RichPlayer *player)
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

void RichGameController::moveOneStep(RichPlayer *player)
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
        repeat = Repeat::create(player->getDownAnimate(), 1);
    }
    if (distanceCol < 0) {
        moveBy = MoveBy::create(kPlayerGoTotalTime, Vec2(-1 * kTiledWidth, 0));
        repeat = Repeat::create(player->getDownAnimate(), 1);
    }
    
    auto spawnAction = Sequence::create(Spawn::create(moveBy, repeat, NULL), _endGoCallFunc, NULL);
    player->runAction(spawnAction);
}

void RichGameController::endGo()
{
    _stepHasGone ++;
    
    if (_stepHasGone >= _stepsCount) {
        return;
    }
    
    _currentRow = _nextRow;
    _currentCol = _nextCol;
    
    moveOneStep(_player);
}
