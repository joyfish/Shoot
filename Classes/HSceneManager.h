//
//  HSceneManager.h
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#ifndef __Shooting__HSceneManager__
#define __Shooting__HSceneManager__

#include "cocos2d.h"
#include "HScene.h"

USING_NS_CC;

class HSceneManager{
public:
    static HSceneManager* S(){
        if (instance==NULL) {
            instance = new HSceneManager();
        }
        return instance;
    }
    
    void purge(){
        CC_SAFE_DELETE(instance);
    }
    
    void changeScene(M_SCENE m_scene,void* data);
    
private:
    static HSceneManager* instance;
};

#endif /* defined(__Shooting__HSceneManager__) */
