//
//  IHWindow.h
//  Shooting
//
//  Created by wilford on 14-10-14.
//
//

#ifndef Shooting_IHWindow_h
#define Shooting_IHWindow_h

#include "cocos2d.h"

class IHWindow : public cocos2d::Ref {
public:
    IHWindow():m_zOrder(0){}
    
    virtual void close(){cocos2d::log("IHWindow Close");}
    virtual void update(float dt){}
    int getZOrder(){return m_zOrder;}
    void setZOrder(int zorder){m_zOrder = zorder;}
protected:
    int m_zOrder;
};

#endif
