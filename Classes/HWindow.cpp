//
//  HWindow.cpp
//  Shooting
//
//  Created by wilford on 14-10-14.
//
//

#include "HWindow.h"

HWindow::HWindow()
:m_tips(nullptr)
,m_node(nullptr)
,m_windowsHelper(nullptr)
,onWindowClosed(nullptr)
,onWindowIn(nullptr)
,m_autoCenter(true)
,m_anim_type(WINDOW_ANIM_TOP)
{}

HWindow::~HWindow(){
    CC_SAFE_DELETE(m_windowsHelper);
    m_node = nullptr;
}

void HWindow::showWindow(){
    if(m_tips){
//         Layout* _panel = (Layout*)m_tips;
//        _panel->setSize(Size(_pScreenSize.width, _pScreenSize.height));
//        _panel->setBackGroundColorOpacity(128);
        m_node->addChild(m_tips);
    
        m_tips->setZOrder(HWindowsManager::S()->getTopZOrder());
        setZOrder(m_tips->getZOrder());
        Node* m_bg = m_tips->getChildByName("bg");
        if (m_autoCenter) {
            m_bg->setPosition(Point(_pCenterX,_pCenterY));
        }
        if (m_bg) {
            m_windowsHelper = new HWindowsHelper(m_bg);
        }
    }
    HWindowsManager::S()->pushWindow(this);
    setTocuhEnable(false);
    startAnim();
}

void HWindow::onClose(){
    HWindowsManager::S()->closeWindow(this);
}

void HWindow::close(){
    IHWindow::close();
    log("HWindow Close");
    if (m_tips) {
        m_tips->removeFromParentAndCleanup(true);
        m_tips = nullptr;
    }
}

void HWindow::setTocuhEnable(bool enabled){
    if (m_windowsHelper) {
        m_windowsHelper->setTouchEnable(enabled);
    }
}

void HWindow::closeWindow(){
    setTocuhEnable(false);
    endAnim();
}

void HWindow::startAnim(){
    if (m_tips) {
        Node* tips_bg = m_tips->getChildByName("bg");
        Point pre_pos = tips_bg->getPosition();
        
        switch (m_anim_type) {
            case WINDOW_ANIM_TOP:
                tips_bg->setPosition(Point(pre_pos.x, _pTop+480));
                tips_bg->runAction(Sequence::create(MoveTo::create(0.3f, Point(pre_pos.x, pre_pos.y-20)),MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y+10)),MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y)),CallFunc::create(CC_CALLBACK_0(HWindow::onStartAnimOver, this)), NULL));
                break;
            case WINDOW_ANIM_RIGHT:
                tips_bg->setPosition(Point(_pRight+640, pre_pos.y));
                tips_bg->runAction(Sequence::create(MoveTo::create(0.3f, Point(pre_pos.x-20, pre_pos.y)),MoveTo::create(0.1f, Point(pre_pos.x+10, pre_pos.y)),MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y)),CallFunc::create(CC_CALLBACK_0(HWindow::onStartAnimOver,this)),NULL));
                break;
            case WINDOW_ANIM_LEFT:
                tips_bg->setPosition(Point(_pLeft-640, pre_pos.y));
                tips_bg->runAction(Sequence::create(MoveTo::create(0.3f, Point(pre_pos.x+20, pre_pos.y)),MoveTo::create(0.1f, Point(pre_pos.x-10, pre_pos.y)),MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y)),CallFunc::create(CC_CALLBACK_0(HWindow::onStartAnimOver,this)),NULL));
                break;
            case WINDOW_ANIM_BOTTOM:
                tips_bg->setPosition(Point(pre_pos.x, _pBottom - 480));
                tips_bg->runAction(Sequence::create(MoveTo::create(0.3f, Point(pre_pos.x, pre_pos.y+20)),MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y-10)),MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y)),CallFunc::create(CC_CALLBACK_0(HWindow::onStartAnimOver, this)), NULL));
                break;
            default:
                onStartAnimOver();
                break;
        }
        
    }
}

void HWindow::onStartAnimOver(){
    setTocuhEnable(true);
    if (onWindowIn) {
        onWindowIn();
    }
}

void HWindow::endAnim(){
    if (m_tips!=NULL) {
        Node* tips_bg = m_tips->getChildByName("bg");
        Point pre_pos = tips_bg->getPosition();
        //tips_bg->runAction(CCSequence::create(CCDelayTime::create(0.3f),CCFadeOut::create(0.1f),NULL));
        switch (m_anim_type) {
            case WINDOW_ANIM_TOP:
                tips_bg->runAction(Sequence::create(MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y-20)),MoveTo::create(0.3f,Point(pre_pos.x, _pTop+480)),CallFuncN::create(CC_CALLBACK_0(HWindow::onCloseAnimOver,this )), NULL));
                break;
            case WINDOW_ANIM_RIGHT:
                tips_bg->runAction(Sequence::create(MoveTo::create(0.1f, Point(pre_pos.x-20, pre_pos.y)),MoveTo::create(0.3f,Point(_pRight+640, pre_pos.y)),CallFuncN::create(CC_CALLBACK_0(HWindow::onCloseAnimOver, this)), NULL));
                break;
            case WINDOW_ANIM_LEFT:
                tips_bg->runAction(Sequence::create(MoveTo::create(0.1f, Point(pre_pos.x+20, pre_pos.y)),MoveTo::create(0.3f,Point(_pLeft-640, pre_pos.y)),CallFuncN::create(CC_CALLBACK_0(HWindow::onCloseAnimOver, this)), NULL));
                break;
            case WINDOW_ANIM_BOTTOM:
                tips_bg->runAction(Sequence::create(MoveTo::create(0.1f, Point(pre_pos.x, pre_pos.y+20)),MoveTo::create(0.3f,Point(pre_pos.x, _pBottom-480)),CallFuncN::create(CC_CALLBACK_0(HWindow::onCloseAnimOver,this )), NULL));
                break;
            default:
                onCloseAnimOver();
                break;
        }
    }
}

void HWindow::onCloseAnimOver(){
    if (onWindowClosed) {
        onWindowClosed();
    }
    onClose();
}