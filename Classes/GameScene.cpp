//
//  GameScene.cpp
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#include "GameScene.h"

GameScene* GameScene::createWithPhysics()
{
    GameScene *ret = new GameScene();
    if (ret && ret->initWithPhysics())
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        CC_SAFE_DELETE(ret);
        return nullptr;
    }
}

void GameScene::onEnter(){
    HScene::onEnter();
    //getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    getPhysicsWorld()->setGravity(Point::ZERO);
    GameLayerTest* gameLayerTest = GameLayerTest::create();
    this->addChild(gameLayerTest);
}

void GameScene::onExit(){
    HScene::onExit();
}

void GameScene::loadResource(){
    HScene::loadResource();
}