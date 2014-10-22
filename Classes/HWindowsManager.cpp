//
//  HWindowsManager.cpp
//  Shooting
//
//  Created by wilford on 14-10-14.
//
//

#include "HWindowsManager.h"

#define PopWindowMinZOrder 50;
#define PopWindowPadding 10;

HWindowsManager* HWindowsManager::S(){
    if (m_instance==NULL) {
        m_instance = new HWindowsManager();
    }
    return m_instance;
}

void HWindowsManager::pushWindow(IHWindow *window){
    m_windows.pushBack(window);
    CCLOG("[openWindow] -> [windows count] = %ld",m_windows.size());
}

void HWindowsManager::closeWindow(IHWindow *window){
    if (!window) {
        return;
    }
    
    for (auto w : m_windows) {
        if (window == w ) {
            m_windows.eraseObject(window);
        }
    }

    m_toclose.pushBack(window);
}

void HWindowsManager::closeAllWindows(){
    for (auto w : m_windows) {
        w->close();
        CC_SAFE_DELETE(w);
    }
    m_windows.clear();
    CCLOG("[closeAllWindows] -> [windows count] = %ld",m_windows.size());
}

void HWindowsManager::clearToClose(){
    for (auto w : m_toclose) {
        w->close();
        CC_SAFE_DELETE(w);
    }
    m_toclose.clear();
}

void HWindowsManager::update(float dt){
    clearToClose();
    updateWindows(dt);
}

void HWindowsManager::updateWindows(float dt){
    for(auto w : m_windows){
        w->update(dt);
    }
}

void HWindowsManager::popWindow(){
    closeWindow(m_windows.at(m_windows.size()-1));
}

int HWindowsManager::getTopZOrder(){
    int zOrder = PopWindowMinZOrder;
    for (auto w : m_windows) {
        if (zOrder<w->getZOrder()) {
            zOrder = w->getZOrder();
        }
    }
    int returnZOrder = zOrder+PopWindowPadding;
    log("[Windows topZOrder] = %d",zOrder);
    return returnZOrder;
}

HWindowsManager::HWindowsManager(){
}

HWindowsManager::~HWindowsManager(){
    
    m_windows.clear();
    
    m_toclose.clear();
}

HWindowsManager* HWindowsManager::m_instance = nullptr;