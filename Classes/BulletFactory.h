//
//  BulletFactory.h
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#ifndef __Shooting__BulletFactory__
#define __Shooting__BulletFactory__

#include "Hero.h"
#include "Bullet.h"
#include "BulletsPool.h"
#include "GunModel.h"

class BulletFactory {
public:
    static Bullet* create(ElementType fromtype, Point pos, float rotate,const GunModel& gunModel);
    
    static void init(Node* p){parent = p;}

private:
    static Node* parent;//×Óµ¯¸¸½Úµã
};

#endif /* defined(__Shooting__BulletFactory__) */
