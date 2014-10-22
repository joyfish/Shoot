//
//  ArmatureBase.h
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#ifndef __Shooting__ArmatureBase__
#define __Shooting__ArmatureBase__

#include "cocostudio/CocoStudio.h"
#include "ScreenFit.h"
#include "LifeCircleLogger.h"
#include "ElementBase.h"

using namespace cocos2d;
using namespace std;
using namespace cocostudio;

class ArmatureBase : public ElementBase{
public:
    virtual void move(Point v);//给予固定方向的速度
    virtual void dir(Point dir);//朝向固定位置
    
    void playAnims(const vector<string> anims);
    void playAnim(string animName,int loop=-1);
    void stopAnim();
    
    const Armature* getArmature() const
    {
        return m_armature;
    }
    
protected:
    virtual bool init();
    
    virtual void initArmature()=0;
    virtual void initColliderBoxs();
    
    
    ArmatureBase()
    :m_armature(nullptr)
    {
        //log("ArmatureBase constructor");
    }
    
    ~ArmatureBase(){
        //log("ArmatureBase destructor");
    }
    
    Armature* m_armature;
};

#endif /* defined(__Shooting__ArmatureBase__) */
