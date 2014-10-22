//
//  Window_Weapon.h
//  Shoot
//
//  Created by wilford on 14-10-21.
//
//

#ifndef __Shoot__Window_Weapon__
#define __Shoot__Window_Weapon__

#include "HWindow.h"

using namespace ui;
using namespace cocos2d;
using namespace std;

class Window_Weapon : public HWindow{
public:
    WINDOW_SINGTON_SHOW(Window_Weapon);
    
    Window_Weapon();
    ~Window_Weapon();
    
    
protected:
    virtual void startAnim() override;
    
    virtual void onStartAnimOver() override;
    
private:
    enum BTNS{
        BTN_CLOSE = 0,
        BTN_COIN_ADD,
        BTN_MONEY_ADD
    };
    
    void onBtnEvent(Ref* sender, Widget::TouchEventType type);
    
    void onCloseClick();
    void onCoinAdd();
    void onMoneyAdd();
    
    void onItemClick(Ref* sender, Widget::TouchEventType type);
    void firstShowItem(int id);
    void showItem(int id);
    
    void updateCoin(EventCustom* event);
    void updateMoney(EventCustom* event);
    
    
    vector<Widget*> m_btns;
    Widget* m_info_bg;
    ImageView* m_black_block_1;
    ImageView* m_black_block_2;
    Widget* m_right_bottom;
    EventListenerCustom* _coin_listener;
    EventListenerCustom* _money_listener;
    TextAtlas* num_coin;
    TextAtlas* num_money;
    static Window_Weapon* instance;
};

#endif /* defined(__Shoot__Window_Weapon__) */
