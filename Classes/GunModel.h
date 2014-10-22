//
//  GunModel.h
//  Shooting
//
//  Created by wilford on 14-8-4.
//
//

#ifndef __Shooting__GunModel__
#define __Shooting__GunModel__

#include "cocos2d.h"


//using namespace rapidjson;
using namespace cocos2d;
using namespace std;

enum HAND_TYPE{
    HAND_TYPE_HANDGUN = 0,
    HAND_TYPE_GUN = 1,
    HAND_TYPE_KNIFE = 2
};

#define BULLET_FILE_PATH "bullet/"
#define BULLET_FILE_NAME "bullet_"
#define BULLET_ANIM "b_anim_"
#define FIRE_EFFECT_FILE_PATH "fire_effect/fire_effect_"
#define FIRE_EFFECT_FILE_NAME "fire_effect_"
#define FIRE_EFFECT_ANIM "fire_effect_"
#define CARTRIDGE_FILE_NAME "cartridge_"
#define CARTRIDGE_FILE_PATH "cartridge/cartridge_"
#define CARTRIDGE_ANIM "anim_"

class GunModel: public Ref{
public:
    int id;
    string name;//名字
    int type;//类型
    HAND_TYPE handtype;//手持类型
    int atk;//攻击
    float duration;//攻击间隔
    int b_count;//载弹
    float reload_time;//换镗时间
    float b_speed;//子弹速度
    float speed;//拿抢移动速度
    float precision;//精度
    float p_speed;//最大偏离时间
    float p_back_speed;//恢复时间
    float range;//射程
    int shoot_bullets;//出镗量
    int init_clips;//初始弹夹
    int price;//价格
    int unlock;//解锁条件
    int bullet_way;//子弹轨迹 0 直线 1 跟踪
    int bullet_is_cross;//是否穿透 0 不穿透 1 穿透
    int bullet_outrange;//子弹到极限距离效果 0 渐变消失 1...
    int bullet_outrange_2;//子弹到极限距离效果分类详细
    int bullet_collision;//子弹碰撞后的效果 0 渐变消失 1...
    int bullet_collision_2;//子弹碰撞后的效果分类详细
    string b_file_name;//子弹动画文件名
    string b_anim_name;//子弹动画名
    float gun_effect0_offset;//枪口特效位置
    float gun_effect1_offset;//子弹掉落特效位置
    string g_ef0_file_name;//枪口特效动画文件名
    string g_ef0_anim_name;//枪口特效动画名
    string g_ef1_file_name;//枪口掉弹动画文件名
    string g_ef1_anim_name;//枪口掉弹动画名
    string des;//描述
    
    GunModel(){autorelease();}
};

#endif /* defined(__Shooting__GunModel__) */
