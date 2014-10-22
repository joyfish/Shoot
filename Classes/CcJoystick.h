//
//  CcJoystick.h
//  Shooting
//
//  Created by wilford on 14-7-17.
//
//

#ifndef __Shooting__CcJoystick__
#define __Shooting__CcJoystick__

#include "cocos2d.h"

using namespace cocos2d;

class CcJoystick :public Layer {
    
    public :
    //初始化 aPoint是摇杆中心 aRadius是摇杆半径 aJsSprite是摇杆控制点 aJsBg是摇杆背景
    static CcJoystick*  CcJoystickWithCenter(Point aPoint ,float aRadius ,Sprite* aJsSprite,Sprite* aJsBg,bool _isFollowRole);
    
    //启动摇杆
    void Active();
    
    //解除摇杆
    void Inactive();
    
private:
    CcJoystick * initWithCenter(Point aPoint ,float aRadius ,Sprite* aJsSprite,Sprite* aJsBg,bool _isFollowRole);
    
    Point centerPoint;//摇杆中心
    
    Point currentPoint;//摇杆当前位置
    
    bool active;//是否激活摇杆
    
    float radius;//摇杆半径
    
    Sprite *jsSprite;
    
    bool isFollowRole;//是否跟随用户点击
    
    Point getDirection();
    
    float getVelocity();
    
    void  updatePos(float dt);
    
    virtual bool onTouchBegan(Touch *pTouch, Event *pEvent); 
    virtual void onTouchMoved(Touch *pTouch, Event *pEvent);
    virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
    CREATE_FUNC(CcJoystick);
    
public:
    std::function<void(Point dir)> onDirectionChanged;
};

#endif /* defined(__Shooting__CcJoystick__) */
