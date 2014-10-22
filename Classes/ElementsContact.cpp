//
//  ElementsContact.cpp
//  Shooting
//
//  Created by wilford on 14-7-29.
//
//

#include "ElementsContact.h"

bool ElementsContact::init(){
    if (!Node::init()) {
        return false;
    }
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(ElementsContact::onContactBegin, this);
//    contactListener->onContactPostSolve = CC_CALLBACK_2(ElementsContact::onContactPostSolve, this);
//    contactListener->onContactSeperate = CC_CALLBACK_1(ElementsContact::onContactSeperate, this);
//    contactListener->onContactPreSolve = CC_CALLBACK_2(ElementsContact::onContactPresolve, this);
    
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

bool ElementsContact::onContactBegin(PhysicsContact& contact){
    ElementBase* nodeA = dynamic_cast<ElementBase*>(contact.getShapeA()->getBody()->getNode());
    ElementBase* nodeB = dynamic_cast<ElementBase*>(contact.getShapeB()->getBody()->getNode());
   // log("A %d ",nodeA->getElementType());
   // log("B %d", nodeB->getElementType());
    
    const PhysicsContactData* pdata = contact.getContactData();
    Point contactPoint = Point(0,0);
    for (int i=0;i<pdata->count; i++) {
        contactPoint += pdata->points[i];
        //log("%f,%f",pdata->points[i].x,pdata->points[i].y);
    }
    contactPoint = contactPoint/pdata->count;
    
    if (nodeA->getElementType() == BULLET && nodeB->getElementType() == WALL) {
        contactBulletAndWall(nodeA, nodeB,contactPoint);
    }
    if (nodeA->getElementType() == WALL && nodeB ->getElementType() == BULLET) {
        contactBulletAndWall(nodeB, nodeA,contactPoint);
    }
    return true;
}

//void ElementsContact::onContactSeperate(cocos2d::PhysicsContact &contact){
//    ElementBase* nodeA = dynamic_cast<ElementBase*>(contact.getShapeA()->getBody()->getNode());
//    ElementBase* nodeB = dynamic_cast<ElementBase*>(contact.getShapeB()->getBody()->getNode());
//    
//    const PhysicsContactData* pdata = contact.getContactData();
//    Point contactPoint = Point(0,0);
//    for (int i=0;i<pdata->count; i++) {
//        contactPoint += pdata->points[i];
//        //log("%f,%f",pdata->points[i].x,pdata->points[i].y);
//    }
//    contactPoint = contactPoint/pdata->count;
//    
//    if (nodeA->getElementType() == BULLET && nodeB->getElementType() == WALL) {
//        contactBulletAndWall(nodeA, nodeB,contactPoint);
//    }
//    if (nodeA->getElementType() == WALL && nodeB ->getElementType() == BULLET) {
//        contactBulletAndWall(nodeB, nodeA,contactPoint);
//    }
//}
//
//bool ElementsContact::onContactPresolve(PhysicsContact& contact, PhysicsContactPreSolve& solve){
//    ElementBase* nodeA = dynamic_cast<ElementBase*>(contact.getShapeA()->getBody()->getNode());
//    ElementBase* nodeB = dynamic_cast<ElementBase*>(contact.getShapeB()->getBody()->getNode());
//    
//    if (nodeA->getElementType() == BULLET && nodeB->getElementType() == WALL) {
//        contactBulletAndWall(nodeA, nodeB);
//    }
//    if (nodeA->getElementType() == WALL && nodeB ->getElementType() == BULLET) {
//        contactBulletAndWall(nodeB, nodeA);
//    }
//    return true;
//}
//
//
//void ElementsContact::onContactPostSolve(PhysicsContact& contact,const PhysicsContactPostSolve& solve){
//    ElementBase* nodeA = dynamic_cast<ElementBase*>(contact.getShapeA()->getBody()->getNode());
//    ElementBase* nodeB = dynamic_cast<ElementBase*>(contact.getShapeB()->getBody()->getNode());
//
//    if (nodeA->getElementType() == BULLET && nodeB->getElementType() == WALL) {
//        contactBulletAndWall(nodeA, nodeB);
//    }
//    if (nodeA->getElementType() == WALL && nodeB ->getElementType() == BULLET) {
//        contactBulletAndWall(nodeB, nodeA);
//    }
//}

void ElementsContact::contactBulletAndWall(ElementBase *bullet, ElementBase *wall,Point contactPoint){
    Bullet* _b = dynamic_cast<Bullet*>(bullet);
    //log("bullet %f %f",_b->getPositionX(),_b->getPositionY());
    _b->onContact(contactPoint);
}