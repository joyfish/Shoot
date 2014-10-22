//
//  SplitBomb.h
//  Shooting
//
//  Created by wilford on 14-8-29.
//
//

#ifndef __Shooting__SplitBomb__
#define __Shooting__SplitBomb__

#include "ArmatureBase.h"
#include "SplitBombModel.h"

using namespace std;


class SplitBomb : public ArmatureBase{
public:
    static SplitBomb* create(const SplitBombModel&  model)
    {
        SplitBomb *pRet = new SplitBomb(model);
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
    
    void play(float rotate);
    
   
    
    const string getAnimFile() const {return _anim_file;};
    
    void set(const SplitBombModel& model){
        _anim_file = model.file_name;
        _anim_name = model.anim_name;
        _speed = model.b_speed;
        _range = model.range;
        _isCross = model.is_cross;
    }
    
protected:
    SplitBomb(const SplitBombModel& model)
    {
        _type = BOMB;
        set(model);
    }
    
    
    ~SplitBomb(){
        // log("Bullet destructor");
    }
    
    virtual void update(float dt);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void initArmature() override;
    
    void play();
    
    void onRangeOut();
    
    string _anim_file;//�ӵ������ļ���
    string _anim_name;//�ӵ�������
    float _speed;//����
    int _range;//���
    float _isCross;//�Ƿ�͸
    float m_move_distance;
    float m_rotate;
    
};

#endif /* defined(__Shooting__SplitBomb__) */
