//
//  HScene.h
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#ifndef __Shooting__HScene__
#define __Shooting__HScene__


#include "cocos2d.h"
#include "cocostudio/Cocostudio.h"
#include "ui/CocosGUI.h"
#include "HGloba.h"
#include "ScreenFit.h"
#include "HWindowsManager.h"
#include "HWindowsHelper.h"


USING_NS_CC;
using namespace std;
using namespace cocostudio;

enum M_SCENE{
    M_SCENE_MENU,
    M_SCENE_MAIN,
    M_SCENE_GAME
};

class HScene : public cocos2d::Scene{
public:
    HScene()
    :m_data(nullptr)
    ,m_helper(nullptr)
    {}
    
    virtual void onEnter() override;
    
    virtual void onExit() override;
    
    virtual void update(float dt) override;
    
    vector<std::string> getTextureNames();
    
    //预加载的资源 重写他来添加资源
    virtual void loadResource();
    //Scene销毁时候调用释放资源
    virtual void ReleaseResource();
    
    void changeScene(M_SCENE m_scene,void* data = nullptr);
    
    void setData(void* data);
    
    void setTouchEnable(bool enabled);
    
    function<void(M_SCENE,void* data)> onChangeScene;
protected:
    void addTextureName(std::string fileName);
    void releaseTexture(const char* fileName);
    //记录开启Scene 传递过来的参数
    void* m_data;
    
    Node* scene_bg;//界面的窗口添加到这层 window直接添加到HScene;
    HWindowsHelper* m_helper;
    
private:
    
    vector<std::string> resourceList;
    
};

class LoadingScene : public cocos2d::Scene{
public:
    virtual void onEnter();
    virtual void onExit();
    CREATE_FUNC(LoadingScene);
    
    void drawUI();
    
    virtual void update(float dt){
        Scene::update(dt);
    }
    
    static void Load(HScene* scene);
    
    void setImagesToLoad(vector<std::string> images_toload);
    
    void setNextScene(Scene* nextScene){
        this->nextScene = nextScene;
        this->nextScene->retain();
    }
    
private:
    void loadNext(Texture2D* texture);
    
    Scene* nextScene;//loading完成开启的Scene
    vector<std::string> images_toload;//储存需要预加载的图片名
    int loaded;//加载完的图片数量
    long total;//图片总数量
};


#endif /* defined(__Shooting__HScene__) */
