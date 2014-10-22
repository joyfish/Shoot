//
//  Hero.h
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#ifndef __Shooting__Hero__
#define __Shooting__Hero__

#include "ArmatureBase.h"
#include "LifeCircleLogger.h"
#include "GunModelManager.h"
#include "Gun.h"
#include "common.h"
#include "mAStar.h"

class Hero : public ArmatureBase{
public:
    static Hero* create(mAStar* aStar)
    {
        Hero *pRet = new Hero(aStar);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }
    
    void fire();
    void startFire(){m_isFiring = true;}//playAnim("fire_"+_hand_type,0);}
    void endFire(){m_isFiring = false;}//stopAnim();playAnim("idle_"+_hand_type);}
    
    virtual void move(Point dir) override;
    
    void changeGun(Gun* gun);
    
    Gun* getGunData(){return _gun;}
    
    SYNTHESIZE(mAStar*, _aStar, AStar)
    
    void AIMoveTo(Point goal){
 //       log("move from %f ,%f  to %f,%f",getPositionX(), getPositionY(), goal.x, goal.y);
        m_way = _aStar->getPath(getPositionX(), getPositionY(), goal.x, goal.y);
//        for (deque<mAStarPoint>::iterator it = m_way.begin(); it!=m_way.end(); ++it) {
//            log("move %f,%f",(*it).x,(*it).y);
//        }
        way_duration = 0;
    }
    
protected:
    Hero(mAStar* aStar)
    :onFire(nullptr)
    ,m_isFiring(false)
    ,m_isReloading(false)
    ,m_fireduration(0)
    ,_gun_id(1)
    ,_precision(0)
    ,_aStar(aStar)
    {
        log("Hero constructor");
        _type = HERO;
    }
    
    ~Hero(){
        log("Hero destructor");
    }
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
    void updateAIWay(float dt);
    
    virtual void initColliderBoxs(){
        ArmatureBase::initColliderBoxs();
        getPhysicsBody()->setContactTestBitmask(HERO_CONTACT_MASK);
        getPhysicsBody()->setCategoryBitmask(HERO_COLLISION_MASK);
        getPhysicsBody()->getFirstShape()->setRestitution(0);
        //getPhysicsBody()->setMass(0.01f);
        //getPhysicsBody()->get
    }
    
    virtual void initArmature() override;
    
    void reload(){
        m_isReloading = true;
        schedule(schedule_selector(Hero::reloadOver), _gunModel->reload_time);
    }
    
    void reloadOver(float dt){
        m_isReloading = false;
        unschedule(schedule_selector(Hero::reloadOver));
        _gun->reload();
    }
    
    int _gun_id;//枪械id
    string _hand_type;//手持方式
    const GunModel* _gunModel;//枪械数据
    bool m_isFiring;//是否在开火状态
    float m_fireduration;//子弹间隔时间记录
    float _precision;//子弹当前精度
    float m_isReloading;//是否在换弹
    Gun* _gun;
    deque<mAStarPoint> m_way;//ai移动的路劲
    float way_duration;//单路劲移动持续时间
    
    
public:
    function<void(ElementType,Point,Point,float,float,const GunModel&)> onFire;
    
};

#endif /* defined(__Shooting__Hero__) */
