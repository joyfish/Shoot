//
//  game_config.h
//  Shooting
//
//  Created by wilford on 14-7-29.
//
//

#ifndef Shooting_game_config_h
#define Shooting_game_config_h

enum ElementType{
    HERO = 0,
    MONSTER = 1,
    BULLET = 3,
    BOMB = 4,
    WALL = 5,
};


const float bullet_unit_speed = 1.0f;//�ӵ� �ٶȵ�λ

//contact masks

#define HERO_CONTACT_MASK           0x000f0f0f //Ӣ��
#define MONSTER_CONTACT_MASK        0x000000ff //����
#define HERO_BULLET_CONTACT_MASK    0x0000f0f0 //Ӣ���ӵ�
#define MONSTER_BULLET_CONTACT_MASK 0x0000ff00 //�����ӵ�
#define WALL_CONTACT_MASK           0x0000f000 //�ϰ���
#define ITEM_CONTACT_MASK           0x000f0000 //����


//collision masks

#define HERO_COLLISION_MASK           0x0000000f //Ӣ��
#define MONSTER_COLLISION_MASK        0x000000f0 //����
#define HERO_BULLET_COLLISION_MASK    0x00000000 //Ӣ���ӵ�
#define MONSTER_BULLET_COLLISION_MASK 0x00000000 //�����ӵ�
#define WALL_COLLISION_MASK           0x000000ff //�ϰ���
#define ITEM_COLLISION_MASK           0x00000000 //����

#endif
