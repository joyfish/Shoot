//
//  NormalBomb.h
//  Shooting
//
//  Created by wilford on 14-8-28.
//
//

#ifndef __Shooting__NormalBomb__
#define __Shooting__NormalBomb__

#include "ArmatureBase.h"
#include "NormalBombModel.h"

using namespace std;


class NormalBomb : public ArmatureBase{
public:
    static NormalBomb* create(const NormalBombModel&  model)
    {
        NormalBomb *pRet = new NormalBomb(model);
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
    
    virtual void initColliderBoxs() override{
        ArmatureBase::initColliderBoxs();
        this->getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(50,50)));
    }
    
    void onCollision();
    
    void fadeout();
    
    void hide();
    
    void play();
    
    const string getAnimFile() const {return _anim_file;};
    
    void set(const NormalBombModel& model){
        _anim_file = model.file_name;
        _anim_name = model.anim_name;
        _duration = model.duration;
    }
    
protected:
    NormalBomb(const NormalBombModel& model)
    :m_duration(0)
    {
        _type = BOMB;
        set(model);
    }
    
    
    ~NormalBomb(){
        // log("Bullet destructor");
    }
    
    virtual void update(float dt);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void initArmature() override;
    
    
    string _anim_file;//子弹动画文件名
    string _anim_name;//子弹动画名
    float _duration;//持续时间
    float m_duration;//当前延时
    
};

#endif /* defined(__Shooting__NormalBomb__) */
