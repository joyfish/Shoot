//
//  HeroFactory.cpp
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//


#include "HeroFactory.h"


Hero* HeroFactory::create(int typeId,mAStar* aStar){
    Hero* _hero = nullptr;
    switch (typeId) {
        case 0:
            _hero = Hero::create(aStar);
            break;
            
        default:
            _hero = Hero::create(aStar);
            break;
    }
    return _hero;
}
