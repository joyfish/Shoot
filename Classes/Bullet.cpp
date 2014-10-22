//
//  Bullet.cpp
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#include "Bullet.h"
#include "common.h"

void Bullet::initArmature(){
    //LOG_FUNCTION_LIFE
    ArmatureDataManager::getInstance()->addArmatureFileInfo(m_anim_file);
    m_armature = Armature::create(getFileNameByPath(m_anim_file.c_str()));
    this->addChild(m_armature);
}

void Bullet::onEnter(){
    ArmatureBase::onEnter();
    scheduleUpdate();
    //play();
}

void Bullet::onExit(){
    ArmatureBase::onExit();
    unscheduleUpdate();
}


void Bullet::fadeout(){
    if (!getPhysicsBody()->isEnabled()) {
        return;
    }
    stopAnim();
    getPhysicsBody()->setVelocity(Point::ZERO);
    getPhysicsBody()->setEnable(false);
    const std::function<void()> callback = [&](void){
        m_armature->setOpacity(255);
        getPhysicsBody()->setEnable(true);
        this->hide();
    };
    m_armature->runAction( CCSequence::create(CCFadeOut::create(0.3f),CallFunc::create(callback), NULL) );
}

void Bullet::hide(){
    stopAnim();
    removeFromParentAndCleanup(false);
}


void Bullet::play(float rotate){
    m_rotate = rotate;
    play();
}

void Bullet::play(){
    m_move_distance = 0;
    playAnim(m_anim_name);
    Point dir = Point(cos(CC_DEGREES_TO_RADIANS(-m_rotate)),sin(CC_DEGREES_TO_RADIANS(-m_rotate)));
    this->setRotation(m_rotate);
    this->getPhysicsBody()->setVelocity(dir*_speed*bullet_unit_speed);
}

void Bullet::update(float dt){
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

void Bullet::onContact(Point contactPoint){
    switch (_bullet_collision) {
        case BULLET_COLLISION_FADEOUT:
            break;
        case BULLET_COLLISION_NORMALBOMB:
        {
            NormalBombModel* model = NormalBombModelManager::getInstance()->getModelByID(_bullet_collision_2);
            NormalBombFactory::create(contactPoint, *model,getPhysicsBody()->getContactTestBitmask(),getPhysicsBody()->getCollisionBitmask());
        }
            break;
        case BULLET_COLLISION_SPLITBOMB:
        {
            SplitBombModel* model = SplitBombModelManager::getInstance()->getModelByID(_bullet_outrange_2);
            SplitBombFactory::create(contactPoint, *model,getPhysicsBody()->getContactTestBitmask(),getPhysicsBody()->getCollisionBitmask());
        }
            break;
        default:
            break;
    }
    fadeout();
}

void Bullet::onRangeOut(){
    switch (_bullet_outrange) {
        case BULLET_OUTRANGE_FADEOUT:
            break;
        case BULLET_OUTRANGE_NORMALBOMB:
        {
            NormalBombModel* model = NormalBombModelManager::getInstance()->getModelByID(_bullet_outrange_2);
            NormalBombFactory::create(getPosition(), *model,getPhysicsBody()->getContactTestBitmask(),getPhysicsBody()->getCollisionBitmask());
        }
            break;
        case BULLET_OUTRANGE_SPLITBOMB:
            break;
        default:
            break;
    }
    fadeout();
}