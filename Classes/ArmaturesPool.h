//
//  ArmaturesPool.h
//  Shooting
//
//  Created by wilford on 14-9-1.
//
//

#ifndef __Shooting__ArmaturesPool__
#define __Shooting__ArmaturesPool__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "PoolTemplate.h"

using namespace cocos2d;
using namespace cocostudio;

class ArmaturesPool : public PoolTemplate<ArmaturesPool, Armature>
{
public:
    friend PoolTemplate<ArmaturesPool,Armature>;
    
protected:
    virtual bool isMatch(Armature* node,string anim_file) override{
    if (node->getParent()) {return false;}
    if (node->getArmatureData()->name.compare(anim_file)!=0){return false;}
    //if (node-> compare(anim_file)!=0) {return false;}
    return true;
    }
    ArmaturesPool(){_className = "ArmaturesPool";}
};




#endif /* defined(__Shooting__ArmaturesPool__) */
