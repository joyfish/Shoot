//
//  Window_Battle.h
//  Shoot
//
//  Created by wilford on 14-10-20.
//
//

#ifndef __Shoot__Window_Battle__
#define __Shoot__Window_Battle__

#include "HWindow.h"

using namespace ui;
using namespace cocos2d;
using namespace std;

class Window_Battle : public HWindow{
public:
    Window_Battle():onStartGame(nullptr){}
    
    WINDOW_SHOW(Window_Battle);
    
    void m_close();
    
protected:
    virtual void startAnim() override;
    
    virtual void endAnim() override;
    
    virtual void onStartAnimOver() override;
    
    
public:
    function<void()> onStartGame;
private:
    enum BTNS{
        BTN_START
    };
    
    void onBtnEvent(Ref* sender, Widget::TouchEventType type);
    
    void onStartClick();
    
    void onItemClick(Ref* sender, Widget::TouchEventType type);
    void firstShowItem(int id);
    void showItem(int id);
    
    vector<Widget*> m_btns;
    Widget* m_stage_info_bg;
    ImageView* m_black_block_1;
    ImageView* m_black_block_2;
    int m_battle_type;
};

#endif /* defined(__Shoot__Window_Battle__) */
