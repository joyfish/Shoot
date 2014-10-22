//
//  Bullet.h
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#ifndef __Shooting__Bullet__
#define __Shooting__Bullet__

#include "ArmatureBase.h"
#include "GunModel.h"
#include "NormalBombFactory.h"
#include "SplitBombFactory.h"
#include "NormalBombModelManager.h"
#include "SplitBombModelManager.h"

using namespace std;

enum BULLET_WAY{
    BULLET_WAY_LINE = 0,
    BULLET_WAY_FOLLOW = 1
};

enum BULLET_OUTRANGE{
    BULLET_OUTRANGE_FADEOUT = 0,
    BULLET_OUTRANGE_NORMALBOMB = 1,
    BULLET_OUTRANGE_SPLITBOMB = 2,
};

enum BULLET_COLLISION{
    BULLET_COLLISION_FADEOUT = 0,
    BULLET_COLLISION_NORMALBOMB = 1,
    BULLET_COLLISION_SPLITBOMB = 2,
};

class Bullet : public ArmatureBase{
public:
    static Bullet* create(const GunModel& gunModel)
    {
        Bullet *pRet = new Bullet(gunModel);
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
        this->getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(40,40)));
    }
    
    void onContact(Point contactPoint);
    
    void fadeout();
    
    void hide();
    
    void play(float rotate);
    
    const string getAnimFile() const {return m_anim_file;};
    
    bool isCross(){return _bullet_is_cross == 1;}
    
    void set(const GunModel& gunModel){
        _speed = gunModel.b_speed;
        _bullet_way = static_cast<BULLET_WAY>(gunModel.bullet_way);
        _bullet_is_cross = gunModel.bullet_is_cross;
        _bullet_outrange = static_cast<BULLET_OUTRANGE>(gunModel.bullet_outrange);
        _bullet_outrange_2 = gunModel.bullet_outrange_2;
        _bullet_collision = static_cast<BULLET_COLLISION>(gunModel.bullet_collision);
        _bullet_collision_2 = gunModel.bullet_collision_2;
        m_anim_name = gunModel.b_anim_name;
        _range = gunModel.range;
    }
    
protected:
    Bullet(const GunModel& gunModel)
    {
       // log("Bullet constructor");
        m_anim_file = gunModel.b_file_name;
        _type = BULLET;
        set(gunModel);
    }
    
    
    ~Bullet(){
       // log("Bullet destructor");
    }
    
    virtual void update(float dt);
    
    virtual void onEnter();
    
    virtual void onExit();
    
    virtual void initArmature() override;
    
    void play();
    
    void onRangeOut();
    
    string m_anim_file;//子弹动画文件id
    string m_anim_name;//子弹动画id
    float m_rotate;
    float m_move_distance;//已经移动的距离
    
    float _range;//攻击范围
    float _speed;//子弹速度
    BULLET_WAY _bullet_way;//子弹轨迹
    int _bullet_is_cross;//是否可穿透
    BULLET_OUTRANGE _bullet_outrange;//子弹到极限距离效果 0 渐变消失 1...
    int _bullet_outrange_2;
    BULLET_COLLISION _bullet_collision;//子弹碰撞后的效果 0 渐变消失 1...
    int _bullet_collision_2;
};

#endif /* defined(__Shooting__Bullet__) */
