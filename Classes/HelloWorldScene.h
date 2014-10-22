#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ScreenFit.h"
#include "CocAnimationTest.h"
#include "CcJoystick.h"
#include "GameLayerTest.h"
#include "GunModel.h"
#include "GunModelManager.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    virtual void onEnter();
    
    
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    
    HelloWorld()
    :m_jsDir(Point(0,0))
    ,m_animation(nullptr)
    ,m_touchPoint(Point(0,0))
    ,m_istouched(false)
    ,_layerPosition(Point::ZERO)
    {}
    ~HelloWorld(){m_animation->release();}
    
    
    CocAnimationTest* m_animation;
    Scene* m_scene;
    Point m_jsDir;//Ò¡¸Ë·½Ïò
    bool m_istouched;
    Point m_touchPoint;
    Size m_mapSize;
    static Scene* physics_scene;
    static Layer* controller_layer;
    Point _layerPosition;
};

#endif // __HELLOWORLD_SCENE_H__
