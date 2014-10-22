//
//  MenuScene.h
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#ifndef __Shooting__MenuScene__
#define __Shooting__MenuScene__

#include "HScene.h"

using namespace ui;
using namespace std;

class MenuScene : public HScene{
public:
    CREATE_FUNC(MenuScene);
    
    virtual void onEnter() override;
    
    virtual void onExit() override;
    
    

    
    virtual void loadResource() override{
        HScene::loadResource();
        addTextureName("ccs/menu/menu_bg.png");
        addTextureName("ccs/menu/menu_man.png");
        addTextureName("ccs/menu/menu_title.png");
    }
    
private:
    void onButtonEvent(Ref* target,Widget::TouchEventType type);
    
    void onStartClick();
    
    void onSettingClick();
    
    void onCloseClick();
    
    enum BTNS{
        BTN_START = 0,
        BTN_SETTING,
        BTN_CLOSE
    };
    
    Label* label;
    vector<Widget*> m_btns;
    
};

#endif /* defined(__Shooting__MenuScene__) */
