//
//  CcJoystick.cpp
//  Shooting
//
//  Created by wilford on 14-7-17.
//
//

#include "CcJoystick.h"

using namespace cocos2d;

void CcJoystick::updatePos(float dt){
    jsSprite->setPosition(jsSprite->getPosition()+((currentPoint-jsSprite->getPosition())*0.5));
}
//启动摇杆
void CcJoystick::Active()
{
    if (!active) {
        active=true;
        schedule(schedule_selector(CcJoystick::updatePos));//添加刷新函数
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto listener = EventListenerTouchOneByOne::create();
        listener->onTouchBegan = CC_CALLBACK_2(CcJoystick::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(CcJoystick::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(CcJoystick::onTouchEnded, this);
        listener->setSwallowTouches(true);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }else {
    }
}
//解除摇杆
void   CcJoystick::Inactive()
{
    if (active) {
        active=false;
        this->unschedule(schedule_selector(CcJoystick::updatePos));//删除刷新
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        dispatcher->removeEventListenersForTarget(this);
    }else {
    }
}
//摇杆方位
Point CcJoystick::getDirection()
{
    return (currentPoint-centerPoint).getNormalized();
}
//摇杆力度
float CcJoystick::getVelocity()
{
    return centerPoint.getDistance(currentPoint);
}
CcJoystick* CcJoystick:: CcJoystickWithCenter(Point aPoint ,float aRadius ,Sprite* aJsSprite,Sprite* aJsBg,bool _isFollowRole){
    CcJoystick *jstick=CcJoystick::create();
    jstick->initWithCenter(aPoint,aRadius,aJsSprite,aJsBg,_isFollowRole);
    return jstick;
}
bool CcJoystick::onTouchBegan(Touch* touch, Event* event)
{
    if (!active)
        return false;
    this->setVisible(true);
    Point touchPoint = touch->getLocation();
    if(!isFollowRole){
        if (touchPoint.getDistance(centerPoint) > radius){
            return false;
        }
    }
    currentPoint = touchPoint;
    if(isFollowRole){
        centerPoint=currentPoint;
        jsSprite->setPosition(currentPoint);
        this->getChildByTag(88)->setPosition(currentPoint);
    }
    return true;
}
void  CcJoystick::onTouchMoved(Touch* touch, Event* event)
{
    Point touchPoint = touch->getLocation();
    if (touchPoint.getDistance(centerPoint) > radius)
    {
        currentPoint = centerPoint+(touchPoint-centerPoint).getNormalized()*radius;
    }else {
        currentPoint = touchPoint;
    }
    if (onDirectionChanged) {
        onDirectionChanged(getDirection());
    }
}
void  CcJoystick::onTouchEnded(Touch* touch, Event* event)
{
    currentPoint = centerPoint;
    if (onDirectionChanged) {
        onDirectionChanged(Point(0,0));
    }
    if(isFollowRole){
        this->setVisible(false);
    }
}

CcJoystick* CcJoystick::initWithCenter(Point aPoint ,float aRadius ,Sprite* aJsSprite,Sprite* aJsBg,bool _isFollowRole){
    
    isFollowRole =_isFollowRole;
    active = false;
    radius = aRadius;
    if(!_isFollowRole){
        centerPoint =aPoint;
    }else{
        centerPoint =Point(0,0);
    }
    
    currentPoint = centerPoint;
    jsSprite = aJsSprite;
    jsSprite->setPosition(centerPoint);
    aJsBg->setPosition(centerPoint);
    aJsBg->setTag(88);
    this->addChild(aJsBg);
    this->addChild(jsSprite);
    if(isFollowRole){
        this->setVisible(false);
    }
    this->Active();//激活摇杆
    return this;
}