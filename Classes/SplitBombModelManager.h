//
//  SplitBombModelManager.h
//  Shooting
//
//  Created by wilford on 14-8-28.
//
//

#ifndef __Shooting__SplitBombModelManager__
#define __Shooting__SplitBombModelManager__

#include "ModelManagerTemplate.h"
#include "SplitBombModel.h"
#include "json/document.h"
#include "cocostudio/DictionaryHelper.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;
using namespace rapidjson;


class SplitBombModelManager : public ModelManagerTemplate<SplitBombModelManager, SplitBombModel>{
    
    static string ID;
    static string FILE_NAME;
    static string ANIM_NAME;
    static string COUNT;
    static string B_SPEED;
    static string RANGE;
    static string IS_CROSS;
    
    friend ModelManagerTemplate<SplitBombModelManager, SplitBombModel>;
    
public:
    SplitBombModel* getModelByID(int id){
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
    SplitBombModelManager();
    
};

#endif /* defined(__Shooting__SplitBombModelManager__) */
