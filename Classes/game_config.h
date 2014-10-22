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


const float bullet_unit_speed = 1.0f;//子弹 速度单位

//contact masks

#define HERO_CONTACT_MASK           0x000f0f0f //英雄
#define MONSTER_CONTACT_MASK        0x000000ff //怪物
#define HERO_BULLET_CONTACT_MASK    0x0000f0f0 //英雄子弹
#define MONSTER_BULLET_CONTACT_MASK 0x0000ff00 //怪物子弹
#define WALL_CONTACT_MASK           0x0000f000 //障碍物
#define ITEM_CONTACT_MASK           0x000f0000 //道具


//collision masks

#define HERO_COLLISION_MASK           0x0000000f //英雄
#define MONSTER_COLLISION_MASK        0x000000f0 //怪物
#define HERO_BULLET_COLLISION_MASK    0x00000000 //英雄子弹
#define MONSTER_BULLET_COLLISION_MASK 0x00000000 //怪物子弹
#define WALL_COLLISION_MASK           0x000000ff //障碍物
#define ITEM_COLLISION_MASK           0x00000000 //道具

#endif
