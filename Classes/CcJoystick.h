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
    //��ʼ�� aPoint��ҡ������ aRadius��ҡ�˰뾶 aJsSprite��ҡ�˿��Ƶ� aJsBg��ҡ�˱���
    static CcJoystick*  CcJoystickWithCenter(Point aPoint ,float aRadius ,Sprite* aJsSprite,Sprite* aJsBg,bool _isFollowRole);
    
    //����ҡ��
    void Active();
    
    //���ҡ��
    void Inactive();
    
private:
    CcJoystick * initWithCenter(Point aPoint ,float aRadius ,Sprite* aJsSprite,Sprite* aJsBg,bool _isFollowRole);
    
    Point centerPoint;//ҡ������
    
    Point currentPoint;//ҡ�˵�ǰλ��
    
    bool active;//�Ƿ񼤻�ҡ��
    
    float radius;//ҡ�˰뾶
    
    Sprite *jsSprite;
    
    bool isFollowRole;//�Ƿ�����û����
    
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
