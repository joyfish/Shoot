//
//  Window_Shop.cpp
//  Shoot
//
//  Created by wilford on 14-10-20.
//
//

#include "Window_Shop.h"

void Window_Shop::init(void *data){
    
    m_tips = GUIReader::getInstance()->widgetFromJsonFile("ccs/Window_Shop.json");
    
    
    
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_close"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(Window_Shop::onBtnEvent, this));
    }
    m_autoCenter = false;
    setAnimType(WINDOW_ANIM_RIGHT);
}


void Window_Shop::onBtnEvent(Ref* sender,Widget::TouchEventType type){
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


void Window_Shop::onCloseClick(){
    closeWindow();
}

Window_Shop* Window_Shop::instance = nullptr;