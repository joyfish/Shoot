//
//  NormalBombFactory.h
//  Shooting
//
//  Created by wilford on 14-8-29.
//
//

#ifndef __Shooting__NormalBombFactory__
#define __Shooting__NormalBombFactory__

#include "NormalBomb.h"
#include "NormalBombPool.h"
#include "NormalBombModel.h"

class NormalBombFactory {
public:
    static NormalBomb* create(Point pos,const NormalBombModel& model,int contactMask,int collisionMask);
    
    static void init(Node* p){parent = p;}
    
private:
    static Node* parent;//×Óµ¯¸¸½Úµã
};

#endif /* defined(__Shooting__NormalBombFactory__) */
