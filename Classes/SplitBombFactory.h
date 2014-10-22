//
//  SplitBombFactory.h
//  Shooting
//
//  Created by wilford on 14-8-29.
//
//

#ifndef __Shooting__SplitBombFactory__
#define __Shooting__SplitBombFactory__

#include "SplitBomb.h"
#include "SplitBombPool.h"
#include "SplitBombModel.h"

class SplitBombFactory {
public:
    static void create(Point pos,const SplitBombModel& model,int contactMask,int collisionMask);
    
    static void init(Node* p){parent = p;}
    
private:
    static Node* parent;//×Óµ¯¸¸½Úµã
};

#endif /* defined(__Shooting__SplitBombFactory__) */
