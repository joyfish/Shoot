//
//  Window_Ability.h
//  Shoot
//
//  Created by wilford on 14-10-20.
//
//

#ifndef __Shoot__Window_Ability__
#define __Shoot__Window_Ability__

#include "HWindow.h"

using namespace ui;
using namespace cocos2d;
using namespace std;

class Window_Ability : public HWindow{
public:
    WINDOW_SINGTON_SHOW(Window_Ability);
    
protected:
    virtual void onStartAnimOver() override;
    
private:
    enum BTNS{
        BTN_CLOSE
    };
    
    void onBtnEvent(Ref* sender, Widget::TouchEventType type);
    
    void onCloseClick();
    
    void onItemClick(Ref* sender, Widget::TouchEventType type);
    void firstShowItem(int id);
    void showItem(int id);
    
    
    vector<Widget*> m_btns;
    Widget* m_info_bg;
    ImageView* m_black_block_1;
    ImageView* m_black_block_2;
    static Window_Ability* instance;
};


#endif /* defined(__Shoot__Window_Ability__) */
