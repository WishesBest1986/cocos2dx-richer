//
//  RouteNavigation.cpp
//  richer
//
//  Created by Li Jun on 2/27/15.
//
//

#include "RouteNavigation.h"
#include "GameBaseLayer.h"

RouteNavigation* RouteNavigation::_instance = NULL;

RouteNavigation::RouteNavigation()
{
    
}

RouteNavigation::~RouteNavigation()
{
    _instance = NULL;
}

RouteNavigation* RouteNavigation::getInstance()
{
    if (!_instance) {
        _instance = new RouteNavigation();
    }
    return _instance;
}

void RouteNavigation::getPath(cocos2d::Sprite *sprite, int stepsCount, bool **canPassGrid, int gridRowsCount, int gridColsCount)
{
    // Clear vector
    _pathRowsVector.clear();
    _pathColsVector.clear();
    
    // define player current & next moment row + col
    int nextRow, nextCol;
    int currentRow, currentCol;
    
    // get player current position
    float x = sprite->getPositionX();
    float y = sprite->getPositionY();
    
    currentCol = x / kTiledWidth;
    // Since we add kTiledHeight in GameBaseLayer::addPlayer(), minus kTiledHeight first
    currentRow = (y - kTiledHeight) / kTiledHeight;
    
    bool **canPassGridCopy = new bool *[gridRowsCount];
    for (int row = 0; row < gridRowsCount; row ++) {
        for (int col = 0; col < gridColsCount; col ++) {
            canPassGridCopy[row][col] = canPassGrid[row][col];
        }
    }
    
    std::vector<bool> direction4;
    std::vector<int> canPassDirVector;
    
    
}