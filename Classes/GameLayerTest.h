//
//  GameLayerTest.h
//  Shooting
//
//  Created by wilford on 14-7-22.
//
//

#ifndef __Shooting__GameLayerTest__
#define __Shooting__GameLayerTest__

#include "cocos2d.h"
//#include "CocAnimationTest.h"
#include "HeroFactory.h"
#include "BulletFactory.h"
#include "CcJoystick.h"
#include "ElementsContact.h"
//#include "BulletsCache.h"
#include "GunModel.h"
#include "DropDownList.h"
#include "Gun.h"
#include "LineContainer.h"
#include "mAStar.h"

using namespace cocos2d;
using namespace cocos2d::CustomDropDownListBox;

class GameLayerTest : public Layer{
public:
    GameLayerTest()
    :_map(nullptr)
//    ,_animation(nullptr)
    ,_gameLayer(nullptr)
    ,_controllerlayer(nullptr)
    ,_jsDir(Point::ZERO)
    ,_bulletDir(Point::ZERO)
    {}
    ~GameLayerTest(){
//        _animation->release();
        BulletsPool::purge();
        for (auto g : gunlist) {
            g->release();
        }
    }
    
    CREATE_FUNC(GameLayerTest);
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    virtual void update(float dt);
    
    void keepHeroInCenter();
    
    void updateGunBulletsAndClips();

    
protected:
    void onFire(ElementType type,Point b_point,Point c_point, float r_rotate, float rotate, const GunModel& gunMode);
    
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    
    virtual void onTouchesBegan(const std::vector<Touch*>& pTouches, Event* pEvents){
        for (int i=0; i<pTouches.size(); i++) {
            log( "begin %d : %f,%f",i,pTouches[i]->getLocation().x,pTouches[i]->getLocation().y);
        }
    }
    
    void onGunChanged(int idx);
    
    
    TMXTiledMap* _map;//地图
    Hero* _hero;
   // CocAnimationTest* _animation;//动画
    Layer* _gameLayer;//游戏层
    Node* _manLayer;//人物层
    Node* _bulletLayer;//子弹层
    Node* _effectUpLayer;//在人物上方的特效层
    Node* _effectDownLayer;//在人物下风的特效层
    Node* _bombLayer;//爆炸层
    
    Layer* _controllerlayer;//控制层
    Point _jsDir;//保存摇杆指示的方向
    
    Point _bulletDir;//保存子弹摇杆方向
    
    bool _istouched;//地图场景时候有触摸事件
    Point _touchPoint;//触摸位置
    
    Point _heroPrePoint;//英雄上次位置
    vector<Gun*> gunlist;
    
    Label* label_bullets;
    Label* label_clips;
    
    LineContainer* man_line_container;
    mAStar* man_AStar;
    
};


#endif /* defined(__Shooting__GameLayerTest__) */
