//
//  Window_Battle.cpp
//  Shoot
//
//  Created by wilford on 14-10-20.
//
//

#include "Window_Battle.h"
#include "HScrollViewBar.h"

void Window_Battle::init(void *data){
    WindowBattleParam* param = static_cast<WindowBattleParam*>(data);
    m_battle_type = 0;
    if (param) {
        m_battle_type = param->battle_id;
    }
    
    m_tips = GUIReader::getInstance()->widgetFromJsonFile("ccs/Window_Battle.json");
    
    ImageView* title_label = dynamic_cast<ImageView*>(ui::Helper::seekWidgetByName(m_tips, "title_label"));
    if (m_battle_type == 0) {//战役
        title_label->loadTexture("ccs/stage/label_battle.png");
    }else if(m_battle_type == 1){//佣兵
        title_label->loadTexture("ccs/stage/label_mercentary.png");
    }
    
    m_stage_info_bg = ui::Helper::seekWidgetByName(m_tips, "stage_info_bg");
    m_stage_info_bg->setOpacity(0);
    m_stage_info_bg->setPosition(Point(-334,-58));
    
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
    
    
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_start"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(Window_Battle::onBtnEvent, this));
    }
    m_autoCenter = false;
    setAnimType(WINDOW_ANIM_RIGHT);
    
    for (int i=0; i<7; i++) {
        char item_name[30];
        sprintf(item_name,"stage_%d_bg",i);
        Widget* item = ui::Helper::seekWidgetByName(m_tips, item_name);
        item->addTouchEventListener(CC_CALLBACK_2(Window_Battle::onItemClick, this));
        item->setTouchEnabled(true);
        item->setTag(i);
    }
}

void Window_Battle::startAnim(){
    if (m_tips) {
        Node* tips_bg = m_tips->getChildByName("bg");
        Point pre_pos = tips_bg->getPosition();
        tips_bg->setPosition(Point(_pRight+900, pre_pos.y));
        tips_bg->runAction(Sequence::create(MoveTo::create(0.3f, Point(pre_pos.x-20, pre_pos.y)),MoveTo::create(0.1f, Point(pre_pos.x+10, pre_pos.y)),MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y)),CallFunc::create(CC_CALLBACK_0(Window_Battle::onStartAnimOver,this)),NULL));
    }
}

void Window_Battle::onStartAnimOver(){
    HWindow::onStartAnimOver();
    firstShowItem(0);
}

void Window_Battle::endAnim(){
    if (m_tips) {
        Node* tips_bg = m_tips->getChildByName("bg");
        Point pre_pos = tips_bg->getPosition();
        tips_bg->runAction(Sequence::create(MoveTo::create(0.1f, Point(pre_pos.x-20, pre_pos.y)),MoveTo::create(0.3f,Point(_pRight+900, pre_pos.y)),CallFuncN::create(CC_CALLBACK_0(Window_Battle::onCloseAnimOver, this)), NULL));
    }
}

void Window_Battle::onBtnEvent(Ref* sender,Widget::TouchEventType type){
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
                case BTN_START:
                    onStartClick();
                    break;
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void Window_Battle::onItemClick(cocos2d::Ref *sender, Widget::TouchEventType type){
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

void Window_Battle::firstShowItem(int id){
    setTocuhEnable(false);
    m_stage_info_bg->runAction(Sequence::create(CCFadeIn::create(0.1f), NULL));
    m_stage_info_bg->runAction(CCSequence::create(CCMoveTo::create(0.15f, Point(-714,-58)),CallFunc::create([&](){setTocuhEnable(true);}), NULL));
    m_black_block_1->runAction(Sequence::create(ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
    m_black_block_2->runAction(Sequence::create(ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
}

void Window_Battle::showItem(int id){
    setTocuhEnable(false);
    m_stage_info_bg->runAction(Sequence::create(CCFadeOut::create(0.2f),CCFadeIn::create(0.1f), NULL));
    m_stage_info_bg->runAction(CCSequence::create(CCMoveTo::create(0.2f, Point(-334,-58)),CCMoveTo::create(0.15f, Point(-714,-58)),CallFunc::create([&](){setTocuhEnable(true);}), NULL));
    m_black_block_1->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f, 1.0f), CCDelayTime::create(0.1f),ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
    m_black_block_2->runAction(Sequence::create(ScaleTo::create(0.1f, 0.1f, 1.0f),CCDelayTime::create(0.1f),ScaleTo::create(0.15f, 1.0f, 1.0f),NULL));
}

void Window_Battle::m_close(){
    setTocuhEnable(false);
    m_stage_info_bg->runAction(CCFadeOut::create(0.2f));
    m_stage_info_bg->runAction(Sequence::create(CCMoveTo::create(0.2f, Point(-334,-58)),CallFunc::create([&](){closeWindow();}), NULL));
    m_black_block_1->runAction(ScaleTo::create(0.1f, 0.1f, 1.0f));
    m_black_block_2->runAction(ScaleTo::create(0.1f, 0.1f, 1.0f));
}

void Window_Battle::onStartClick(){
    log("onStartClick");
    if (onStartGame) {
        onStartGame();
    }
}

