//
//  NormalBomb.cpp
//  Shooting
//
//  Created by wilford on 14-8-28.
//
//

#include "NormalBomb.h"
#include "common.h"


void NormalBomb::initArmature(){
    //LOG_FUNCTION_LIFE
    ArmatureDataManager::getInstance()->addArmatureFileInfo(_anim_file+".ExportJson");
    m_armature = Armature::create(getFileNameByPath(_anim_file.c_str()));
    this->addChild(m_armature);
}

void NormalBomb::onEnter(){
    ArmatureBase::onEnter();
    scheduleUpdate();
    
    function<void(Armature*,MovementEventType,string)> callback = [&](Armature* armature, MovementEventType evt, string animationName){
        switch (evt) {
            case cocostudio::COMPLETE:
                fadeout();
                //log("%s %s complete",armature->getName().c_str(),animationName.c_str());
                break;
            case cocostudio::LOOP_COMPLETE:
                //log("%s %s loop complete", armature->getName().c_str(),animationName.c_str());
                break;
            case cocostudio::START:
                //log("%s %s start", armature->getName().c_str(),animationName.c_str());
                break;
            default:
                break;
        }
    };
    
    m_armature->getAnimation()->setMovementEventCallFunc(callback);
}

void NormalBomb::onExit(){
    ArmatureBase::onExit();
    unscheduleUpdate();
}


void NormalBomb::fadeout(){
    stopAnim();
    getPhysicsBody()->setEnable(false);
    const std::function<void()> callback = [&](void){
        m_armature->setOpacity(255);
        getPhysicsBody()->setEnable(true);
        this->hide();
    };
    m_armature->runAction( CCSequence::create(CCFadeOut::create(0.3f),CallFunc::create(callback), NULL) );
}

void NormalBomb::hide(){
    stopAnim();
    removeFromParentAndCleanup(false);
}


void NormalBomb::play(){
    playAnim(_anim_name);
    m_duration = _duration;
}

void NormalBomb::update(float dt){
    ArmatureBase::update(dt);
    if (m_duration>0) {
        m_duration-= dt;
        if (m_duration <= 0) {
            getPhysicsBody()->setEnable(false);
        }
    }
}

void NormalBomb::onCollision(){
    
}
