//
//  GunModelManager.h
//  Shooting
//
//  Created by wilford on 14-8-4.
//
//

#ifndef __Shooting__GunModelManager__
#define __Shooting__GunModelManager__

#include "ModelManagerTemplate.h"
#include "GunModel.h"
#include "json/document.h"
#include "cocostudio/DictionaryHelper.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;
using namespace rapidjson;

class GunModelManager : public ModelManagerTemplate<GunModelManager, GunModel>{
    
    static string ID;
    static string NAME;
    static string TYPE;
    static string HANDTYPE;
    static string ATK;
    static string DURATION;
    static string B_COUNT;
    static string RELOAD_TIME;
    static string B_SPEED;
    static string SPEED;
    static string PRECISION;
    static string P_SPEED;
    static string P_BACK_SPEED;
    static string RANGE;
    static string SHOOT_BULLETS;
    static string INIT_CLIPS;
    static string PRICE;
    static string UNLOCK;
    static string DES;
    static string BULLET_WAY;
    static string BULLET_IS_CROSS;
    static string BULLET_OUTRANGE;
    static string BULLET_OUTRANGE_2;
    static string BULLET_COLLISION;
    static string BULLET_COLLISION_2;
    static string B_FILE_ID;
    static string B_ANIM_ID;
    static string GUN_EFFECT0_OFFSET;
    static string GUN_EFFECT1_OFFSET;
    static string G_EF0_FILE_ID;//枪口特效动画文件
    static string G_EF0_ANIM_ID;//枪口特效动画id
    static string G_EF1_FILE_ID;//枪口掉弹动画文件
    static string G_EF1_ANIM_ID;//枪口掉弹动画id
    
    friend ModelManagerTemplate<GunModelManager, GunModel>;
    
public:
    GunModel* getModelByID(int id) {
        for (auto m : _models) {
            if (m->id == id) {
                return m;
            }
        }
        return nullptr;
    }
    
    int getIdxByID(int id){
        int idx =0;
        for (auto m: _models) {
            if (m->id == id) {
                return idx;
            }
            idx++;
        }
        return -1;
    }
    
private:
    GunModelManager();
    
//    virtual bool isMatch(GunModel* model,int idx) override{
//        if (model->id == idx) {
//            return true;
//        }
//        return false;
//    }
};

#endif /* defined(__Shooting__GunModelManager__) */
