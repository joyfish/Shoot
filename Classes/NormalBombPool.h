//
//  NormalBombPool.h
//  Shooting
//
//  Created by wilford on 14-8-29.
//
//

#ifndef Shooting_NormalBombPool_h
#define Shooting_NormalBombPool_h


#include "cocos2d.h"
#include "NormalBomb.h"
#include "PoolTemplate.h"

using namespace cocos2d;

class NormalBombPool : public PoolTemplate<NormalBombPool, NormalBomb>
{
public:
    friend PoolTemplate<NormalBombPool,NormalBomb>;
    
protected:
    virtual bool isMatch(NormalBomb* node,string anim_file) override{
        if (node->getParent()) {return false;}
        if (node->getAnimFile().compare(anim_file)!=0) {return false;}
        return true;
    }
    NormalBombPool(){_className = "NormalBombPool";}
};

#endif
