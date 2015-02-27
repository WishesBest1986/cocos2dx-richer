//
//  SeaLayer.cpp
//  richer
//
//  Created by Li Jun on 2/26/15.
//
//

#include "SeaLayer.h"

Scene* SeaLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = SeaLayer::create();
    scene->addChild(layer);
    return scene;
}

bool SeaLayer::init()
{
    if ( !GameBaseLayer::init() ) {
        return false;
    }
    
    return true;
}

void GameBaseLayer::addMap()
{
    _map = TMXTiledMap::create("sea.tmx");
    addChild(_map);
}

void GameBaseLayer::initTiledGrid()
{
    _tiledColsCount = 20;
    _tiledRowsCount = 15;
    
    _canPassGrid = new bool*[_tiledRowsCount];
    for (int i = 0; i < _tiledRowsCount; i ++) {
        _canPassGrid[i] = new bool[_tiledColsCount];
    }
    
    for (int row = 0; row < _tiledRowsCount; row ++) {
        for (int col = 0; col < _tiledColsCount; col ++) {
            _canPassGrid[row][col] = false;
        }
    }
}