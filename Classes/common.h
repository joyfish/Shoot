//
//  common.h
//  Shooting
//
//  Created by wilford on 14-8-5.
//
//

#ifndef Shooting_common_h
#define Shooting_common_h

#include "cocos2d.h"

using namespace std;

#define SYNTHESIZE(varType, varName, funName)\
protected: varType varName;\
public: virtual varType get##funName(void) const { return varName; }\
public: virtual void set##funName(varType var){ varName = var; }

static void t_startRandom(){
    srand((unsigned)time(NULL));
}

static int t_getRandom(int max){
    int result = floor(CCRANDOM_0_1()*max);
    if(result >= max)
        result = 0;
    return result;
}

inline string getFileNameByPath(const char* full_name)
{
	string file_name = full_name;
	const char*  mn_first = full_name;
	const char*  mn_last  = full_name + strlen( full_name );
	if ( strrchr( full_name, '\\' ) != NULL )
		mn_first = strrchr( full_name, '\\' ) + 1;
	else if ( strrchr( full_name, '/' ) != NULL )
		mn_first = strrchr( full_name, '/' ) + 1;
	if ( strrchr( full_name, '.' ) != NULL )
		mn_last = strrchr( full_name, '.' );
	if ( mn_last < mn_first )
		mn_last = full_name + strlen( full_name );
	
	file_name.assign( mn_first, mn_last );
    
	return file_name;
}

inline void PositionNodeWithPhysicsChildren(Node* node,cocos2d::Point pos){
    node->setPosition(pos);
    //int count = 0;
    function<void(Node*)> f = [&](Node* node){
        auto children =  node->getChildren();
        for(auto child : children){
            if(child->getPhysicsBody()){
                //log("tag %d",child->getTag());
                //count++;
                cocos2d::Point p = child->getPosition();
                child->setPosition(p+cocos2d::Point(1,1));
                child->setPosition(p);
            }
            f(child);
        }
    };
    f(node);
    //log("count %d",count);
}

#endif
