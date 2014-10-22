//
//  Window_Tips.cpp
//  Shoot
//
//  Created by wilford on 14/10/22.
//
//

#include "Window_Tips.h"
#include "Location.h"

void Window_Tips::init(void *data){
    m_tips = GUIReader::getInstance()->widgetFromJsonFile("ccs/Window_Tips.json");
    
    WindowTipsParam* param = static_cast<WindowTipsParam*>(data);
    if (param) {
        Node* bg = m_tips->getChildByName("bg");
        Label* m_label = Label::createWithSystemFont(loc(param->key), "", 27);
        m_label->setWidth(320);
        m_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
        m_label->setPosition(Point(40,410));
        m_label->setTextColor(Color4B(200,200,200,255));
        bg->addChild(m_label);
    }
    
    CC_SAFE_DELETE(param);

    
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_ok"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_close"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(Window_Tips::onBtnEvent, this));
    }
    m_autoCenter = false;
    setAnimType(WINDOW_ANIM_RIGHT);
}


void Window_Tips::onBtnEvent(Ref* sender,Widget::TouchEventType type){
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
                case BTN_OK:
                    onCloseClick();
                    break;
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


void Window_Tips::onCloseClick(){
    closeWindow();
}
