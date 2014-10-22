//
//  HWindowsManager.h
//  Shooting
//
//  Created by wilford on 14-10-14.
//
//

#ifndef __Shooting__HWindowsManager__
#define __Shooting__HWindowsManager__

#define __Bomb__HWindowsManager__

#include "IHWindow.h"
#include "cocos2d.h"

USING_NS_CC;

//
//Manage all the window show by HBaseWindows
//
class HWindowsManager{
public:
    static HWindowsManager* S();
    
    void pushWindow(IHWindow* window);
    
    void popWindow();
    
    void closeWindow(IHWindow* window);
    
    void closeAllWindows();
    
    bool hasWindowsShowed(){return m_windows.size()>0;}
    
    void update(float dt);
    
    void clearToClose();
    
    void updateWindows(float dt);
    
    void purge(){
        
        CC_SAFE_DELETE(m_instance);
    }
    
    int getTopZOrder();
    
protected:
    //
    //constructor
    //
    HWindowsManager();
    
    //
    //destructor
    //
    ~HWindowsManager();
    
private:
    Vector<IHWindow*> m_windows;//开启的HWindow
    Vector<IHWindow*> m_toclose;//待关闭的HWindow
    static HWindowsManager* m_instance;
};



#endif /* defined(__Shooting__HWindowsManager__) */
