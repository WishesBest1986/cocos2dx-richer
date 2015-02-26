//
//  GameBaseLayer.cpp
//  richer
//
//  Created by Li Jun on 2/26/15.
//
//

#include "GameBaseLayer.h"

Scene* GameBaseLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = GameBaseLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameBaseLayer::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    addMap();
    addRightBanner();
    drawTable(2);
    addPlayer();
    
    return true;
}

void GameBaseLayer::addRightBanner()
{
    
}

void GameBaseLayer::drawTable(int playerNumber)
{
    
}

void GameBaseLayer::addPlayer()
{
    
}