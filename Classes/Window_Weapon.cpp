//
//  Window_Weapon.cpp
//  Shoot
//
//  Created by wilford on 14-10-21.
//
//

#include "Window_Weapon.h"
#include "HScrollViewBar.h"
#include "Window_Shop.h"

Window_Weapon::Window_Weapon()
:_coin_listener(nullptr),_money_listener(nullptr)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    _coin_listener = EventListenerCustom::create(EVENT_COIN_UPDATE, CC_CALLBACK_1(Window_Weapon::updateCoin, this));
    _money_listener = EventListenerCustom::create(EVENT_MONEY_UPDATE, CC_CALLBACK_1(Window_Weapon::updateMoney, this));
    dispatcher->addEventListenerWithFixedPriority(_coin_listener, 1);
    dispatcher->addEventListenerWithFixedPriority(_money_listener, 1);
}

Window_Weapon::~Window_Weapon(){
    if (_coin_listener) {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_coin_listener);
    }
    if (_money_listener) {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_money_listener);
    }
}

void Window_Weapon::init(void *data){
    
    m_tips = GUIReader::getInstance()->widgetFromJsonFile("ccs/Window_Weapon.json");
    
    m_info_bg = ui::Helper::seekWidgetByName(m_tips, "weapon_bg");
    m_info_bg->setOpacity(0);
    m_info_bg->setPosition(Point(300,18));
    ScrollView* m_weapon_scrollview = dynamic_cast<ScrollView*>(ui::Helper::seekWidgetByName(m_info_bg, "weapon_container"));
    HScrollViewBar* weapon_bar = HScrollViewBar::create();
    m_info_bg->addChild(weapon_bar);
    weapon_bar->setLocalZOrder(1);
    weapon_bar->setBackgroundImage("ccs/common/scroll_view_bar_bg.png", 510);
    weapon_bar->setForegroundImage("ccs/common/scroll_view_bar_fore.png");
    weapon_bar->attach(m_weapon_scrollview, HSCROLLBAR_VERTICAL);
    weapon_bar->setRotation(-90);
    weapon_bar->setPosition(Point(605,10));
    
    m_black_block_1 = dynamic_cast<ImageView*>(ui::Helper::seekWidgetByName(m_tips,"black_block_1"));
    m_black_block_1->setScaleX(0.1f);
    m_black_block_2 = dynamic_cast<ImageView*>(ui::Helper::seekWidgetByName(m_tips,"black_block_2"));
    m_black_block_2->setScaleX(0.1f);
    
    Widget* stage_bg = ui::Helper::seekWidgetByName(m_tips, "weapon_type_bg");
    ScrollView* m_scroll_view = dynamic_cast<ScrollView*>(ui::Helper::seekWidgetByName(stage_bg, "weapon_type_container"));
    HScrollViewBar* bar = HScrollViewBar::create();
    stage_bg->addChild(bar);
    bar->setLocalZOrder(1);
    bar->setBackgroundImage("ccs/common/scroll_view_bar_bg.png", 490);
    bar->setForegroundImage("ccs/common/scroll_view_bar_fore.png");
    bar->attach(m_scroll_view, HSCROLLBAR_VERTICAL);
    bar->setRotation(-90);
    bar->setPosition(Point(310,10));
    
    for (int i=0; i<8; i++) {
        char item_name[30];
        sprintf(item_name,"type_bg_%d",i);
        Widget* item = ui::Helper::seekWidgetByName(m_tips, item_name);
        item->addTouchEventListener(CC_CALLBACK_2(Window_Weapon::onItemClick, this));
        item->setTouchEnabled(true);
        item->setTag(i);
    }
    
    m_right_bottom = ui::Helper::seekWidgetByName(m_tips, "right_bottom");
    
    
    num_coin = dynamic_cast<TextAtlas*>(ui::Helper::seekWidgetByName(m_tips, "num_coin"));
    num_money = dynamic_cast<TextAtlas*>(ui::Helper::seekWidgetByName(m_tips, "num_money"));
    num_coin->setString(to_string(G::getCoin()));
    num_money->setString(to_string(G::getMoney()));
    
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_close"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_coin_add"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_money_add"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(Window_Weapon::onBtnEvent, this));
    }
    m_autoCenter = false;
    setAnimType(WINDOW_ANIM_RIGHT);
}


void Window_Weapon::startAnim(){
    HWindow::startAnim();
    m_right_bottom->setPosition(Point(_pRight,_pBottom-65));
    m_right_bottom->runAction(MoveTo::create(0.2f, Point(_pRight,_pBottom)));
}

void Window_Weapon::onStartAnimOver(){
    HWindow::onStartAnimOver();
    firstShowItem(0);
}


void Window_Weapon::onBtnEvent(Ref* sender,Widget::TouchEventType type){
    Widget* btn = dynamic_cast<Widget*>(sender);
    if (btn==nullptr) {
        return;
    }
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            if (dynamic_cast<ImageView*>(sender)!=nullptr) {
                PopBtn(btn);
            }
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            switch (btn->getTag()) {
                case BTN_CLOSE:
                    onCloseClick();
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

void Window_Weapon::onItemClick(cocos2d::Ref *sender, Widget::TouchEventType type){
    Widget* btn = dynamic_cast<Widget*>(sender);
    if (btn==nullptr) {
        return;
    }
    switch (type) {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            showItem(btn->getTag());
            break;
            
        default:
            break;
    }
}

void Window_Weapon::firstShowItem(int id){
    setTocuhEnable(false);
    m_info_bg->runAction(Sequence::create(CCFadeIn::create(0.1f), NULL));
    m_info_bg->runAction(CCSequence::create(CCMoveTo::create(0.15f, Point(-333,18)),CallFunc::create([&](){setTocuhEnable(true);}), NULL));
    m_black_block_1->runAction(Sequence::create(ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
    m_black_block_2->runAction(Sequence::create(ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
}

void Window_Weapon::showItem(int id){
    setTocuhEnable(false);
    m_info_bg->runAction(Sequence::create(CCFadeOut::create(0.2f),CCFadeIn::create(0.1f), NULL));
    m_info_bg->runAction(CCSequence::create(CCMoveTo::create(0.2f, Point(300,18)),CCMoveTo::create(0.15f, Point(-333,18)),CallFunc::create([&](){setTocuhEnable(true);}), NULL));
    m_black_block_1->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f, 1.0f), CCDelayTime::create(0.1f),ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
    m_black_block_2->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f, 1.0f),CCDelayTime::create(0.1f),ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
}


void Window_Weapon::onCloseClick(){
    setTocuhEnable(false);
    m_info_bg->runAction(CCFadeOut::create(0.2f));
    m_info_bg->runAction(Sequence::create(CCMoveTo::create(0.2f, Point(300,18)),CallFunc::create([&](){closeWindow();}), NULL));
    m_black_block_1->runAction(ScaleTo::create(0.1f, 0.1f, 1.0f));
    m_black_block_2->runAction(ScaleTo::create(0.1f, 0.1f, 1.0f));
    m_right_bottom->runAction(MoveTo::create(0.2f, Point(_pRight,_pBottom-65)));
}

void Window_Weapon::updateCoin(EventCustom* event){
    if (num_coin) {
        num_coin->setString(to_string(G::getCoin()));
        PopBtn(num_coin);
    }
}

void Window_Weapon::updateMoney(EventCustom* event){
    if (num_money) {
        num_money->setString(to_string(G::getMoney()));
        PopBtn(num_money);
    }
}

void Window_Weapon::onCoinAdd(){
    //Window_Shop::show(m_node);
    G::AddCoin(1000);
}

void Window_Weapon::onMoneyAdd(){
    //Window_Shop::show(m_node);
    G::AddMoney(10);
}

Window_Weapon* Window_Weapon::instance = nullptr;