#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "HSceneManager.h"
#include "Location.h"
#include "GunModelManager.h"
#include "NormalBombModelManager.h"
#include "SplitBombModelManager.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    LOG_FUNCTION_LIFE
}

AppDelegate::~AppDelegate()
{
    LOG_FUNCTION_LIFE
    Location::purge();
    GunModelManager::purge();
    NormalBombModelManager::purge();
    SplitBombModelManager::purge();
}

bool AppDelegate::applicationDidFinishLaunching()
{
    LOG_FUNCTION_LIFE
//    log("__TIME__ %s",__TIME__);
//    log("__TIMESTAMP__ %s",__TIMESTAMP__);
//    log("__FILE__ %s",__FILE__);
//    log("__DATE__ %s",__DATE__);
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    ScreenFit::Fit(960, 640);
    
    
    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    Location::S();
    GunModelManager::getInstance();
    NormalBombModelManager::getInstance();
    SplitBombModelManager::getInstance();

//    // create a scene. it's an autorelease object
//    auto scene = HelloWorld::createScene();
//
//    t_startRandom();
//    
//    // run
//    director->runWithScene(scene);

    HSceneManager::S()->changeScene(M_SCENE_MENU, nullptr);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    LOG_FUNCTION_LIFE
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    LOG_FUNCTION_LIFE
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
