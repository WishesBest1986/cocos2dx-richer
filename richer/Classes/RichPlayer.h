//
//  RichPlayer.h
//  richer
//
//  Created by Li Jun on 2/27/15.
//
//

#ifndef __richer__RichPlayer__
#define __richer__RichPlayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RichPlayer : public Sprite
{
public:
    RichPlayer();
    ~RichPlayer();
    
    static RichPlayer* create(std::string name, int tag, bool enemy, int money = 50000, int strength = 100);
    bool init(std::string name, int tag, bool enemy, int money, int strength);
    
    void startGo(std::vector<int> rowVector, std::vector<int> colVector);
    
private:
    void addPlayerAnimation();
    
public:
    CC_SYNTHESIZE(Vector<SpriteFrame*>, _animLeftVector, AnimLeftVector);
    CC_SYNTHESIZE(Vector<SpriteFrame*>, _animRightVector, AnimRightVector);
    CC_SYNTHESIZE(Vector<SpriteFrame*>, _animUpVector, AnimUpVector);
    CC_SYNTHESIZE(Vector<SpriteFrame*>, _animDownVector, AnimDownVector);
    
    CC_SYNTHESIZE(Animate*, _leftAnimate, LeftAnimate);
    CC_SYNTHESIZE(Animate*, _rightAnimate, RightAnimate);
    CC_SYNTHESIZE(Animate*, _upAnimate, UpAnimate);
    CC_SYNTHESIZE(Animate*, _downAnimate, DownAnimate);
    
private:
    SpriteFrameCache    *_spriteFrameCache;
    
    CC_SYNTHESIZE(std::string, _name, Name);
    CC_SYNTHESIZE(int, _money, Money);
    CC_SYNTHESIZE(int, _strength, Strength);
    CC_SYNTHESIZE(bool, _enemy, Enemy);
    
    CC_SYNTHESIZE(int, _comeFromRow, ComeFromRow);
    CC_SYNTHESIZE(int, _comeFromCol, ComeFromCol);
};

#endif /* defined(__richer__RichPlayer__) */
