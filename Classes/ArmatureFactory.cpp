//
//  ArmatureFactory.cpp
//  Shooting
//
//  Created by wilford on 14-9-1.
//
//

#include "ArmatureFactory.h"
#include "common.h"

void ArmatureFactory::create(Node* parent, Point pos,float rotate,string anim_file,string anim_name){
    CCASSERT(parent, " parent can't be nullptr ");
    CCASSERT(!anim_file.empty(), "anim_file_name can't be empty");
    CCASSERT(!anim_name.empty(), "anim_name can't be empty");
    
    function<void(Armature*,MovementEventType,string)> callback = [&](Armature* armature, MovementEventType evt, string animationName){
        switch (evt) {
            case cocostudio::COMPLETE:
                armature->removeFromParentAndCleanup(false);
                break;
            default:
                break;
        }
    };

    Armature* a = ArmaturesPool::getInstance()->get(getFileNameByPath(anim_file.c_str()));
    if (a == nullptr) {
        ArmatureDataManager::getInstance()->addArmatureFileInfo( anim_file);
        a = Armature::create(getFileNameByPath(anim_file.c_str()));
        if (a) {
            ArmaturesPool::getInstance()->add(a);
        }
    }
    
    if (a) {
        a->setPosition(parent->convertToNodeSpace(pos));
        a->setRotation(rotate);
        a->getAnimation()->play(anim_name);
        parent->addChild(a);
        a->getAnimation()->setMovementEventCallFunc(callback);
    }
}