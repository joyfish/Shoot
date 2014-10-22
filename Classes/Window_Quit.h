//
//  Window_Quit.h
//  Shoot
//
//  Created by wilford on 14/10/22.
//
//

#ifndef __Shoot__Window_Quit__
#define __Shoot__Window_Quit__

#include "HWindow.h"

using namespace ui;
using namespace cocos2d;
using namespace std;

class Window_Quit : public HWindow{
public:
    WINDOW_SINGTON_SHOW(Window_Quit);
    
    
private:
    enum BTNS{
        BTN_OK,
        BTN_CANCEL,
        BTN_CLOSE
    };
    
    void onBtnEvent(Ref* sender, Widget::TouchEventType type);
    
    void onCloseClick();
    
    void onOKClick();
    
    
    vector<Widget*> m_btns;
    static Window_Quit* instance;
};

#endif /* defined(__Shoot__Window_Quit__) */
