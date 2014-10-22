//
//  PoolTemplate.h
//  Shooting
//
//  Created by wilford on 14-8-6.
//
//

#ifndef Shooting_PoolTemplate_h
#define Shooting_PoolTemplate_h

#include "cocos2d.h"

using namespace cocos2d;
using namespace std;

template<class T,class O>
class PoolTemplate{
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
    
    void add(O* node){
        CCASSERT(node, "node can not be null");
        if (!_nodes.contains(node)) {
            _nodes.pushBack(node);
        }
       // log("%s size %ld",_className.c_str(), _nodes.size());
    }
    
    O* get(string anim_file){
        for (auto node: _nodes) {
            if (isMatch(node,anim_file)) {
                return node;
            }
        }
        return nullptr;
    }
    
    
protected:
    virtual bool isMatch(O* node, string anim_file) = 0;
    
    PoolTemplate(){
        _className = "PoolTemplate";
        _nodes.clear();
    }
    ~PoolTemplate(){
        _nodes.clear();
    }
    
    Vector<O*> _nodes;
    string _className;
    static T* instance;
    
};

template<class T,class O>
T* PoolTemplate<T,O>::instance = nullptr;

#endif
