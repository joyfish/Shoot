//
//  NormalBombModelManager.h
//  Shooting
//
//  Created by wilford on 14-8-28.
//
//

#ifndef __Shooting__NormalBombModelManager__
#define __Shooting__NormalBombModelManager__

#include "ModelManagerTemplate.h"
#include "NormalBombModel.h"
#include "json/document.h"
#include "cocostudio/DictionaryHelper.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace std;
using namespace rapidjson;

class NormalBombModelManager : public ModelManagerTemplate<NormalBombModelManager, NormalBombModel>{
    
    static string ID;
    static string FILE_NAME;
    static string ANIM_NAME;
    static string DURATION;
    
    friend ModelManagerTemplate<NormalBombModelManager, NormalBombModel>;
    
public:
    NormalBombModel* getModelByID(int id) {
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
    NormalBombModelManager();
    
};


#endif /* defined(__Shooting__NormalBombModelManager__) */
