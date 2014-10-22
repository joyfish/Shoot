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
    
    void onWeapon();//����
    void onAbility();//����
    void onChallenge();//��ս
    void onShop();//�̳�
    
    void onBackToMain();//��ս���˵�����
    void onBack();//�Ӵ����˵�����
    
    void onBattle();//ս��
    void onMercentary();//Ӷ��
    void updateBattleAndMercentary();
    
    void onCoinAdd();//����
    void onMoneyAdd();//����ʯ
    
    void updateCoin(EventCustom* event);
    void updateMoney(EventCustom* event);
    
    void StartGame();//��ʼ��Ϸ
    
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
    
    int m_battle_type;//0-ս�� 1-Ӷ��
    Window_Battle* m_battle_window;
    
    EventListenerCustom* _coin_listener;
    EventListenerCustom* _money_listener;
};

#endif /* defined(__Shoot__MainScene__) */
