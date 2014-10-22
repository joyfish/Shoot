//
//  HeroFactory.h
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#ifndef __Shooting__HeroFactory__
#define __Shooting__HeroFactory__


#include "Hero.h"

class HeroFactory {
public:
    static Hero* create(int typeId,mAStar* aStar);
    
};



#endif /* defined(__Shooting__HeroFactory__) */
