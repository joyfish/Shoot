//
//  HSceneManager.cpp
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#include "HSceneManager.h"
#include "MenuScene.h"
#include "MainScene.h"
#include "GameScene.h"

HSceneManager* HSceneManager::instance = nullptr;

void HSceneManager::changeScene(M_SCENE m_scene,void* data){
    HScene* scene = nullptr;
    
    switch (m_scene) {
        case M_SCENE_MENU:
            scene = MenuScene::create();
            break;
        case M_SCENE_MAIN:
            scene = MainScene::create();
            break;
        case M_SCENE_GAME:
            scene = GameScene::createWithPhysics();
        default:
            break;
    }
    if (scene) {
        scene->onChangeScene = CC_CALLBACK_2(HSceneManager::changeScene, this);
        scene->setData(data);
        LoadingScene::Load(scene);
    }
    HWindowsManager::S()->closeAllWindows();
}