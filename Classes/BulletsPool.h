//
//  BulletsCache.h
//  Shooting
//
//  Created by wilford on 14-7-29.
//
//

#ifndef __Shooting__BulletsCache__
#define __Shooting__BulletsCache__

#include "cocos2d.h"
#include "Bullet.h"
#include "PoolTemplate.h"

using namespace cocos2d;

class BulletsPool : public PoolTemplate<BulletsPool, Bullet>
{
public:
    friend PoolTemplate<BulletsPool,Bullet>;
    
protected:
    virtual bool isMatch(Bullet* node,string anim_file) override{
        if (node->getParent()) {return false;}
        if (node->getAnimFile().compare(anim_file)!=0) {return false;}
        return true;
    }
    BulletsPool(){_className = "BulletsPool";}
};

#endif /* defined(__Shooting__BulletsCache__) */
