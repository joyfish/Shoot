//
//  Window_Setting.cpp
//  Shoot
//
//  Created by wilford on 14-10-17.
//
//

#include "Window_Setting.h"

void Window_Setting::init(void *data){
    m_tips = GUIReader::getInstance()->widgetFromJsonFile("ccs/Window_Setting.json");
    
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_effect_off"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_effect_on"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_music_off"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_music_on"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_save"));
    m_btns.push_back(ui::Helper::seekWidgetByName(m_tips, "btn_close"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(Window_Setting::onBtnEvent, this));
    }
    
    updateEffectBtns();
    updateMusicBtns();
    
    m_autoCenter = false;
    setAnimType(WINDOW_ANIM_RIGHT);
}

void Window_Setting::onBtnEvent(Ref* sender,Widget::TouchEventType type){
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
                case BTN_EFFECT_OFF:
                    G::setEffectState(false);
                    updateEffectBtns();
                    break;
                case BTN_EFFECT_ON:
                    G::setEffectState(true);
                    updateEffectBtns();
                    break;
                case BTN_MUSIC_OFF:
                    G::setBackGroundMusicState(false);
                    updateMusicBtns();
                    break;
                case BTN_MUSIC_ON:
                    G::setBackGroundMusicState(true);
                    updateMusicBtns();
                    break;
                case BTN_SAVE:
                    onSaveClick();
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

void Window_Setting::updateEffectBtns(){
    log("updateEffectBtns");
    if (G::isEffectOn()) {
        dynamic_cast<ImageView*>(m_btns.at(BTN_EFFECT_ON))->loadTexture("ccs/setting/sound_on_selected.png");
        dynamic_cast<ImageView*>(m_btns.at(BTN_EFFECT_OFF))->loadTexture("ccs/setting/sound_off_unselected.png");
    }else{
        dynamic_cast<ImageView*>(m_btns.at(BTN_EFFECT_ON))->loadTexture("ccs/setting/sound_on_unselected.png");
        dynamic_cast<ImageView*>(m_btns.at(BTN_EFFECT_OFF))->loadTexture("ccs/setting/sound_off_selected.png");
    }
}

void Window_Setting::updateMusicBtns(){
    log("update_MusicBtns");
    if (G::isBackGroundMusicOn()) {
        dynamic_cast<ImageView*>(m_btns.at(BTN_MUSIC_ON))->loadTexture("ccs/setting/sound_on_selected.png");
        dynamic_cast<ImageView*>(m_btns.at(BTN_MUSIC_OFF))->loadTexture("ccs/setting/sound_off_unselected.png");
    }else{
        dynamic_cast<ImageView*>(m_btns.at(BTN_MUSIC_ON))->loadTexture("ccs/setting/sound_on_unselected.png");
        dynamic_cast<ImageView*>(m_btns.at(BTN_MUSIC_OFF))->loadTexture("ccs/setting/sound_off_selected.png");
    }
}

void Window_Setting::onSaveClick(){
    closeWindow();
}

void Window_Setting::onCloseClick(){
    closeWindow();
}


Window_Setting* Window_Setting::instance = nullptr;