//
//  HWindowsHelper.cpp
//  Shooting
//
//  Created by wilford on 14-10-14.
//
//

#include "HWindowsHelper.h"


HWindowsHelper::HWindowsHelper(Node* node):
m_node(node)
{}

HWindowsHelper::HWindowsHelper(){
    if (m_touchEnabledchildren.size()>0) {
        m_touchEnabledchildren.clear();
    }
}

void HWindowsHelper::setTouchEnable(bool enabled){
    if (enabled) {
        for (auto enabledchild: m_touchEnabledchildren) {
            enabledchild->setTouchEnabled(true);
        }
        m_touchEnabledchildren.clear();
    }else{
        touchDisable(m_node);
    }
}

void HWindowsHelper::touchDisable(Node* node){
    if (node == nullptr) {
        return;
    }
    
    std::function<void(Node*)> disableChid = [&](Node* node){
        if (node->getChildrenCount()==0) {
            return;
        }
        for (auto child : node->getChildren()) {
            Widget* widget = dynamic_cast<Widget*>(child);
            if (widget) {
                if (widget->isTouchEnabled()) {
                    m_touchEnabledchildren.push_back(widget);
                    widget->setTouchEnabled(false);
                }
            }
            if (child->getChildrenCount()>0) {
                disableChid(child);
            }
        }
    };
    
    Widget* widget = dynamic_cast<Widget*>(node);
    if (widget) {
        if (widget->isTouchEnabled()) {
            m_touchEnabledchildren.push_back(widget);
            widget->setTouchEnabled(false);
        }
    }
    disableChid(node);
}