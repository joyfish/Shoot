//
//  Window_Quit.cpp
//  Shoot
//
//  Created by wilford on 14/10/22.
//
//

#include "Window_Quit.h"
#include "Location.h"

void Window_Quit::init(void *data){
    
    m_tips = GUIReader::getInstance()->widgetFromJsonFile("ccs/Window_Quit.json");
    
    Node* bg = m_tips->getChildByName("bg");
    Label* m_label = Label::createWithSystemFont(loc("quit_game"), "", 27);
    m_label->setWidth(320);
    m_label->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
    m_label->setPosition(Point(40,410));
    m_label->setTextColor(Color4B(200,200,200,255));
    bg->addChild(m_label);
//    RichText* _richText =  RichText::create();
//    _richText->ignoreContentAdaptWithSize(false);
//    _richText->setContentSize(Size(320,288));
//    RichElementText* re1 = RichElementText::create(1, Color3B::YELLOW, 255, loc("quit_game"), "", 27);
//    RichElementText* re2 = RichElementText::create(1, Color3B::YELLOW, 255, loc("test"), "", 27);
//    _richText->pushBackElement(re1);
//    _richText->pushBackElement(re2);
//    _richText->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
//    bg->addChild(_richText);
    //_richText->setPosition(Point(34,123));
    
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_ok"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_cancel"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_close"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(Window_Quit::onBtnEvent, this));
    }
    m_autoCenter = false;
    setAnimType(WINDOW_ANIM_RIGHT);
}


void Window_Quit::onBtnEvent(Ref* sender,Widget::TouchEventType type){
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
                    onOKClick();
                    break;
                case BTN_CANCEL:
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

void Window_Quit::onOKClick(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

}

void Window_Quit::onCloseClick(){
    closeWindow();
}

Window_Quit* Window_Quit::instance = nullptr;