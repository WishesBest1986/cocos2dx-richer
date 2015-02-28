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
    struct timeval now;
    gettimeofday(&now, NULL);
    unsigned randSeed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
    srand(randSeed);
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
    for (int i = 0; i < gridRowsCount; i ++) {
        canPassGridCopy[i] = new bool[gridColsCount];
    }
    
    for (int row = 0; row < gridRowsCount; row ++) {
        for (int col = 0; col < gridColsCount; col ++) {
            canPassGridCopy[row][col] = canPassGrid[row][col];
        }
    }
    
    std::vector<bool> direction4;
    std::vector<int> canPassDirVector;
    
    int hasGoneNumber = 0;
    while (hasGoneNumber < stepsCount) {
        direction4.clear();
        for (int i = 0; i < 4; i ++) {
            direction4.push_back(false);
        }
        
        canPassDirVector.clear();
        direction4[(int) Direction::UP] = isCanGoByRowCol(currentRow, currentCol, Direction::UP, canPassGridCopy);
        direction4[(int) Direction::DOWN] = isCanGoByRowCol(currentRow, currentCol, Direction::DOWN, canPassGrid);
        direction4[(int) Direction::LEFT] = isCanGoByRowCol(currentRow, currentCol, Direction::LEFT, canPassGrid);
        direction4[(int) Direction::RIGHT] = isCanGoByRowCol(currentRow, currentCol, Direction::RIGHT, canPassGrid);
        
        
        for (int i = 0; i < direction4.size(); i ++) {
            if (direction4[i]) {
                canPassDirVector.push_back(i);
            }
        }
        
        if (canPassDirVector.size() == 0)
            return;
        
        int randNum = rand() % (canPassDirVector.size());
        switch (Direction(canPassDirVector[randNum])) {
            case Direction::UP:
                nextRow = currentRow - 1;
                nextCol = currentCol;
                break;
                
            case Direction::DOWN:
                nextRow = currentRow + 1;
                nextCol = currentCol;
                break;
                
            case Direction::LEFT:
                nextRow = currentRow;
                nextCol = currentCol - 1;
                break;
                
            case Direction::RIGHT:
                nextRow = currentRow;
                nextCol = currentCol + 1;
                break;
                
            default:
                break;
        }
        
        _pathRowsVector.push_back(nextRow);
        _pathColsVector.push_back(nextCol);
        
        canPassGridCopy[currentRow][currentCol] = false;
        currentRow = nextRow;
        currentCol = nextCol;
        
        hasGoneNumber ++;
    }

    for (int i = 0; i  < gridRowsCount; i ++) {
        CC_SAFE_DELETE_ARRAY(canPassGridCopy[i]);
    }
    CC_SAFE_DELETE_ARRAY(canPassGridCopy);
    
    direction4.clear();
    canPassDirVector.clear();
    std::vector<bool>(direction4).swap(direction4);
    std::vector<int>(canPassDirVector).swap(canPassDirVector);
}

bool RouteNavigation::isCanGoByRowCol(int row, int col, RouteNavigation::Direction direction, bool **canPassGrid)
{
    bool result = false;
    switch (direction) {
        case Direction::UP:
            result = canPassGrid[row - 1][col];
            break;
        case Direction::DOWN:
            result = canPassGrid[row + 1][col];
            break;
        case Direction::LEFT:
            result = canPassGrid[row][col - 1];
            break;
        case Direction::RIGHT:
            result = canPassGrid[row][col + 1];
            break;
        default:
            break;
    }
    return result;
}
