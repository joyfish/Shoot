//
//  ElementBase.h
//  Shooting
//
//  Created by wilford on 14-7-29.
//
//

#ifndef __Shooting__ElementBase__
#define __Shooting__ElementBase__

#include "cocos2d.h"
#include "game_config.h"

using namespace cocos2d;

class ElementBase:public Node{
public:
    CREATE_FUNC(ElementBase);
    
    const ElementType getElementType()const {return _type;};
    
protected:
    ElementBase():_type(WALL){}
    
    ElementType _type;
};

#endif /* defined(__Shooting__ElementBase__) */
