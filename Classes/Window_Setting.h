//
//  Window_Setting.h
//  Shoot
//
//  Created by wilford on 14-10-17.
//
//

#ifndef __Shoot__Window_Setting__
#define __Shoot__Window_Setting__


#include "HWindow.h"

using namespace ui;
using namespace cocos2d;
using namespace std;

class Window_Setting : public HWindow{
public:
    WINDOW_SINGTON_SHOW(Window_Setting);
    
private:
    enum BTNS{
        BTN_EFFECT_OFF = 0,
        BTN_EFFECT_ON,
        BTN_MUSIC_OFF,
        BTN_MUSIC_ON,
        BTN_SAVE,
        BTN_CLOSE,
    };
    
    void onBtnEvent(Ref* sender, Widget::TouchEventType type);
    
    void updateMusicBtns();
    void updateEffectBtns();
    void onSaveClick();
    void onCloseClick();
    
    static Window_Setting* instance;
    vector<Widget*> m_btns;
};

#endif /* defined(__Shoot__Window_Setting__) */
