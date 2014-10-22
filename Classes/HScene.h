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
    
    //Ԥ���ص���Դ ��д���������Դ
    virtual void loadResource();
    //Scene����ʱ������ͷ���Դ
    virtual void ReleaseResource();
    
    void changeScene(M_SCENE m_scene,void* data = nullptr);
    
    void setData(void* data);
    
    void setTouchEnable(bool enabled);
    
    function<void(M_SCENE,void* data)> onChangeScene;
protected:
    void addTextureName(std::string fileName);
    void releaseTexture(const char* fileName);
    //��¼����Scene ���ݹ����Ĳ���
    void* m_data;
    
    Node* scene_bg;//����Ĵ�����ӵ���� windowֱ����ӵ�HScene;
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
    
    Scene* nextScene;//loading��ɿ�����Scene
    vector<std::string> images_toload;//������ҪԤ���ص�ͼƬ��
    int loaded;//�������ͼƬ����
    long total;//ͼƬ������
};


#endif /* defined(__Shooting__HScene__) */
