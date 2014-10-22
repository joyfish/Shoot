//
//  SplitBombPool.h
//  Shooting
//
//  Created by wilford on 14-8-29.
//
//

#ifndef Shooting_SplitBombPool_h
#define Shooting_SplitBombPool_h

#include "cocos2d.h"
#include "SplitBomb.h"
#include "PoolTemplate.h"

using namespace cocos2d;

class SplitBombPool : public PoolTemplate<SplitBombPool, SplitBomb>
{
public:
    friend PoolTemplate<SplitBombPool,SplitBomb>;
    
protected:
    virtual bool isMatch(SplitBomb* node,string anim_file) override{
    if (node->getParent()) {return false;}
    if (node->getAnimFile().compare(anim_file)!=0) {return false;}
    return true;
}
SplitBombPool(){_className = "SplitBombPool";}
};


#endif
