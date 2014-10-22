//
//  GameScene.h
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#ifndef __Shooting__GameScene__
#define __Shooting__GameScene__

#include "HScene.h"
#include "GameLayerTest.h"

using namespace ui;

class GameScene : public HScene{
public:
    static GameScene* createWithPhysics();
    
    virtual void onEnter() override;
    
    virtual void onExit() override;
    
    virtual void loadResource() override;
};


#endif /* defined(__Shooting__GameScene__) */
