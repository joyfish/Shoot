//
//  Window_Tips.h
//  Shoot
//
//  Created by wilford on 14/10/22.
//
//

#ifndef __Shoot__Window_Tips__
#define __Shoot__Window_Tips__

#include "HWindow.h"

using namespace ui;
using namespace cocos2d;
using namespace std;

class Window_Tips : public HWindow{
public:
    WINDOW_SHOW(Window_Tips);
    
    
private:
    enum BTNS{
        BTN_OK,
        BTN_CLOSE
    };
    
    void onBtnEvent(Ref* sender, Widget::TouchEventType type);
    
    void onCloseClick();
    
    
    vector<Widget*> m_btns;
};

#endif /* defined(__Shoot__Window_Tips__) */
