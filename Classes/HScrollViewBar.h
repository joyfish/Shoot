//
//  HScrollViewBar.h
//  Shoot
//
//  Created by wilford on 14-10-20.
//
//

#ifndef __Shoot__HScrollViewBar__
#define __Shoot__HScrollViewBar__

#include "cocos2d.h"
#include "ScreenFit.h"
#include "cocostudio/Cocostudio.h"
#include "ui/CocosGUI.h"


using namespace cocostudio;
using namespace ui;
USING_NS_CC;


enum HSCROLLBAR_DIR{
    HSCROLLBAR_VERTICAL=0,
    HSCROLLBAR_HORIZONTAL
};

class   HScrollViewBar : public Node{
public:
    HScrollViewBar();
   // ~HScrollViewBar();
    
    CREATE_FUNC(HScrollViewBar);
    
    virtual void onEnter();
    
    void attach(ScrollView* view,HSCROLLBAR_DIR dir);
    
    void setBackgroundImage(const char* fileName,float width);
    void setForegroundImage(const char* fileName);
    
    void restBarSize();
    
    void setPercent(int percent);
    
    virtual void update(float dt);
    
    void updateBar();
private:
    
    ImageView* m_background;
    ImageView* m_foreground;
    int m_percent;
    float m_bar_start_x;
    float m_bar_end_x;
    float m_scrollview_inner;
    float m_scrollview_container;
    ScrollView* attachView;
    HSCROLLBAR_DIR m_scroll_dir;
};


#endif /* defined(__Shoot__HScrollViewBar__) */
