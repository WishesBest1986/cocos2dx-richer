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
    
    char leftAnimationName[20];
    memset(leftAnimationName, 0, sizeof(char) * 20);
    sprintf(leftAnimationName, "left_animation_%d", _tag);
    
    char rightAnimationName[20];
    memset(rightAnimationName, 0, sizeof(char) * 20);
    sprintf(rightAnimationName, "right_animation_%d", _tag);
    
    char upAnimationName[20];
    memset(upAnimationName, 0, sizeof(char) * 20);
    sprintf(upAnimationName, "up_animation_%d", _tag);
    
    char downAnimationName[20];
    memset(downAnimationName, 0, sizeof(char) * 20);
    sprintf(downAnimationName, "down_animation_%d", _tag);
    
    auto animationCache = AnimationCache::getInstance();
    if ( !animationCache->getAnimation(leftAnimationName) ) {
        animationCache->addAnimation(Animation::createWithSpriteFrames(_animLeftVector, kPlayerGoPerFrame), leftAnimationName);
    }
    if ( !animationCache->getAnimation(rightAnimationName) ) {
        animationCache->addAnimation(Animation::createWithSpriteFrames(_animRightVector, kPlayerGoPerFrame), rightAnimationName);
    }
    if ( !animationCache->getAnimation(upAnimationName) ) {
        animationCache->addAnimation(Animation::createWithSpriteFrames(_animUpVector, kPlayerGoPerFrame), upAnimationName);
    }
    if ( !animationCache->getAnimation(downAnimationName) ) {
        animationCache->addAnimation(Animation::createWithSpriteFrames(_animDownVector, kPlayerGoPerFrame), downAnimationName);
    }
    
    _leftAnimate = Animate::create(animationCache->getAnimation(leftAnimationName));
    _rightAnimate = Animate::create(animationCache->getAnimation(rightAnimationName));
    _upAnimate = Animate::create(animationCache->getAnimation(upAnimationName));
    _downAnimate = Animate::create(animationCache->getAnimation(downAnimationName));
    
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