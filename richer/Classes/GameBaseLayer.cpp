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
    auto rightBanner = Sprite::create(IMAGE_RIGHT_BANNER);
    rightBanner->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    rightBanner->setPosition(Vec2(kTableStartPositionX, 0));
    addChild(rightBanner);
}

void GameBaseLayer::drawTable(int playerNumber)
{
    auto winSize = Director::getInstance()->getWinSize();
    
    auto drawNode = DrawNode::create();
    this->addChild(drawNode);
    
    for (int i = 0; i < playerNumber; i ++) {
        drawNode->drawSegment(Vec2(kTableStartPositionX, kTableStartPositionY - 2 * i * kTableHeight), Vec2(kTableStartPositionX + 3 * kTableWidth, kTableStartPositionY - 2 * i * kTableHeight), 1, Color4F(0, 1, 0, 1));
        drawNode->drawSegment(Vec2(kTableStartPositionX, kTableStartPositionY - 2 * (i + 1) * kTableHeight), Vec2(kTableStartPositionX + 3 * kTableWidth, kTableStartPositionY - 2 * (i + 1) * kTableHeight), 1, Color4F(0, 1, 0, 1));
        drawNode->drawSegment(Vec2(kTableStartPositionX + kTableWidth, kTableStartPositionY - kTableHeight - 2 * i * kTableHeight), Vec2(kTableStartPositionX + 3 * kTableWidth, kTableStartPositionY - kTableHeight - 2 * i * kTableHeight), 1, Color4F(0, 1, 0, 1));
        drawNode->drawSegment(Vec2(kTableStartPositionX + kTableWidth, kTableStartPositionY - 2 * i * kTableHeight), Vec2(kTableStartPositionX + kTableWidth, kTableStartPositionY - 2 * kTableHeight - 2 * i * kTableHeight), 1, Color4F(0, 1, 0, 1));
    }
}

void GameBaseLayer::addPlayer()
{
    
}