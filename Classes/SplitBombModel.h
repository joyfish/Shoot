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
    string file_name;//�����ļ���
    string anim_name;//������
    int count;//��������
    float b_speed;//�ӵ��ٶ�
    float range;//���
    int is_cross;//�Ƿ�͸ 0 ����͸
    
    SplitBombModel(){autorelease();}
};


#endif
