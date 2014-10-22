//
//  MainScene.cpp
//  Shoot
//
//  Created by wilford on 14-10-17.
//
//

#include "MainScene.h"
#include "Window_Task.h"
#include "Window_Ability.h"
#include "Window_Shop.h"
#include "Window_Weapon.h"


void MainScene::onEnter(){
    HScene::onEnter();
    m_bg = GUIReader::getInstance()->widgetFromJsonFile("ccs/Main.json");
    scene_bg->addChild(m_bg);
   
    initWidgets();
    initButtons();
    showMainIn();
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    _coin_listener = EventListenerCustom::create(EVENT_COIN_UPDATE, CC_CALLBACK_1(MainScene::updateCoin, this));
    _money_listener = EventListenerCustom::create(EVENT_MONEY_UPDATE, CC_CALLBACK_1(MainScene::updateMoney, this));
    dispatcher->addEventListenerWithFixedPriority(_coin_listener, 1);
    dispatcher->addEventListenerWithFixedPriority(_money_listener, 1);
}

void MainScene::onExit(){
    HScene::onExit();
    if (_coin_listener) {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_coin_listener);
    }
    if (_money_listener) {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_money_listener);
    }
}

void MainScene::initWidgets(){
    if (m_bg == nullptr) {
        return;
    }
    m_top_left_0 = ui::Helper::seekWidgetByName(m_bg, "top_left_0");
    m_top_left_1 = ui::Helper::seekWidgetByName(m_bg, "top_left_1");
    m_weapon_bg_0 = ui::Helper::seekWidgetByName(m_bg, "weapon_bg_0");
    m_weapon_bg_1 = ui::Helper::seekWidgetByName(m_bg, "weapon_bg_1");
    m_knife_bg = ui::Helper::seekWidgetByName(m_bg, "knife_bg");
    m_man = ui::Helper::seekWidgetByName(m_bg, "man");
    m_start_bg = ui::Helper::seekWidgetByName(m_bg, "black_bg");
    m_bottom = ui::Helper::seekWidgetByName(m_bg, "bottom");
    m_right_bottom = ui::Helper::seekWidgetByName(m_bg, "right_bottom");
    m_top_left_0->setPosition(Point(0,_pTop+120));
    m_top_left_0->setVisible(true);
    m_top_left_1->setPosition(Point(0,_pTop+120));
    m_top_left_1->setVisible(true);
    m_weapon_bg_0->setPosition(Point(-500,441));
    m_weapon_bg_1->setPosition(Point(-500,270));
    m_knife_bg->setPosition(Point(-500,125));
    m_start_bg->setPosition(Point(_pRight+215,222));
    m_man->setPosition(Point(_pRight+180,305));
    m_bottom->setPosition(Point(_pCenterX,_pBottom-65));
    m_right_bottom->setPosition(Point(_pRight,_pBottom-65));
    
    num_coin = dynamic_cast<TextAtlas*>(ui::Helper::seekWidgetByName(m_right_bottom, "num_coin"));
    num_money = dynamic_cast<TextAtlas*>(ui::Helper::seekWidgetByName(m_right_bottom, "num_money"));
    num_coin->setString(to_string(G::getCoin()));
    num_money->setString(to_string(G::getMoney()));
}

void MainScene::showMainIn(){
    setTouchEnable(false);
    m_top_left_0->runAction(MoveTo::create(0.2f, Point(_pLeft,_pTop)));
    m_weapon_bg_0->runAction(Sequence::create(DelayTime::create(0),MoveTo::create(0.2f, Point(_pLeft+20,441)),nullptr));
    m_weapon_bg_1->runAction(Sequence::create(DelayTime::create(0.1f),MoveTo::create(0.2f, Point(_pLeft+20,270)),nullptr));
    m_knife_bg->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pLeft+20,125)),CallFunc::create([&](){setTouchEnable(true);}),nullptr));
    m_bottom->runAction(MoveTo::create(0.2f, Point(_pCenterX,_pBottom)));
    m_right_bottom->runAction(MoveTo::create(0.2f, Point(_pRight,_pBottom)));
    m_man->setOpacity(60);
    m_man->runAction(FadeTo::create(0.3f, 255));
    m_man->runAction(MoveTo::create(0.3f, Point(_pCenterX+220,305)));
    m_start_bg->runAction(MoveTo::create(0.3f, Point(_pRight-150,222)));
}

void MainScene::changeToBattle(){
    setTouchEnable(false);
    m_weapon_bg_0->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pLeft-500,441)),nullptr));
    m_weapon_bg_1->runAction(Sequence::create(DelayTime::create(0.1f),MoveTo::create(0.2f, Point(_pLeft-500,270)),nullptr));
    m_knife_bg->runAction(Sequence::create(DelayTime::create(0),MoveTo::create(0.2f, Point(_pLeft-500,125)),nullptr));
    m_man->runAction(Sequence::create(DelayTime::create(0.2f),FadeTo::create(0.3f, 60),nullptr));
    m_man->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.3f, Point(_pRight+180,305)),nullptr));
    m_start_bg->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.3f, Point(_pRight+215,222)),nullptr));
    m_right_bottom->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pRight,_pBottom-65)),nullptr));
    m_top_left_0->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pLeft,_pTop+120)),nullptr));
    m_top_left_1->runAction(Sequence::create(DelayTime::create(0.4f),CallFunc::create([&](){ m_battle_window = Window_Battle::show(this);m_battle_window->onStartGame=CC_CALLBACK_0(MainScene::StartGame, this);}),MoveTo::create(0.2f, Point(_pLeft,_pTop)),CallFunc::create([&](){setTouchEnable(true);}),nullptr));
   
}

void MainScene::changeToMain(){
    setTouchEnable(false);
    m_top_left_1->runAction(Sequence::create(MoveTo::create(0.2f, Point(_pLeft,_pTop+120)),nullptr));
    if (m_battle_window) {
        m_battle_window->closeWindow();
        m_battle_window->onWindowClosed = [&](){
            m_weapon_bg_0->runAction(Sequence::create(DelayTime::create(0),MoveTo::create(0.2f, Point(_pLeft+20,441)),nullptr));
            m_weapon_bg_1->runAction(Sequence::create(DelayTime::create(0.1f),MoveTo::create(0.2f, Point(_pLeft+20,270)),nullptr));
            m_knife_bg->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pLeft+20,125)),nullptr));
            m_man->setOpacity(60);
            m_man->runAction(FadeTo::create(0.3f, 255));
            m_man->runAction(MoveTo::create(0.3f, Point(_pCenterX+220,305)));
            m_start_bg->runAction(MoveTo::create(0.3f, Point(_pRight-150,222)));
            m_right_bottom->runAction(MoveTo::create(0.2f, Point(_pRight,_pBottom)));
            m_top_left_0->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pLeft,_pTop)),CallFunc::create([&](){setTouchEnable(true);}),nullptr));
        };
    }
}

void MainScene::initButtons(){
    if (m_bg == nullptr) {
        return;
    }
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_start"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_weapon"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_ability"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_challenge"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_shop"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_battle"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_mercentary"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_buy"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_back"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_back_to_main"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_coin_add"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_bg, "btn_money_add"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(MainScene::onButtonEvent, this));
    }
    updateBattleAndMercentary();
}

void MainScene::onButtonEvent(Ref* target,Widget::TouchEventType type){
    Widget* btn = dynamic_cast<Widget*>(target);
    if (btn == nullptr) {
        return;
    }
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            if (dynamic_cast<ImageView*>(target)!=nullptr) {
                PopBtn(btn);
            }
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            switch (btn->getTag()) {
                case BTN_START:
                    onStartClick();
                    break;
                case BTN_WEAPON:
                    onWeapon();
                    break;
                case BTN_ABILITY:
                    onAbility();
                    break;
                case BTN_CHALLENGE:
                    onChallenge();
                    break;
                case BTN_SHOP:
                    onShop();
                    break;
                case BTN_BATTLE:
                    onBattle();
                    break;
                case BTN_MERCENTARY:
                    onMercentary();
                    break;
                case BTN_BUY_WEAPON:
                    onWeapon();
                    break;
                case BTN_BACK:
                    onBack();
                    break;
                case BTN_BACK_TO_MAIN:
                    onBackToMain();
                    break;
                case BTN_COIN_ADD:
                    onCoinAdd();
                    break;
                case BTN_MONEY_ADD:
                    onMoneyAdd();
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}



void MainScene::onStartClick(){
    log("onStartClick");
    changeToBattle();
}

void MainScene::onWeapon(){
    //log("onWeaponClick");
    Window_Weapon::show(this);
}
void MainScene::onAbility(){
    Window_Ability::show(this);
    //log("onAbilityClick");
}
void MainScene::onChallenge(){
    Window_Task::show(this);
    //log("onChallengeClick");
}
void MainScene::onShop(){
    Window_Shop::show(this);
    //log("onShopClick");
}

void MainScene::onBackToMain(){
    log("onBackToMainClick");
    changeToMain();
}

void MainScene::onBack(){
    setTouchEnable(false);
    m_top_left_0->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pLeft,_pTop+120)),nullptr));
    m_weapon_bg_0->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pLeft-500,441)),CallFunc::create([&](){changeScene(M_SCENE_MENU);}),nullptr));
    m_weapon_bg_1->runAction(Sequence::create(DelayTime::create(0.1f),MoveTo::create(0.2f, Point(_pLeft-500,270)),nullptr));
    m_knife_bg->runAction(Sequence::create(DelayTime::create(0),MoveTo::create(0.2f, Point(_pLeft-500,125)),nullptr));
    m_bottom->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pCenterX,_pBottom-65)),nullptr));
    m_right_bottom->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.2f, Point(_pRight,_pBottom-65)),nullptr));
    m_man->runAction(Sequence::create(DelayTime::create(0.2f),FadeTo::create(0.3f, 60),nullptr));
    m_man->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.3f, Point(_pRight+180,305)),nullptr));
    m_start_bg->runAction(Sequence::create(DelayTime::create(0.2f),MoveTo::create(0.3f, Point(_pRight+215,222)),nullptr));
}

void MainScene::onBattle(){
    log("onBattleClick");
    m_battle_type = 0;
    updateBattleAndMercentary();
    setTouchEnable(false);
    if (m_battle_window) {
        m_battle_window->m_close();
        m_battle_window->onWindowClosed = [&](){
            m_battle_window = Window_Battle::show(this,new WindowBattleParam(m_battle_type));
            m_battle_window->onStartGame = CC_CALLBACK_0(MainScene::StartGame, this);
            m_battle_window->onWindowIn = [&](){
                setTouchEnable(true);
            };
        };
    }
}

void MainScene::onMercentary(){
    log("onMercentaryClick");
    m_battle_type = 1;
    updateBattleAndMercentary();
    setTouchEnable(false);
    if (m_battle_window) {
        m_battle_window->m_close();
        m_battle_window->onWindowClosed = [&](){
            m_battle_window = Window_Battle::show(this,new WindowBattleParam(m_battle_type));
            m_battle_window->onStartGame = CC_CALLBACK_0(MainScene::StartGame, this);
            m_battle_window->onWindowIn = [&](){
                setTouchEnable(true);
            };
        };
    }

}

void MainScene::updateBattleAndMercentary(){
    ImageView* btn_battle = dynamic_cast<ImageView*>(m_btns[BTN_BATTLE]);
    ImageView* btn_Mercentary = dynamic_cast<ImageView*>(m_btns[BTN_MERCENTARY]);
    if (m_battle_type == 0) {//у╫рш
        btn_battle->loadTexture("ccs/main/btn_battle_selected.png");
        btn_Mercentary->loadTexture("ccs/main/btn_mercentary_unselected.png");
        btn_battle->setTouchEnabled(false);
        btn_Mercentary->setTouchEnabled(true);
    }else{
        btn_battle->loadTexture("ccs/main/btn_battle_unselected.png");
        btn_Mercentary->loadTexture("ccs/main/btn_mercentary_selected.png");
        btn_battle->setTouchEnabled(true);
        btn_Mercentary->setTouchEnabled(false);
    }
}


void MainScene::onCoinAdd(){
    Window_Shop::show(this);
}

void MainScene::onMoneyAdd(){
    Window_Shop::show(this);
}

void MainScene::updateCoin(EventCustom* event){
    log("Main_UpdateCoin");
    if (num_coin) {
        num_coin->setString(to_string(G::getCoin()));
        PopBtn(num_coin);
    }
}

void MainScene::updateMoney(EventCustom* event){
    log("Main_UpdateMoney");
    if (num_money) {
        num_money->setString(to_string(G::getMoney()));
        PopBtn(num_money);
    }
}

void MainScene::StartGame(){
    changeScene(M_SCENE_GAME);
}
