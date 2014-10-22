//
//  ModelManagerTemplate.h
//  Shooting
//
//  Created by wilford on 14-8-5.
//
//

#ifndef __Shooting__ModelManagerTemplate__
#define __Shooting__ModelManagerTemplate__

#include "cocos2d.h"


using namespace cocos2d;

template <class T,class M>
class ModelManagerTemplate {
public:
    static T* getInstance(){
        if (instance == nullptr) {
            instance = new T();
        }
        return instance;
    }
    
    static void purge(){
        CC_SAFE_DELETE(instance);
    }
    
    M* getModel(int idx){
//        for(auto model : _models){
//            if (isMatch(model,idx)) {
//                return model;
//            }
//        }
        if (idx<_models.size()) {
            return _models.at(idx);
        }
        return nullptr;
    }
    
    const Vector<M*> getModels()const{
        return _models;
    }
    
protected:
    ModelManagerTemplate(){
        //log("modelManager constructor");
        _models.clear();
    }
    
    ~ModelManagerTemplate(){
       // log("modelManager destructor");
        _models.clear();
    }
    
//    virtual bool isMatch(M* model,int idx){
//        return false;
//    }

    
    Vector<M*> _models;
    static T* instance;
};

template <class T,class M>
T* ModelManagerTemplate<T,M>::instance = nullptr;

#endif /* defined(__Shooting__ModelManagerTemplate__) */
