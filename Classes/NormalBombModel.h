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
    string file_name;//�����ļ���
    string anim_name;//������
    float duration;//����ʱ��
    
    NormalBombModel(){autorelease();}
};

#endif
