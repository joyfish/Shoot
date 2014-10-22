//
//  BulletFactory.cpp
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#include "BulletFactory.h"


Bullet* BulletFactory::create(ElementType fromtype,Point pos,float rotate ,const GunModel& gunModel){
    CCASSERT(parent, "must init parent first");
    
    Bullet* _bullet = nullptr;
    string anim_file = gunModel.b_file_name;
    _bullet = BulletsPool::getInstance()->get(anim_file);
    if (_bullet == nullptr) {
        _bullet = Bullet::create(gunModel);
        BulletsPool::getInstance()->add(_bullet);
    }else{
        _bullet->set(gunModel);
    }
    
    parent->addChild(_bullet);
    
    _bullet->setPosition(parent->convertToNodeSpace(pos));
    _bullet->play(rotate);
    
    switch (fromtype) {
        case HERO:
            _bullet->getPhysicsBody()->setContactTestBitmask(HERO_BULLET_CONTACT_MASK);
            _bullet->getPhysicsBody()->setCollisionBitmask(HERO_BULLET_COLLISION_MASK);
            break;
        case MONSTER:
            _bullet->getPhysicsBody()->setContactTestBitmask(MONSTER_BULLET_CONTACT_MASK);
            _bullet->getPhysicsBody()->setCollisionBitmask(MONSTER_BULLET_COLLISION_MASK);
            break;
        default:
            break;
    }
    
    return _bullet;
}


Node* BulletFactory::parent = nullptr;
