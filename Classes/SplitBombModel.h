//
//  SplitBombModel.h
//  Shooting
//
//  Created by wilford on 14-8-28.
//
//

#ifndef Shooting_SplitBombModel_h
#define Shooting_SplitBombModel_h

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;


class SplitBombModel: public Ref{
public:
    int id;
    string file_name;//动画文件名
    string anim_name;//动画名
    int count;//分裂数量
    float b_speed;//子弹速度
    float range;//射程
    int is_cross;//是否穿透 0 不穿透
    
    SplitBombModel(){autorelease();}
};


#endif
