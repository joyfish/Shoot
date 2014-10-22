//
//  Gun.h
//  Shooting
//
//  Created by wilford on 14-8-27.
//
//

#ifndef __Shooting__Gun__
#define __Shooting__Gun__

#include "ArmatureBase.h"
#include "GunModel.h"
#include "GunModelManager.h"


class Gun: public ArmatureBase{
public:
    static Gun* create(int gun_id)
    {
        Gun *pRet = new Gun(gun_id);
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
    
    bool hasClips(){//是否有弹夹
        return clips>0;
    }
    
    void fire(){
        bullets_count-= _gunModel->shoot_bullets;
        bullets_count = MAX(0,bullets_count);
    }
    
    void reload(){//换镗
        if (clips<=0) {
            return;
        }
        clips--;
        bullets_count = _gunModel->b_count;
    }
    
    const int getBCount()const{//子弹数量
        return bullets_count;
    }
    const int getClips() const{//弹夹数
        return clips;
    }
    
    const GunModel* getGunModel() const{
        return _gunModel;
    }
    
    const int getGunID() const{
        return _gunModel->id;
    }
    
protected:
    Gun(int gun_id)
    {
        _gunModel = GunModelManager::getInstance()->getModelByID(gun_id);
        CCASSERT(_gunModel, "gunModel can't be null");
        bullets_count = _gunModel->b_count;
        clips = _gunModel->init_clips;
    }
    
    Gun(){}
    
    
    virtual void initArmature() override {}
    
    const GunModel* _gunModel;
    int bullets_count;//子弹数
    int clips;//弹夹数
    
};


#endif /* defined(__Shooting__Gun__) */
