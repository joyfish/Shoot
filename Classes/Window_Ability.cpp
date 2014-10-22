//
//  Window_Ability.cpp
//  Shoot
//
//  Created by wilford on 14-10-20.
//
//

#include "Window_Ability.h"
#include "HScrollViewBar.h"

void Window_Ability::init(void *data){
    
    m_tips = GUIReader::getInstance()->widgetFromJsonFile("ccs/Window_Ability.json");
    
    m_info_bg = ui::Helper::seekWidgetByName(m_tips, "stage_info_bg");
    m_info_bg->setOpacity(0);
    m_info_bg->setPosition(Point(-334,-58));
    
    m_black_block_1 = dynamic_cast<ImageView*>(ui::Helper::seekWidgetByName(m_tips,"black_block_1"));
    m_black_block_1->setScaleX(0.1f);
    m_black_block_2 = dynamic_cast<ImageView*>(ui::Helper::seekWidgetByName(m_tips,"black_block_2"));
    m_black_block_2->setScaleX(0.1f);
    
    Widget* stage_bg = ui::Helper::seekWidgetByName(m_tips, "stage_bg");
    ScrollView* m_scroll_view = dynamic_cast<ScrollView*>(ui::Helper::seekWidgetByName(stage_bg, "stage_list_container"));
    HScrollViewBar* bar = HScrollViewBar::create();
    stage_bg->addChild(bar);
    bar->setLocalZOrder(1);
    bar->setBackgroundImage("ccs/common/scroll_view_bar_bg.png", 460);
    bar->setForegroundImage("ccs/common/scroll_view_bar_fore.png");
    bar->attach(m_scroll_view, HSCROLLBAR_VERTICAL);
    bar->setRotation(-90);
    bar->setPosition(Point(508,10));
    
    
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_close"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(Window_Ability::onBtnEvent, this));
    }
    m_autoCenter = false;
    setAnimType(WINDOW_ANIM_RIGHT);
    
    for (int i=0; i<7; i++) {
        char item_name[30];
        sprintf(item_name,"stage_%d_bg",i);
        Widget* item = ui::Helper::seekWidgetByName(m_tips, item_name);
        item->addTouchEventListener(CC_CALLBACK_2(Window_Ability::onItemClick, this));
        item->setTouchEnabled(true);
        item->setTag(i);
    }
}


void Window_Ability::onStartAnimOver(){
    HWindow::onStartAnimOver();
    firstShowItem(0);
}


void Window_Ability::onBtnEvent(Ref* sender,Widget::TouchEventType type){
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
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void Window_Ability::onItemClick(cocos2d::Ref *sender, Widget::TouchEventType type){
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

void Window_Ability::firstShowItem(int id){
    setTocuhEnable(false);
    m_info_bg->runAction(Sequence::create(CCFadeIn::create(0.1f), NULL));
    m_info_bg->runAction(CCSequence::create(CCMoveTo::create(0.15f, Point(-714,-58)),CallFunc::create([&](){setTocuhEnable(true);}), NULL));
    m_black_block_1->runAction(Sequence::create(ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
    m_black_block_2->runAction(Sequence::create(ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
}

void Window_Ability::showItem(int id){
    setTocuhEnable(false);
    m_info_bg->runAction(Sequence::create(CCFadeOut::create(0.2f),CCFadeIn::create(0.1f), NULL));
    m_info_bg->runAction(CCSequence::create(CCMoveTo::create(0.2f, Point(-334,-58)),CCMoveTo::create(0.15f, Point(-714,-58)),CallFunc::create([&](){setTocuhEnable(true);}), NULL));
    m_black_block_1->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f, 1.0f), CCDelayTime::create(0.1f),ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
    m_black_block_2->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f, 1.0f),CCDelayTime::create(0.1f),ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
}


void Window_Ability::onCloseClick(){
    setTocuhEnable(false);
    m_info_bg->runAction(CCFadeOut::create(0.2f));
    m_info_bg->runAction(Sequence::create(CCMoveTo::create(0.2f, Point(-334,-58)),CallFunc::create([&](){closeWindow();}), NULL));
    m_black_block_1->runAction(ScaleTo::create(0.1f, 0.1f, 1.0f));
    m_black_block_2->runAction(ScaleTo::create(0.1f, 0.1f, 1.0f));
}

Window_Ability* Window_Ability::instance = nullptr;
