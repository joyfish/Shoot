//
//  ScreenFit.h
//  Shooting
//
//  Created by wilford on 14-7-16.
//
//

#ifndef Shooting_ScreenFit_h
#define Shooting_ScreenFit_h

#include "cocos2d.h"

using namespace cocos2d;

const float DesignW = 960;
const float DesignH = 640;

#define _pLeft Director::getInstance()->getVisibleOrigin().x
#define _pRight (Director::getInstance()->getVisibleOrigin().x+Director::getInstance()->getVisibleSize().width)
#define _pTop (Director::getInstance()->getVisibleOrigin().y + Director::getInstance()->getVisibleSize().height)
#define _pBottom Director::getInstance()->getVisibleOrigin().y
#define _pCenterX _pRight/2
#define _pCenterY _pTop/2

#define _nCenter      Point(.5f,.5)
#define _nTop	      Point(.5f,1)
#define _nRight       Point(1,0.5f)
#define _nBottom      Point(.5f,0)
#define _nLeft        Point(0,.5f)
#define _nTopLeft     Point(0,1)
#define _nTopRight    Point(1,1)
#define _nBottomLeft  Point(0,0)
#define _nBottomRight Point(1,0)

#define _screenScale Director::getInstance()->getContentScaleFactor()

#define _pScreenSize Director::getInstance()->getVisibleSize()

class ScreenFit
{
public:
    static void Fit(float ResourceW,float ResourceH){
        auto director = Director::getInstance();
        auto glview = director->getOpenGLView();
        float ScreenW = director->getWinSize().width;
        float ScreenH = director->getWinSize().height;
        
        director->setContentScaleFactor(ResourceH/DesignH);
        if ((DesignH/DesignW)>ScreenH/ScreenW) {
            glview->setDesignResolutionSize(DesignW, DesignH, ResolutionPolicy::FIXED_HEIGHT);
        }else{
            glview->setDesignResolutionSize(DesignW, DesignH, ResolutionPolicy::FIXED_WIDTH);
        }
        
    }
};

#endif
