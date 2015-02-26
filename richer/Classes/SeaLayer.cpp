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