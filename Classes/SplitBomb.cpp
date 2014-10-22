//
//  SplitBomb.cpp
//  Shooting
//
//  Created by wilford on 14-8-29.
//
//

#include "SplitBomb.h"
#include "common.h"

void SplitBomb::initArmature(){
    //LOG_FUNCTION_LIFE
    ArmatureDataManager::getInstance()->addArmatureFileInfo(_anim_file+".ExportJson");
    
    m_armature = Armature::create(getFileNameByPath(_anim_file.c_str()));
    
    this->addChild(m_armature);
}

void SplitBomb::onEnter(){
    ArmatureBase::onEnter();
    scheduleUpdate();
}

void SplitBomb::onExit(){
    ArmatureBase::onExit();
    unscheduleUpdate();
}


void SplitBomb::fadeout(){
    stopAnim();
    getPhysicsBody()->setEnable(false);
    const std::function<void()> callback = [&](void){
        m_armature->setOpacity(255);
        getPhysicsBody()->setEnable(true);
        this->hide();
    };
    m_armature->runAction( CCSequence::create(CCFadeOut::create(0.3f),CallFunc::create(callback), NULL) );
}

void SplitBomb::hide(){
    stopAnim();
    removeFromParentAndCleanup(false);
}

void SplitBomb::play(float rotate){
    m_rotate = rotate;
    play();
}

void SplitBomb::play(){
    m_move_distance = 0;
    playAnim(_anim_name);
    Point dir = Point(cos(CC_DEGREES_TO_RADIANS(-m_rotate)),sin(CC_DEGREES_TO_RADIANS(-m_rotate)));
    this->setRotation(m_rotate);
    this->getPhysicsBody()->setVelocity(dir*_speed*bullet_unit_speed);
}

void SplitBomb::update(float dt){
    ArmatureBase::update(dt);
    do{
        if(!getPhysicsBody()->isEnabled()){
            break;
        }
        
        if (m_move_distance>=_range) {
            break;
        }
        m_move_distance+=dt*_speed*bullet_unit_speed;
        if (m_move_distance >= _range) {
            onRangeOut();
        }
    }while (0);
}

void SplitBomb::onCollision(){
    
}

void SplitBomb::onRangeOut(){
    fadeout();
}