//
//  CocAnimationTest.h
//  Shooting
//
//  Created by wilford on 14-7-16.
//
//

#ifndef __Shooting__CocAnimationTest__
#define __Shooting__CocAnimationTest__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ScreenFit.h"

USING_NS_CC;
using namespace cocostudio;

class CocAnimationTest : public Ref{
public:
    static CocAnimationTest* create(Layer* layer){
        CocAnimationTest* instance = new CocAnimationTest();
        if(instance->init(layer)){
            instance->autorelease();
            instance->retain();
            return instance;
        }
        CC_SAFE_DELETE(instance);
        return nullptr;
    }
    void move(Point p);
    void dir(Point p);
    Point pos();
    Armature* getArmature(){return m_armature;}
private:
    CocAnimationTest():m_armature(nullptr),m_node(nullptr){}
    bool init(Layer* layer);
    Layer* m_layer;
    Armature* m_armature;
    Node* m_node;
};


#endif /* defined(__Shooting__CocAnimationTest__) */
