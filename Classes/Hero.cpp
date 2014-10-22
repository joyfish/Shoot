//
//  Hero.cpp
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#include "Hero.h"

void Hero::initArmature(){
    ArmatureDataManager::getInstance()->addArmatureFileInfo("hero.ExportJson");
    m_armature = Armature::create("hero");
    this->addChild(m_armature);
    Bone* gunBone = m_armature->getBone("gun");
    
    Vector<GunModel*> gunModels = GunModelManager::getInstance()->getModels();
    
    int idx = 0;
    for (auto gModel:gunModels) {
        CCASSERT(gModel, "gunModel can't be null");
        string g_id = to_string(gModel->id);
        Skin* weaponSkin = Skin ::create("guns/gun_"+g_id+".png");
        CCASSERT(weaponSkin, "no image for gun");
        gunBone->addDisplay(weaponSkin,idx);
        idx++;
    }
}

void Hero::fire(){
    float r_rotate = getRotation() - _precision + 2*_precision*CCRANDOM_0_1();
    Bone* gunBone = m_armature->getBone("gun");
    BaseData* data = gunBone->getWorldInfo();
    Point gunPos = Point(data->x,data->y);
    Point _boutPoint = gunPos+Point(_gunModel->gun_effect0_offset,0);
    Point point = this->convertToWorldSpace(_boutPoint);
    Point _c_point = gunPos + Point(_gunModel->gun_effect1_offset,0);
    Point c_point = this->convertToWorldSpace(_c_point);
    onFire(_type,point,c_point,r_rotate,getRotation(), *_gunModel);
    stopAnim();
    playAnim("fire_"+_hand_type);
    _gun->fire();
    if (_gun->getBCount()<=0 && _gun->hasClips()) {
        reload();
    }
    //playAnims(vector<string>{"fire_"+_hand_type,"idle_"+_hand_type});
}

void Hero::onEnter(){
    ArmatureBase::onEnter();
    //this->getPhysicsBody()->setEnable(false);
    scheduleUpdate();
    //changeGun(_gun_id);
    //playAnim("fire");
}

void Hero::onExit(){
    ArmatureBase::onExit();
    unscheduleUpdate();
}

void Hero::update(float dt){
    ArmatureBase::update(dt);
    if (m_fireduration > 0)
        m_fireduration -= dt;
    if (m_isFiring&&!m_isReloading&&_gun->getBCount()>0) {
        if (m_fireduration <= 0) {
            fire();
            m_fireduration = _gunModel->duration;
        }
        
        _precision+= _gunModel->precision/_gunModel->p_speed*dt;
        _precision = MIN(_precision, _gunModel->precision);
    }else{
        _precision-= _gunModel->precision/_gunModel->p_back_speed*dt;
        _precision = MAX(_precision, 0);
    }
    
    //updateAIWay(dt);
}

void Hero::updateAIWay(float dt){
    way_duration -= dt;
    if (way_duration <=0 ) {
        if (m_way.size()>0) {
            Point p = getPosition();
            mAStarPoint aP = m_way.front();
            m_way.pop_front();
            Point g = Point(aP.x,aP.y);
            float distance = p.getDistance(g);
            way_duration = distance/300;
            move((g-p).getNormalized());
        }else{
            move(Point(0,0));
        }
    }
}

void Hero::move(cocos2d::Point dir){
    CC_ASSERT(getPhysicsBody());
//    PhysicsBody* body = getPhysicsBody();
//    Point vel = body->getVelocity();
//    float m = body->getMass();// the mass of the body
//    Point desiredVel = dir*300;// the vector speed you set
//    Point velChange = desiredVel - vel;
//    Point impluse = velChange * m; //impluse = mv
//    body->applyImpulse(impluse);
    getPhysicsBody()->setVelocity(dir*300);
}

void Hero::changeGun(Gun* gun){
    _gun = gun;
    reloadOver(0);
    _gun_id = _gun->getGunID();
    m_fireduration = 0;
    int idx = GunModelManager::getInstance()->getIdxByID(_gun_id);
    _gunModel = GunModelManager::getInstance()->getModelByID(_gun_id);
    CCAssert(_gunModel,"gunModel can't be nil");
    Bone* gunBone = m_armature->getBone("gun");
    _hand_type = to_string(_gunModel->handtype);
    gunBone->changeDisplayWithIndex(idx, true);
    playAnim("idle_"+_hand_type);
}
