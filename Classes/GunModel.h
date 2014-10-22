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
    string name;//����
    int type;//����
    HAND_TYPE handtype;//�ֳ�����
    int atk;//����
    float duration;//�������
    int b_count;//�ص�
    float reload_time;//����ʱ��
    float b_speed;//�ӵ��ٶ�
    float speed;//�����ƶ��ٶ�
    float precision;//����
    float p_speed;//���ƫ��ʱ��
    float p_back_speed;//�ָ�ʱ��
    float range;//���
    int shoot_bullets;//������
    int init_clips;//��ʼ����
    int price;//�۸�
    int unlock;//��������
    int bullet_way;//�ӵ��켣 0 ֱ�� 1 ����
    int bullet_is_cross;//�Ƿ�͸ 0 ����͸ 1 ��͸
    int bullet_outrange;//�ӵ������޾���Ч�� 0 ������ʧ 1...
    int bullet_outrange_2;//�ӵ������޾���Ч��������ϸ
    int bullet_collision;//�ӵ���ײ���Ч�� 0 ������ʧ 1...
    int bullet_collision_2;//�ӵ���ײ���Ч��������ϸ
    string b_file_name;//�ӵ������ļ���
    string b_anim_name;//�ӵ�������
    float gun_effect0_offset;//ǹ����Чλ��
    float gun_effect1_offset;//�ӵ�������Чλ��
    string g_ef0_file_name;//ǹ����Ч�����ļ���
    string g_ef0_anim_name;//ǹ����Ч������
    string g_ef1_file_name;//ǹ�ڵ��������ļ���
    string g_ef1_anim_name;//ǹ�ڵ���������
    string des;//����
    
    GunModel(){autorelease();}
};

#endif /* defined(__Shooting__GunModel__) */
