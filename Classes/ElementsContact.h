//
//  ElementsContact.h
//  Shooting
//
//  Created by wilford on 14-7-29.
//
//

#ifndef __Shooting__ElementsContact__
#define __Shooting__ElementsContact__

#include "cocos2d.h"
#include "ElementBase.h"
#include "Bullet.h"

using namespace cocos2d;

class ElementsContact : public Node{
public:
    CREATE_FUNC(ElementsContact)
    
    virtual bool init();
    
    
protected:
    bool onContactBegin(PhysicsContact& contact);
    //bool onContactPresolve(PhysicsContact& contact,PhysicsContactPreSolve& solve);
    //void onContactPostSolve(PhysicsContact& contact,const PhysicsContactPostSolve& solve);
    void onContactSeperate(PhysicsContact& contact);
    
    void contactBulletAndWall(ElementBase* bullet,ElementBase* wall,Point contactPoint);
};

#endif /* defined(__Shooting__ElementsContact__) */
