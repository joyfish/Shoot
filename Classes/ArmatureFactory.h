//
//  ArmatureFactory.h
//  Shooting
//
//  Created by wilford on 14-9-1.
//
//

#ifndef __Shooting__ArmatureFactory__
#define __Shooting__ArmatureFactory__

#include "ArmaturesPool.h"


class ArmatureFactory {
public:
    static void create(Node* parent, Point pos,float rotate,string anim_file,string anim_name);
};


#endif /* defined(__Shooting__ArmatureFactory__) */
