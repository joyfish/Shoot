//
//  HScene.cpp
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#include "HScene.h"

using namespace ui;

void HScene::onEnter() {
    Scene::onEnter();
    scheduleUpdate();
    scene_bg = Node::create();
    this->addChild(scene_bg);
    m_helper = new HWindowsHelper(scene_bg);
}

void HScene::onExit(){
    Scene::onExit();
    ReleaseResource();
    CC_SAFE_DELETE(m_helper);
}

void HScene::update(float dt){
    Scene::update(dt);
    HWindowsManager::S()->update(dt);
    G::g_m_played_effects.clear();
}

void HScene::releaseTexture(const char* fileName){
    Director::getInstance()->getTextureCache()->removeTextureForKey(fileName);
}

vector<std::string> HScene::getTextureNames(){
    return resourceList;
}

void HScene::addTextureName(std::string fileName){
    resourceList.push_back(fileName);
}

void HScene::loadResource(){
}
void HScene::ReleaseResource(){
    for (auto image : resourceList ) {
        log("[release image] %s",image.c_str());
        releaseTexture(image.c_str());
    }
    resourceList.clear();
}

void HScene::setTouchEnable(bool enabled){
    if (m_helper) {
        m_helper->setTouchEnable(enabled);
    }
}


void HScene::changeScene(M_SCENE m_scene,void* data /*= nullptr*/){
    onChangeScene(m_scene,data);
}

void HScene::setData(void* data){
    m_data = data;
}


void LoadingScene::onEnter(){
    log("Loading onEnter");
    Scene::onEnter();
    unscheduleAllSelectors();
    
    drawUI();
    
    CCLOG("start Loading");
    
    loadNext(nullptr);
}

void LoadingScene::onExit(){
    log("Loading onExit");
    Scene::onExit();
    images_toload.clear();
}

void LoadingScene::drawUI(){
    //绘制加载界面
    Widget* loading_bg =  GUIReader::getInstance()->widgetFromJsonFile("ccs/Loading.json");
    if (loading_bg) {
        this->addChild(loading_bg);
        for (int i=0; i<3; i++) {
            std::string circle_name = "circle_"+to_string(i);
            Node* circle = ui::Helper::seekWidgetByName(loading_bg, circle_name.c_str());
            if (i%2==1) {
                circle->runAction(RepeatForever::create(RotateBy::create(1.0f, 60)));
            }else{
                circle->runAction(RepeatForever::create(RotateBy::create(1.0f, -60)));
            }
        }
    }
}

void LoadingScene::Load(HScene *scene){
    Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
    
    LoadingScene* loading = LoadingScene::create();
    Director* director = Director::getInstance();
    scene->loadResource();
    loading->setImagesToLoad(scene->getTextureNames());
    loading->setNextScene(scene);
    
    if(G::g_currentScene==nullptr){
        director->runWithScene(loading);
    }else{
        director->replaceScene(loading);
    }
}

void LoadingScene::setImagesToLoad(vector<std::string> images_toload){
    this->images_toload = images_toload;
    loaded = 0;
    total = images_toload.size();
}



void LoadingScene::loadNext(Texture2D* texture){
    if (loaded>=total) {
        Director::getInstance()->replaceScene(nextScene);
        G::g_currentScene = nextScene;
        nextScene->release();
        return;
    }
    
    std::string imageName = images_toload[loaded++];
    Director::getInstance()->getTextureCache()->addImageAsync(imageName, CC_CALLBACK_1(LoadingScene::loadNext, this));
    CCLOG("[loading image] %s",imageName.c_str());
}