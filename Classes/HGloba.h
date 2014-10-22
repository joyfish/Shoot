//
//  HGloba.h
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#ifndef __Shooting__HGloba__
#define __Shooting__HGloba__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "DataBase64.h"


USING_NS_CC;
using namespace std;
using namespace CocosDenshion;

//Defines
#define PopBtn(__Btn__)\
__Btn__->runAction(Sequence::create(ScaleTo::create(0.1f, 1.2f), ScaleTo::create(0.15f, 0.9f) ,ScaleTo::create(0.05f, 1.0f),NULL));

#define EVENT_COIN_UPDATE "coin_update_event"
#define EVENT_MONEY_UPDATE "money_update_event"

#define COIN_OFFSET 1000
#define MONEY_OFFSET 10000

#define INITCOIN 10000
#define INITMONEY 10

//Params
class WindowBattleParam{
public:
    int battle_id;//0-战役 1-佣兵
    WindowBattleParam(int battle_id){
        this->battle_id = battle_id;
    }
};



//Globa
class G{
public:
    static std::string getStringForKey(const char* pKey);
    static void setStringForKey(const char* pKey,const char* value);
    static int getIntForKey(const char* pKey,int d);
    static void setIntForKey(const char* pKey,int value);
    static bool getBoolForKey(const char* pKey,bool b);
    static void setBoolForKey(const char* pKey,bool value);
    
    /////////////////////////////声音
    
    static bool isBackGroundMusicOn();
    
    static void setBackGroundMusicState(bool isOn,const char* backgroundmusic = nullptr);
    
    static bool isEffectOn();
    
    static void setEffectState(bool isOn);
    
    static vector<const char*> g_m_played_effects;
    
    static void playEffect(const char* path,bool loop = false);
    
    static void playBackGroundMusic(const char* path);

    /////////货币
    
    static void setCoin(int coin);
    
    static int getCoin();
    
    static void AddCoin(int coinAdd);
    
    static bool CostCoin(int coinCost);
    
    static void setMoney(int money);
    
    static int getMoney();
    
    static void AddMoney(int moneyAdd);
    
    static bool CostMoney(int moneyCost);
    
    static Scene* g_currentScene;
};

#endif /* defined(__Shooting__HGloba__) */
