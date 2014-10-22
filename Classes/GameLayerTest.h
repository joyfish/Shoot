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
    
    
    TMXTiledMap* _map;//��ͼ
    Hero* _hero;
   // CocAnimationTest* _animation;//����
    Layer* _gameLayer;//��Ϸ��
    Node* _manLayer;//�����
    Node* _bulletLayer;//�ӵ���
    Node* _effectUpLayer;//�������Ϸ�����Ч��
    Node* _effectDownLayer;//�������·����Ч��
    Node* _bombLayer;//��ը��
    
    Layer* _controllerlayer;//���Ʋ�
    Point _jsDir;//����ҡ��ָʾ�ķ���
    
    Point _bulletDir;//�����ӵ�ҡ�˷���
    
    bool _istouched;//��ͼ����ʱ���д����¼�
    Point _touchPoint;//����λ��
    
    Point _heroPrePoint;//Ӣ���ϴ�λ��
    vector<Gun*> gunlist;
    
    Label* label_bullets;
    Label* label_clips;
    
    LineContainer* man_line_container;
    mAStar* man_AStar;
    
};


#endif /* defined(__Shooting__GameLayerTest__) */
