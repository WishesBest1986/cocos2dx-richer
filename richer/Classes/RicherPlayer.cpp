//
//  RicherPlayer.cpp
//  richer
//
//  Created by Li Jun on 2/27/15.
//
//

#include "RicherPlayer.h"
#include "RicherGameController.h"

RicherPlayer::RicherPlayer()
{
    _comeFromRow = -1;
    _comeFromCol = -1;
}

RicherPlayer::~RicherPlayer()
{
    CC_SAFE_RELEASE(_leftAnimate);
    CC_SAFE_RELEASE(_rightAnimate);
    CC_SAFE_RELEASE(_upAnimate);
    CC_SAFE_RELEASE(_downAnimate);
}

RicherPlayer* RicherPlayer::create(std::string name, int tag, bool enemy, int money, int strength)
{
    RicherPlayer *player = new RicherPlayer();
    player->init(name, tag, enemy, money, strength);
    player->autorelease();
    return player;
}

bool RicherPlayer::init(std::string name, int tag, bool enemy, int money, int strength)
{
    this->setTag(tag);
    addPlayerAnimation();
    char fileName[20];
    memset(fileName, 0, sizeof(char) * 20);
    sprintf(fileName, IMAGE_PLAYER_X_ANIM_Y, tag, 1);
    auto spriteFrame = _spriteFrameCache->getSpriteFrameByName(fileName);
    
    if ( !Sprite::initWithSpriteFrame(spriteFrame) ) {
        return false;
    }
    
    _name = name;
    _enemy = enemy;
    _money = money;
    _strength = strength;
    
    return true;
}

void RicherPlayer::addPlayerAnimation()
{
    _spriteFrameCache = SpriteFrameCache::getInstance();
    
    char plistFileName[20];
    memset(plistFileName, 0, sizeof(char) * 20);
    sprintf(plistFileName, IMAGE_PLIST_PLAYER_ANIM_X, _tag);
    
    char pngFileName[20];
    memset(pngFileName, 0, sizeof(char) * 20);
    sprintf(pngFileName, IMAGE_PNG_PLAYER_ANIM_X, _tag);
    
    _spriteFrameCache->addSpriteFramesWithFile(plistFileName, pngFileName);
    
    char name[20];
    memset(name, 0, sizeof(char) * 20);
    
    for (int i = 1; i <= 4; i ++) {
        sprintf(name, IMAGE_PLAYER_X_ANIM_Y, _tag, i);
        _animLeftVector.pushBack(_spriteFrameCache->getSpriteFrameByName(name));
    }
    for (int i = 5; i <= 8; i ++) {
        sprintf(name, IMAGE_PLAYER_X_ANIM_Y, _tag, i);
        _animRightVector.pushBack(_spriteFrameCache->getSpriteFrameByName(name));
    }
    for (int i = 9; i <= 12; i ++) {
        sprintf(name, IMAGE_PLAYER_X_ANIM_Y, _tag, i);
        _animDownVector.pushBack(_spriteFrameCache->getSpriteFrameByName(name));
    }
    for (int i = 13; i <= 16; i ++) {
        sprintf(name, IMAGE_PLAYER_X_ANIM_Y, _tag, i);
        _animUpVector.pushBack(_spriteFrameCache->getSpriteFrameByName(name));
    }
    
    _leftAnimate = Animate::create(Animation::createWithSpriteFrames(_animLeftVector, 0.1));
    _rightAnimate = Animate::create(Animation::createWithSpriteFrames(_animRightVector, 0.1));
    _upAnimate = Animate::create(Animation::createWithSpriteFrames(_animUpVector, 0.1));
    _downAnimate = Animate::create(Animation::createWithSpriteFrames(_animDownVector, 0.1));
    
    _leftAnimate->retain();
    _rightAnimate->retain();
    _upAnimate->retain();
    _downAnimate->retain();
}

void RicherPlayer::startGo(std::vector<int> rowVector, std::vector<int> colVector)
{
    auto controller = RicherGameController::getInstance();
    controller->startRealGo(rowVector, colVector, this);
}