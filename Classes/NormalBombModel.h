//
//  NormalBombModel.h
//  Shooting
//
//  Created by wilford on 14-8-28.
//
//

#ifndef Shooting_NormalBombModel_h
#define Shooting_NormalBombModel_h

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

class NormalBombModel: public Ref{
public:
    int id;
    string file_name;//动画文件名
    string anim_name;//动画名
    float duration;//持续时间
    
    NormalBombModel(){autorelease();}
};

#endif
