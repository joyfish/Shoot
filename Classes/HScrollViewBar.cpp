//
//  HScrollViewBar.cpp
//  Shoot
//
//  Created by wilford on 14-10-20.
//
//

#include "HScrollViewBar.h"

HScrollViewBar::HScrollViewBar():
m_background(NULL),
m_foreground(NULL),
m_bar_end_x(0),
m_bar_start_x(0),
m_percent(100),
m_scrollview_container(0),
m_scrollview_inner(0),
m_scroll_dir(HSCROLLBAR_VERTICAL)
{
    
}

//HScrollViewBar::~HScrollViewBar(){
//    if (m_background) {
//        m_background->removeFromParentAndCleanup(true);
//    }
//    if (m_foreground) {
//        m_foreground->removeFromParentAndCleanup(true);
//    }
//}

void HScrollViewBar::onEnter(){
    Node::onEnter();
    scheduleUpdate();
}

void HScrollViewBar::attach(ScrollView *view,HSCROLLBAR_DIR dir){
    if (view == NULL) {
        return;
    }
    attachView = view;
    m_scroll_dir = dir;
    switch (dir) {
        case HSCROLLBAR_VERTICAL:
            m_scrollview_inner = attachView->getContentSize().height;
            m_scrollview_container = attachView->getInnerContainerSize().height;
            break;
        case HSCROLLBAR_HORIZONTAL:
            m_scrollview_inner = attachView->getContentSize().width;
            m_scrollview_container =attachView->getInnerContainerSize().width;
            break;
        default:
            break;
    }
    restBarSize();
}

void HScrollViewBar::setBackgroundImage(const char *fileName,float width){
    if (m_background==NULL) {
        m_background = ImageView::create();
        this->addChild(m_background);
        m_background->setZOrder(0);
    }
    m_background->loadTexture(fileName);
    Size image_size = m_background->getContentSize();
    m_background->setScale9Enabled(true);
    m_background->setCapInsets(Rect(11, 11, 43, 2));
    m_background->setContentSize(Size(width, image_size.height));
    m_background->setAnchorPoint(_nLeft);
    m_background->setPosition(Point::ZERO);
    restBarSize();
}

void HScrollViewBar::setForegroundImage(const char *fileName){
    if (m_foreground == NULL) {
        m_foreground = ImageView::create();
        this->addChild(m_foreground);
        m_foreground->setZOrder(1);
    }
    m_foreground->loadTexture(fileName);
    Size image_size = m_foreground->getContentSize();
    m_foreground->setScale9Enabled(true);
    m_foreground->setCapInsets(Rect(11, 11, 43, 2));
    m_foreground->setContentSize(image_size);
    m_foreground->setAnchorPoint(_nLeft);
    m_foreground->setPosition(Point::ZERO);
    restBarSize();
}

void HScrollViewBar::restBarSize(){
    if (m_scrollview_inner==0||m_scrollview_container==0) {
        setVisible(false);
        return;
    }
    if (m_background==NULL||m_foreground == NULL) {
        return;
    }
    
    Size backgroundSize = m_background->getContentSize();
    
    float sizepercent = m_scrollview_inner/m_scrollview_container;
    
    if (sizepercent>1) {
        sizepercent =1;
    }
    
    if (sizepercent==1) {
        setVisible(false);
    }else
        setVisible(true);
    
    m_foreground->setContentSize(Size(backgroundSize.width*sizepercent, m_foreground->getContentSize().height));
    
    m_bar_end_x = m_background->getContentSize().width - m_foreground->getContentSize().width;
}

void HScrollViewBar::setPercent(int percent){
    if (m_foreground==NULL||m_bar_end_x ==0) {
        return;
    }
    percent = MAX(0, percent);
    percent = MIN(100, percent);
    
    m_foreground->setPosition(Point(m_bar_end_x*percent/100, 0));
}

void HScrollViewBar::update(float dt){
    Node::update(dt);
    updateBar();
}

void HScrollViewBar::updateBar(){
    if (attachView==NULL) {
        return;
    }
    Layout* inner = attachView->getInnerContainer();
    
    bool bSizeChanged = false;
    
    switch (m_scroll_dir) {
        case HSCROLLBAR_HORIZONTAL:
        {
            if (m_scrollview_container!=inner->getContentSize().width) {
                m_scrollview_container = inner->getContentSize().width;
                bSizeChanged = true;
            }
            if (m_scrollview_inner!=attachView->getContentSize().width) {
                m_scrollview_inner = attachView->getContentSize().width;
                bSizeChanged = true;
            }
            if (bSizeChanged) {
                restBarSize();
            }
            
            float maxW = inner->getContentSize().width- attachView->getContentSize().width;
            maxW = MAX(0, maxW);
            float offsetX = abs(inner->getPosition().x);
            offsetX=MIN(maxW, offsetX);
            setPercent((offsetX)*100/maxW);
        }
            break;
        case HSCROLLBAR_VERTICAL:{
            if (m_scrollview_container!=inner->getContentSize().height) {
                m_scrollview_container = inner->getContentSize().height;
                bSizeChanged = true;
            }
            
            if (m_scrollview_inner!=attachView->getContentSize().height) {
                m_scrollview_inner = attachView->getContentSize().height;
                bSizeChanged = true;
            }
            
            if (bSizeChanged) {
                restBarSize();
            }
            float maxH = inner->getContentSize().height-attachView->getContentSize().height;
            maxH = MAX(0, maxH);
            float offsetY = abs(inner->getPosition().y);
            offsetY=MIN(maxH, offsetY);
            setPercent((offsetY)*100/maxH);
        }
            break;
            
        default:
            break;
    }
}


