//
//  ArmatureBase.cpp
//  Shooting
//
//  Created by wilford on 14-7-28.
//
//

#include "ArmatureBase.h"


bool ArmatureBase::init(){
    if (!Node::init()) {
        return false;
    }
    initArmature();
//    if (m_armature == nullptr) {
//        return false;
//    }
    this->setAnchorPoint(Point::ANCHOR_MIDDLE);
    this->setPhysicsBody(PhysicsBody::create());
    initColliderBoxs();
    return true;
}

void ArmatureBase::initColliderBoxs(){
    if (m_armature == nullptr) {
        return;
    }
    Map<string, Bone*> dict = m_armature->getBoneDic();
    for (auto iter = dict.begin(); iter!=dict.end(); ++iter) {
        Bone* bone = iter->second;
        ColliderDetector* detector = bone->getColliderDetector();
        if (!detector) {
            continue;
        }
        Vector<ColliderBody*> vec = detector->getColliderBodyList();
        for (Vector<ColliderBody*>::iterator it = vec.begin(); it!=vec.end(); it++) {
            ColliderBody* body = dynamic_cast<ColliderBody*>(*it);
            vector<Point> vertexList = body->getCalculatedVertexList();
            int length = static_cast<int>(vertexList.size());
            Point* points = new Point[length];
            for (int i=0; i<length; i++) {
                points[i] = vertexList[length-i-1];
            }
            this->getPhysicsBody()->addShape(PhysicsShapePolygon::create(points, length));
        }
    }
    this->getPhysicsBody()->setRotationEnable(false);
}


void ArmatureBase::playAnims(const vector<string> anims){
    CC_ASSERT(m_armature);
    m_armature->getAnimation()->playWithNames(anims);
}

void ArmatureBase::playAnim(const string animName,int loop/* = -1*/){
    CC_ASSERT(m_armature);
    m_armature->getAnimation()->play(animName,-1,loop);
}

void ArmatureBase::stopAnim(){
    CC_ASSERT(m_armature);
    m_armature->getAnimation()->stop();
}

void ArmatureBase::move(cocos2d::Point v){
    CC_ASSERT(getPhysicsBody());
    getPhysicsBody()->setVelocity(v);
}

void ArmatureBase::dir(Point dir){
    //Point _dir = point - getPosition();
    setRotation(CC_RADIANS_TO_DEGREES(-atan2(dir.y, dir.x)));
}

