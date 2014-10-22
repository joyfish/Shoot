//
//  MenuScene.cpp
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#include "MenuScene.h"
#include "MainScene.h"
#include "Window_Setting.h"
#include "Window_Quit.h"
#include "Window_Tips.h"


void MenuScene::onEnter(){
    HScene::onEnter();
    Widget* menu_bg = GUIReader::getInstance()->widgetFromJsonFile("ccs/Menu.json");
    scene_bg->addChild(menu_bg);
    Node* light = ui::Helper::seekWidgetByName(menu_bg, "light");
    if (light) {
        light->runAction(RepeatForever::create(RotateBy::create(1.0f, -60)));
    }
    Node* title = ui::Helper::seekWidgetByName(menu_bg, "title");
    if (title) {
        title->setScale(2);
        title->runAction(ScaleTo::create(0.1f, 1));
        title->setOpacity(80);
        title->runAction(FadeTo::create(0.05f,255));
    }
    
    m_btns.push_back(ui::Helper::seekWidgetByName(menu_bg, "start"));
    m_btns.push_back(ui::Helper::seekWidgetByName(menu_bg, "btn_setting"));
    m_btns.push_back(ui::Helper::seekWidgetByName(menu_bg, "btn_close"));
    
    int tag = 0;
    for (auto btn :m_btns) {
        btn->setTag(tag++);
        btn->setTouchEnabled(true);
        btn->addTouchEventListener(CC_CALLBACK_2(MenuScene::onButtonEvent, this));
    }
}

void MenuScene::onExit(){
    HScene::onExit();
}

void MenuScene::onButtonEvent(Ref* target,Widget::TouchEventType type){
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
                case BTN_CLOSE:
                    onCloseClick();
                    break;
                case BTN_SETTING:
                    onSettingClick();
                    break;
                    
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void MenuScene::onSettingClick(){
    Window_Setting::show(this);
}

void MenuScene::onStartClick(){
    changeScene(M_SCENE_MAIN);
    log("onStartClick");
}

void MenuScene::onCloseClick(){
    Window_Quit::show(this);
}