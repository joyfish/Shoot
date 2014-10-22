//
//  CocAnimationTest.cpp
//  Shooting
//
//  Created by wilford on 14-7-16.
//
//

#include "CocAnimationTest.h"

using namespace std;

bool CocAnimationTest::init(Layer* layer){
    do{
        m_layer = layer;
        CC_BREAK_IF(!m_layer);
        ArmatureDataManager::getInstance()->addArmatureFileInfo("hero.ExportJson");
        m_armature = Armature::create("hero");
       // Armature* gun = Armature::create("man");
        //gun->setPosition(Point(100,100));
        
        //m_layer->addChild(gun,10);
        
//        Sprite* s = Sprite::create("CloseNormal.png");
//        s->setPosition(Point(_pCenterX,_pCenterY+100));
//        s->setPhysicsBody(PhysicsBody::createBox(Size(50/_screenScale, 50/_screenScale)));
//        m_layer->addChild(s,10);
        
//        Bone* bone1 = gun->getBone("manBone");
//        gunBone->addChild(gun);
        
        
        
        CC_BREAK_IF(!m_armature);
       
        m_node = Node::create();
        m_layer->addChild(m_node);
        m_node->setPosition(Point(_pCenterX,_pCenterY));
        m_node->setAnchorPoint(Point::ANCHOR_MIDDLE);
        m_node->addChild(m_armature);
        m_node->setPhysicsBody(PhysicsBody::create());
        
        m_armature->setPosition(Point::ZERO);
        
        Bone* _bulletout = m_armature->getBone("bulletout");
        BaseData* data = _bulletout->getWorldInfo();
        m_node->getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(20,20),PHYSICSSHAPE_MATERIAL_DEFAULT,Point(data->x,data->y)));
       // Point points[4] = {Point(0,0),Point(100,100),Point(200,100)};
       // m_node->getPhysicsBody()->addShape(PhysicsShapePolygon::create(points, 3));
        
        //m_armature->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
        
//        m_armature->setPhysicsBody(PhysicsBody::create());
//        m_armature->getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(50/_screenScale, 50/_screenScale)));
////        Point points[4] = {Point(0,0),Point(100,100),Point(0,100)};
////        m_armature->getPhysicsBody()->addShape(PhysicsShapePolygon::create(points, 3));
//        
//       log("pos x=%f,y = %f",m_armature->getBone("shoulder_l")->getWorldInfo()-> x,m_armature->getBone("shoulder_r")->getWorldInfo()->y);
//        m_armature->getPhysicsBody()->addShape(PhysicsShapeBox::create(Size(20,20),PHYSICSSHAPE_MATERIAL_DEFAULT,Point(125,-5)));
//        
//        
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
                int length = vertexList.size();
                log("length %d",length);
                Point* points = new Point[length];
                for (int i=0; i<length; i++) {
                    points[i] = vertexList[length-i-1];
                    log("point %d %f,%f",i,vertexList[i].x,vertexList[i].y);
                }
                
                m_node->getPhysicsBody()->addShape(PhysicsShapePolygon::create(points, length));
                
            }
        }
        
        m_node->getPhysicsBody()->setRotationEnable(false);
        //Bone* manBone = m_armature->getBone("manBone");
        //m_armature->setPhysicsBody(PhysicsBody::createBox(Size(50/_screenScale, 50/_screenScale)));
        //m_armature->setPosition(Point(100,100));
       // m_armature->setRotation(60);
      //  m_armature->getPhysicsBody()->setVelocity(Point(0,500));
     //   m_armature->getPhysicsBody()->getShape(0)->setTag(99);
      //  m_armature->getPhysicsBody()->setContactTestBitmask(10);
      //  m_armature->getPhysicsBody()->setRotationEnable(false);
      //  m_armature->getPhysicsBody()->setCategoryBitmask(0xf);
       // m_armature->getPhysicsBody()->getShape(99)->setRestitution(0);
 //       Bone* gunBone = gun->getBone("manBone");

//        manBone->addChildBone(gunBone);
        
 //       m_armature->setPhysicsBody(PhysicsBody::createEdgeBox(Size(50/_screenScale, 50/_screenScale)));
//        m_armature->getAnimation()->play("run");
//        m_armature->getAnimation()->setSpeedScale(0.5f);
 //       manBone->addChild(gunBone);
        
        function<void(Armature*,MovementEventType,string)> callback = [](Armature* armature, MovementEventType evt, string animationName){
            switch (evt) {
                case cocostudio::COMPLETE:
                    log("%s %s complete",armature->getName().c_str(),animationName.c_str());
                    break;
                case cocostudio::LOOP_COMPLETE:
                    log("%s %s loop complete", armature->getName().c_str(),animationName.c_str());
                    break;
                case cocostudio::START:
                    log("%s %s start", armature->getName().c_str(),animationName.c_str());
                    break;
                default:
                    break;
            }
        };
        
       // m_armature->getAnimation()->setMovementEventCallFunc(callback);
        //armature->setRotation(60);
        
        
        
        
        return true;
        //m_layer->addChild(gun,11);
    }while (0);
    return false;
}

void CocAnimationTest::move(cocos2d::Point p){
    if (m_armature) {
        m_node->getPhysicsBody()->setVelocity(p);
        //Point _currentPos = m_armature->getPosition();
        //m_armature->setPosition(_currentPos+p);
    }
}

void CocAnimationTest::dir(Point p){
    if (m_armature) {
        Point _dir = p - m_node->getPosition();
        //m_node->stopAllActions();
        //m_node->runAction(CCRotateTo::create(0.3f, CC_RADIANS_TO_DEGREES(-atan2(_dir.y, _dir.x))));
        m_node->setRotation(CC_RADIANS_TO_DEGREES(-atan2(_dir.y, _dir.x)));
    }
}

Point CocAnimationTest::pos(){
    if (m_armature) {
//        log("p x = %f,y= %f", m_armature->getPhysicsBody()->getPosition().x,m_armature->getPhysicsBody()->getPosition().y);
        return m_armature->getPosition();
    }
    return Point(0,0);
}