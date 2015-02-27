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
    drawTable();
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

void GameBaseLayer::drawTable()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    auto drawNode = DrawNode::create();
    this->addChild(drawNode);
    
    for (int i = 0; i < kPlayerNumber; i ++) {
        drawNode->drawSegment(Vec2(kTableStartPositionX, kTableStartPositionY - 2 * i * kTableHeight), Vec2(kTableStartPositionX + 3 * kTableWidth, kTableStartPositionY - 2 * i * kTableHeight), 1, Color4F(0, 1, 0, 1));
        drawNode->drawSegment(Vec2(kTableStartPositionX, kTableStartPositionY - 2 * (i + 1) * kTableHeight), Vec2(kTableStartPositionX + 3 * kTableWidth, kTableStartPositionY - 2 * (i + 1) * kTableHeight), 1, Color4F(0, 1, 0, 1));
        drawNode->drawSegment(Vec2(kTableStartPositionX + kTableWidth, kTableStartPositionY - kTableHeight - 2 * i * kTableHeight), Vec2(kTableStartPositionX + 3 * kTableWidth, kTableStartPositionY - kTableHeight - 2 * i * kTableHeight), 1, Color4F(0, 1, 0, 1));
        drawNode->drawSegment(Vec2(kTableStartPositionX + kTableWidth, kTableStartPositionY - 2 * i * kTableHeight), Vec2(kTableStartPositionX + kTableWidth, kTableStartPositionY - 2 * kTableHeight - 2 * i * kTableHeight), 1, Color4F(0, 1, 0, 1));
    }
}

std::string jointPlayerImage(std::string prefix, int index, std::string suffix)
{
    std::stringstream stream;
    stream << prefix << index << suffix;
    return stream.str();
}

void GameBaseLayer::addPlayer()
{
    for (int i = 0; i < kPlayerNumber; i ++) {
        auto player = Sprite::create(jointPlayerImage(IMAGE_PLAYER_PREFIX, (i + 1), IMAGE_PLAYER_SUFFIX));
        player->setPosition(Vec2(kTableStartPositionX + kTableWidth / 2.0, kTableStartPositionY - (i * 2 + 1) * kTableHeight));
        addChild(player);
        
        auto playerMoney = LabelTTF::create();
        playerMoney->setString("$");
        playerMoney->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        playerMoney->setFontSize(25);
        playerMoney->setPosition(Vec2(kTableStartPositionX + kTableWidth, kTableStartPositionY - (i * 4 + 1) * kTableHeight / 2.0));
        addChild(playerMoney);
        
        auto playerStrength = LabelTTF::create();
        playerStrength->setString("+");
        playerStrength->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        playerStrength->setFontSize(28);
        playerStrength->setPosition(Vec2(kTableStartPositionX + kTableWidth, kTableStartPositionY - (i * 4 + 3) * kTableHeight / 2.0));
        addChild(playerStrength);
    }
}