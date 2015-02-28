//
//  RouteNavigation.h
//  richer
//
//  Created by Li Jun on 2/27/15.
//
//

#ifndef __richer__RouteNavigation__
#define __richer__RouteNavigation__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class RouteNavigation
{
public:
    static RouteNavigation* getInstance();
    void getPath(Sprite* sprite, int stepsCount, bool** canPassGrid, int gridRowsCount, int gridColsCount);

    enum class Direction
    {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3
    };

private:
    RouteNavigation();
    ~RouteNavigation();
    
    bool isCanGoByRowCol(int row, int col, Direction direction, bool** canPassGrid);
    
    CC_SYNTHESIZE(std::vector<int>, _pathRowsVector, PathRowsVector);
    CC_SYNTHESIZE(std::vector<int>, _pathColsVector, PathColsVector);
    
    static RouteNavigation* _instance;
};

#endif /* defined(__richer__RouteNavigation__) */
