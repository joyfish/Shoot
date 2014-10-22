//
//  HWindowsHelper.h
//  Shooting
//
//  Created by wilford on 14-10-14.
//
//

#ifndef __Shooting__HWindowsHelper__
#define __Shooting__HWindowsHelper__

#include "cocos2d.h"
#include "cocostudio/Cocostudio.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

class HWindowsHelper{
public:
    HWindowsHelper(Node* node);
    HWindowsHelper();
    
    void setTouchEnable(bool enabled);
    
private:
    void touchDisable(Node* node);
    
    Node* m_node;
    std::vector<Widget*> m_touchEnabledchildren;
};

#endif /* defined(__Shooting__HWindowsHelper__) */
