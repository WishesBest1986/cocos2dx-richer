//
//  MapChooseLayer.h
//  richer
//
//  Created by Li Jun on 2/26/15.
//
//

#ifndef __richer__MapChooseLayer__
#define __richer__MapChooseLayer__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "ConstUtil.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int kValidMoveDistance = 200;
const int kTagBeachSprite = 10001;
const int kTagSeaSprite = 10002;
const int kTagMoonSprite = 10003;

class MapChooseLayer : public Layer, public ScrollViewDelegate
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MapChooseLayer);
    
    enum class MoveDirection
    {
        NONE = -1,
        LEFT = 0,
        RIGHT
    };
    
private:
    void singleTouchDown(Ref* pSender, Control::EventType event);
    void addBackgroundSprite();
    void addScrollView();
    
    void scrollViewDidScroll(ScrollView* view);
    void scrollViewDidZoom(ScrollView* view);
    void adjustScrollView(MoveDirection direction);
    bool onTouchBegan(Touch* touch, Event *unused_event);
    void onTouchMoved(Touch* touch, Event *unused_event);
    void onTouchCancelled(Touch* touch, Event *unused_event);
    void onTouchEnded(Touch* touch, Event *unused_event);
    
private:
    Size        _sizeVisible;
    Layer       *_spritesContainer;
    int         _currentPage;
    Point       _beginTouchPoint;
    ScrollView  *_scrollView;
};


#endif /* defined(__richer__MapChooseLayer__) */
