//
//  MapChooseLayer.cpp
//  richer
//
//  Created by Li Jun on 2/26/15.
//
//

#include "MapChooseLayer.h"

Scene* MapChooseLayer::createScene()
{
    auto scene = Scene::create();
    auto layer = MapChooseLayer::create();
    scene->addChild(layer);
    return scene;
}

bool MapChooseLayer::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    _sizeVisible = Director::getInstance()->getVisibleSize();
    _currentPage = 1;
    
    addBackgroundSprite();
    addScrollView();
    
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MapChooseLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MapChooseLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MapChooseLayer::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MapChooseLayer::onTouchCancelled, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

void MapChooseLayer::addBackgroundSprite()
{
    auto stageBg = Sprite::create(IMAGE_STAGE_BACKGROUND);
    stageBg->setPosition(Vec2::ZERO);
    stageBg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    addChild(stageBg);
}

void MapChooseLayer::addScrollView()
{
    auto center = Vec2(_sizeVisible.width / 2.0, _sizeVisible.height / 2.0);
    
    _spritesContainer = Layer::create();
    
    auto beachSprite = Sprite::create(IMAGE_ITEM_BEACH);
    auto seaSprite = Sprite::create(IMAGE_ITEM_SEA);
    auto moonSprite = Sprite::create(IMAGE_ITEM_MOON);
    
    _spritesContainer->addChild(beachSprite);
    beachSprite->setPosition(center);
    
    _spritesContainer->addChild(seaSprite);
    seaSprite->setPosition(center + Vec2(_sizeVisible.width, 0));
    
    _spritesContainer->addChild(moonSprite);
    moonSprite->setPosition(center + Vec2(2 * _sizeVisible.width, 0));
    
    _spritesContainer->setPosition(Point::ZERO);
    _spritesContainer->setContentSize(Size(_sizeVisible.width * _spritesContainer->getChildrenCount(), _sizeVisible.height));
    
    _scrollView = ScrollView::create(_sizeVisible);
    _scrollView->setContainer(_spritesContainer);
    _scrollView->setDirection(ScrollView::Direction::HORIZONTAL);
    _scrollView->setTouchEnabled(true);
    _scrollView->setPosition(Point::ZERO);
    _scrollView->setContentOffset(Vec2::ZERO);
    _scrollView->setDelegate(this);
//    _scrollView->setBounceable(false);
    addChild(_scrollView);
}

bool MapChooseLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    _beginTouchPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
    
    return true;
}

void MapChooseLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    
}

void MapChooseLayer::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    adjustScrollView(MoveDirection::NONE);
}

void MapChooseLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event)
{
    auto endPoint = Director::getInstance()->convertToGL(touch->getLocationInView());
    float distance = endPoint.x - _beginTouchPoint.x;
    
    if ( fabs(distance) > kValidMoveDistance ) {
        adjustScrollView(distance > 0 ? MoveDirection::RIGHT : MoveDirection::LEFT);
    } else {
        adjustScrollView(MoveDirection::NONE);
    }
}

void MapChooseLayer::adjustScrollView(MapChooseLayer::MoveDirection direction)
{
    // close ScrollView auto adjustment
    _scrollView->unscheduleAllCallbacks();
    
    switch (direction) {
        case MoveDirection::LEFT:
            _currentPage ++;
            break;
        case MoveDirection::RIGHT:
            _currentPage --;
            break;
            
        default:
            break;
    }
    
    if (_currentPage < 1) {
        _currentPage = 1;
    }
    if (_currentPage > _spritesContainer->getChildrenCount()) {
        _currentPage = _spritesContainer->getChildrenCount();
    }
    
    auto adjustPos = Point(-1 * _sizeVisible.width * (_currentPage - 1), 0);
    _scrollView->setContentOffset(adjustPos, true);
}

void MapChooseLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view)
{
    
}

void MapChooseLayer::scrollViewDidZoom(cocos2d::extension::ScrollView *view)
{
    
}
