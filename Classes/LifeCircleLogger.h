//
//  LifeCircleLogger.h
//  Shooting
//
//  Created by wilford on 14-7-15.
//
//

#ifndef Shooting_LifeCircleLogger_h
#define Shooting_LifeCircleLogger_h

#include "cocos2d.h"

USING_NS_CC;

class LifeCircleLogger{
    std::string m_msg;
public:
    LifeCircleLogger(){}
    LifeCircleLogger(const std::string& msg)
    :m_msg(msg)
    {
        log("%s BEGINS!",m_msg.c_str());
    }
    ~LifeCircleLogger()
    {
        log("%s ENDS!",m_msg.c_str());
    }
};
#define LOG_FUNCTION_LIFE LifeCircleLogger(__FUNCTION__);

#endif
