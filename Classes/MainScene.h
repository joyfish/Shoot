//
//  MainScene.h
//  Shoot
//
//  Created by wilford on 14-10-17.
//
//

#ifndef __Shoot__MainScene__
#define __Shoot__MainScene__

#include "HScene.h"
#include "Window_Battle.h"

using namespace ui;
using namespace std;

class MainScene : public HScene{
public:
    MainScene():m_battle_type(0),m_battle_window(nullptr){}
    
    CREATE_FUNC(MainScene);
    
    virtual void onEnter() override;
    
    virtual void onExit() override;
    
    virtual void loadResource() override{
        HScene::loadResource();
        addTextureName("ccs/main/main_bg.png");
        addTextureName("ccs/main/main_man.png");
        addTextureName("ccs/main/main_weapon_bg.png");
        addTextureName("ccs/main/main_knife_bg.png");
        addTextureName("ccs/main/main_bottom.png");
        addTextureName("ccs/main/main_right_bottom.png");
        addTextureName("ccs/main/main_top_left.png");
    }
    
private:
    void initWidgets();
    
    void initButtons();
    
    void showMainIn();
    
    void changeToBattle();
    void changeToMain();
    
    void onButtonEvent(Ref* target,Widget::TouchEventType type);
    
    void onStartClick();
    
    void onWeapon();//武器
    void onAbility();//能力
    void onChallenge();//挑战
    void onShop();//商城
    
    void onBackToMain();//从战役退到大厅
    void onBack();//从大厅退到封面
    
    void onBattle();//战役
    void onMercentary();//佣兵
    void updateBattleAndMercentary();
    
    void onCoinAdd();//买金币
    void onMoneyAdd();//买钻石
    
    void updateCoin(EventCustom* event);
    void updateMoney(EventCustom* event);
    
    void StartGame();//开始游戏
    
    enum BTNS{
        BTN_START = 0,
        BTN_WEAPON,
        BTN_ABILITY,
        BTN_CHALLENGE,
        BTN_SHOP,
        BTN_BATTLE,
        BTN_MERCENTARY,
        BTN_BUY_WEAPON,
        BTN_BACK,
        BTN_BACK_TO_MAIN,
        BTN_COIN_ADD,
        BTN_MONEY_ADD
    };
    
    Label* label;
    vector<Widget*> m_btns;
    
    Widget* m_bg;
    Widget* m_top_left_0;
    Widget* m_top_left_1;
    Widget* m_weapon_bg_0;
    Widget* m_weapon_bg_1;
    Widget* m_knife_bg;
    Widget* m_man;
    Widget* m_bottom;
    Widget* m_right_bottom;
    Widget* m_start_bg;
    TextAtlas* num_coin;
    TextAtlas* num_money;
    
    int m_battle_type;//0-战役 1-佣兵
    Window_Battle* m_battle_window;
    
    EventListenerCustom* _coin_listener;
    EventListenerCustom* _money_listener;
};

#endif /* defined(__Shoot__MainScene__) */
