//
//  NormalBombFactory.cpp
//  Shooting
//
//  Created by wilford on 14-8-29.
//
//

#include "NormalBombFactory.h"

NormalBomb* NormalBombFactory::create(Point pos,const NormalBombModel& model,int contactMask,int collisonMask){
    CCASSERT(parent, "must init parent first");
    
    NormalBomb* _normalbomb = nullptr;
    _normalbomb = NormalBombPool::getInstance()->get(model.file_name);
    if (_normalbomb == nullptr) {
        _normalbomb = NormalBomb::create(model);
        NormalBombPool::getInstance()->add(_normalbomb);
    }else{
        _normalbomb->set(model);
    }
    
    parent->addChild(_normalbomb);
    _normalbomb->setPosition(parent->convertToNodeSpace(pos));
    _normalbomb->play();

    _normalbomb->getPhysicsBody()->setContactTestBitmask(contactMask);
    _normalbomb->getPhysicsBody()->setCollisionBitmask(collisonMask);
    
    return _normalbomb;
}


Node* NormalBombFactory::parent = nullptr;