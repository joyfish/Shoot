//
//  HGloba.cpp
//  Shooting
//
//  Created by wilford on 14-10-13.
//
//

#include "HGloba.h"

std::string G::getStringForKey(const char* pKey)
{
    std::string data = UserDefault::getInstance()->getStringForKey(pKey);
    data = ParseData(data);
    return data;;
}

void G::setStringForKey(const char* pKey,const char* value)
{
    std::string data = value;
    data = SaveData(reinterpret_cast<const unsigned char*>(data.c_str()), data.length());
    UserDefault::getInstance()->setStringForKey(pKey, data);
}


int G::getIntForKey(const char* pKey,int d){
    std::string tmp = getStringForKey(pKey);
    if(tmp.empty()){
        return d;
    }else{
        return atoi(tmp.c_str());
    }
}

void G::setIntForKey(const char* pKey,int value){
    char tmp[20];
    sprintf(tmp,"%d",value);
    setStringForKey(pKey,tmp);
}

bool G::getBoolForKey(const char* pKey,bool b){
    std::string tmp = getStringForKey(pKey);
    if(tmp.empty()){
        return b;
    }else{
        if(tmp == "true"){
            return true;
        }else
            return false;
    }
}

void G::setBoolForKey(const char* pKey,bool value){
    if(value){
        setStringForKey(pKey,"true");
    }else
        setStringForKey(pKey,"false");
}

bool G::isBackGroundMusicOn(){
    return getBoolForKey("isBackGroundMusicOn", true);
}

void G::setBackGroundMusicState(bool isOn,const char* backgroundmusic /*= nullptr*/){
    if (isBackGroundMusicOn() == isOn) {
        return;
    }
    setBoolForKey("isBackGroundMusicOn", isOn);
    UserDefault::getInstance()->flush();
    if (isOn) {
        if(backgroundmusic!=NULL)
            SimpleAudioEngine::getInstance()->playBackgroundMusic(backgroundmusic,true);
    }else{
        SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
    }
}

bool G::isEffectOn(){
    return getBoolForKey("isEffectOn", true);
    UserDefault::getInstance()->flush();
}

void G::setEffectState(bool isOn){
    if (isEffectOn() == isOn) {
        return;
    }
    setBoolForKey("isEffectOn", isOn);
}

void G::playEffect(const char* path,bool loop /* = false*/){
    if(isEffectOn()){
        for (int i=0; i<g_m_played_effects.size(); i++) {
            if (strcmp(path, g_m_played_effects[i])==0) {
                return;
            }
        }
        SimpleAudioEngine::getInstance()->playEffect(path,loop);
        g_m_played_effects.push_back(path);
    }
}

void G::playBackGroundMusic(const char* path){
    if(isBackGroundMusicOn())
        SimpleAudioEngine::getInstance()->playBackgroundMusic(path,true);
}


void G::setCoin(int coin)
{
    if (coin == getCoin()) {
        return;
    }
    setIntForKey("coin", coin+COIN_OFFSET);
    UserDefault::getInstance()->flush();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_COIN_UPDATE);
}

int G::getCoin(){
    return getIntForKey("coin", INITCOIN+COIN_OFFSET)-COIN_OFFSET;
}

bool G::CostCoin(int coinCost){
    if (coinCost>getCoin()) {
        return false;
    }
    setCoin(getCoin()-coinCost);
    return true;
}

void G::AddCoin(int coinAdd){
    setCoin(getCoin()+coinAdd);
}

void G::setMoney(int money)
{
    if (money == getMoney()) {
        return;
    }
    setIntForKey("money", money+MONEY_OFFSET);
    UserDefault::getInstance()->flush();
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EVENT_MONEY_UPDATE);
}

int G::getMoney(){
    return getIntForKey("money", INITMONEY+MONEY_OFFSET)-MONEY_OFFSET;
}

bool G::CostMoney(int moneyCost){
    if (moneyCost>getMoney()) {
        return false;
    }
    setMoney(getMoney()-moneyCost);
    return true;
}

void G::AddMoney(int moneyAdd){
    setMoney(getMoney()+moneyAdd);
}

vector<const char*> G::g_m_played_effects;

Scene* G::g_currentScene = nullptr;
