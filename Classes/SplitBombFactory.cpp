//
//  SplitBombFactory.cpp
//  Shooting
//
//  Created by wilford on 14-8-29.
//
//

#include "SplitBombFactory.h"

void SplitBombFactory::create(Point pos,const SplitBombModel& model,int contactMask,int collisonMask){
    CCASSERT(parent, "must init parent first");
    
    
    int b_count = model.count;
    float r_padding = 360/b_count;
    for (int i=0;i<b_count; i++) {
        SplitBomb* _splitbomb = nullptr;
        _splitbomb = SplitBombPool::getInstance()->get(model.file_name);
        if (_splitbomb == nullptr) {
            _splitbomb = SplitBomb::create(model);
            SplitBombPool::getInstance()->add(_splitbomb);
        }else{
            _splitbomb->set(model);
        }
        parent->addChild(_splitbomb);
        _splitbomb->setPosition(parent->convertToNodeSpace(pos));
        _splitbomb->play(r_padding*i);
        _splitbomb->getPhysicsBody()->setContactTestBitmask(contactMask);
        _splitbomb->getPhysicsBody()->setCollisionBitmask(collisonMask);
    }
}

Node* SplitBombFactory::parent = nullptr;