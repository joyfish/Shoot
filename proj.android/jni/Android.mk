LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
../../Classes/ArmatureBase.cpp \
../../Classes/ArmatureFactory.cpp \
../../Classes/Bullet.cpp \
../../Classes/BulletFactory.cpp \
../../Classes/CcJoystick.cpp \
../../Classes/CocAnimationTest.cpp \
../../Classes/DataBase64.cpp \
../../Classes/DropDownList.cpp \
../../Classes/ElementsContact.cpp \
../../Classes/GameLayerTest.cpp \
../../Classes/GameScene.cpp \
../../Classes/Gun.cpp \
../../Classes/GunModelManager.cpp \
../../Classes/HGloba.cpp \
../../Classes/HScene.cpp \
../../Classes/HSceneManager.cpp \
../../Classes/HScrollViewBar.cpp \
../../Classes/HWindow.cpp \
../../Classes/HWindowsHelper.cpp \
../../Classes/HWindowsManager.cpp \
../../Classes/HelloWorldScene.cpp \
../../Classes/Hero.cpp \
../../Classes/HeroFactory.cpp \
../../Classes/LineContainer.cpp \
../../Classes/MainScene.cpp \
../../Classes/MenuScene.cpp \
../../Classes/NormalBomb.cpp \
../../Classes/NormalBombFactory.cpp \
../../Classes/NormalBombModelManager.cpp \
../../Classes/SplitBomb.cpp \
../../Classes/SplitBombFactory.cpp \
../../Classes/SplitBombModelManager.cpp \
../../Classes/Window1.cpp \
../../Classes/Window2.cpp \
../../Classes/Window3.cpp \
../../Classes/Window_Ability.cpp \
../../Classes/Window_Battle.cpp \
../../Classes/Window_Setting.cpp \
../../Classes/Window_Shop.cpp \
../../Classes/Window_Task.cpp \
../../Classes/Window_Weapon.cpp \
../../Classes/mAStar.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
 LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
 $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
# $(call import-module,extensions)
