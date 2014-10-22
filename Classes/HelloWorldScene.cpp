#include "HelloWorldScene.h"

USING_NS_CC;

Layer* HelloWorld::controller_layer = nullptr;
Scene* HelloWorld::physics_scene = nullptr;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene -> getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    scene ->getPhysicsWorld()->setGravity(Point::ZERO);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    

    GameLayerTest* gameLayerTest = GameLayerTest::create();
    
    this->addChild(gameLayerTest);
    
    //log("aaa %s", GunModel::getInstance()->getName(0).c_str());
    
    
    return true;
}

void HelloWorld::onEnter(){
    Layer::onEnter();
    

}





void HelloWorld::menuCloseCallback(Ref* pSender)
{
    this->setPosition(getPosition()+Point(0,-1000));
//    if (!_children.empty()) {
//        log("size %d",_children.size());
//        for (auto child:_children) {
//            if (child->getPhysicsBody()) {
//                Point pos = child->getPosition();
//                child->setPosition(pos+Point(1,1));
//                child->setPosition(pos);
//            }
//        }
//    }
//    auto bodys = this->getScene()->getPhysicsWorld()->getAllBodies();
//    for (auto body : bodys) {
//        auto _node = body->getNode();
//        Point pos = _node->getPosition();
//        //log("body1 pos = %f %f",body->getPosition().x,body->getPosition().y);
//        _node->setPosition(pos+Point(1,1));
//        _node->setPosition(pos);
//        //log("body2 pos = %f %f",body->getPosition().x,body->getPosition().y);
//    }
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//
//    Director::getInstance()->end();
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
}




