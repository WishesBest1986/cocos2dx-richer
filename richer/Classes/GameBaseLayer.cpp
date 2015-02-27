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
    
    addGoButton();
    initTiledGrid();
    setWayPassToGrid();
    
    addPlayer();

    return true;
}

void GameBaseLayer::addRightBanner()
{
    auto rightBanner = Sprite::create(IMAGE_RIGHT_BANNER);
    rightBanner->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    rightBanner->setPosition(Vec2(kTableStartPositionX - 10, 0));
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

//std::string jointPlayerImage(std::string prefix, int index, std::string suffix)
//{
//    std::stringstream stream;
//    stream << prefix << index << suffix;
//    return stream.str();
//}

void GameBaseLayer::addPlayer()
{
    addPlayerInfo();
    
    struct timeval now;
    gettimeofday(&now, NULL);
    unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
    srand(rand_seed);
    
    _player1 = RichPlayer::create(STR_PLAYER_1_NAME, TAG_PLAYER_1, false);
    int rand1 = rand() % (_wayLayerPassVector.size());
    auto vec2ForPlayer1 = _wayLayerPassVector.at(rand1);
    vec2ForPlayer1.y += kTiledHeight;
    _player1->setPosition(vec2ForPlayer1);
    _player1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(_player1);
    
    _player2 = RichPlayer::create(STR_PLAYER_2_NAME, TAG_PLAYER_2, false);
    int rand2 = rand() % (_wayLayerPassVector.size());
    auto vec2ForPlayer2 = _wayLayerPassVector.at(rand2);
    vec2ForPlayer2.y += kTiledHeight;
    _player2->setPosition(vec2ForPlayer2);
    _player2->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    addChild(_player2);
}

void GameBaseLayer::addPlayerInfo()
{
    for (int i = 0; i < kPlayerNumber; i ++) {
        char fileName[20];
        memset(fileName, 0, sizeof(char) * 20);
        sprintf(fileName, IMAGE_PLAYER_X, (i + 1));
        
        auto player = Sprite::create(fileName);
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

void GameBaseLayer::addGoButton()
{
    auto menu = Menu::create();
    menu->setPosition(Vec2::ZERO);
    
    auto goMenuItemButton = MenuItemImage::create(IMAGE_GO_BUTTON_NORMAL, IMAGE_GO_BUTTON_PRESS);
    goMenuItemButton->setPosition(Vec2(kTableStartPositionX + 2 * kTableWidth, kTableStartPositionY - kTableHeight * 6));
    goMenuItemButton->setCallback(std::bind(menu_selector(GameBaseLayer::goButtonCallback), this, std::placeholders::_1));
    menu->addChild(goMenuItemButton);
    
    addChild(menu);
}

void GameBaseLayer::goButtonCallback(cocos2d::Ref *pSender)
{
    log("go clicked");
}

void GameBaseLayer::setWayPassToGrid()
{
    auto wayLayer = _map->getLayer("way");
    auto mapSize = wayLayer->getLayerSize();
    
    for (int i = 0; i < mapSize.width; i ++) {
        for (int j = 0; j < mapSize.height; j ++) {
            auto sprite = wayLayer->getTileAt(Point(i, j));
            if ( sprite ) {
                auto x = sprite->getPositionX();
                auto y = sprite->getPositionY();
                int col = x / kTiledWidth;
                int row = y / kTiledHeight;
                _canPassGrid[row][col] = true;
                
                _wayLayerPassVector.push_back(sprite->getPosition());
                
                log("canPassGrid row = %d, col= %d, canpass = %d", row, col, _canPassGrid[row][col]);
            }
        }
    }
}

void GameBaseLayer::onExit()
{
    for (int i = 0; i  < _tiledRowsCount; i ++) {
        CC_SAFE_DELETE_ARRAY(_canPassGrid[i]);
    }
    CC_SAFE_DELETE_ARRAY(_canPassGrid);
    
    Layer::onExit();
}
