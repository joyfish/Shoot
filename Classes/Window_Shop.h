//
//  Window_Shop.h
//  Shoot
//
//  Created by wilford on 14-10-20.
//
//

#ifndef __Shoot__Window_Shop__
#define __Shoot__Window_Shop__

#include "HWindow.h"

using namespace ui;
using namespace cocos2d;
using namespace std;

class Window_Shop : public HWindow{
public:
    WINDOW_SINGTON_SHOW(Window_Shop);
    
    
private:
    enum BTNS{
        BTN_CLOSE
    };
    
    void onBtnEvent(Ref* sender, Widget::TouchEventType type);
    
    void onCloseClick();
    
    
    vector<Widget*> m_btns;
    static Window_Shop* instance;
};

#endif /* defined(__Shoot__Window_Shop__) */
