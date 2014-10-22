#ifndef _LINECONTAINER_H_
#define _LINECONTAINER_H_

#include "cocos2d.h"
#include "Array2D.h"
#include "Cell.h"
#include <vector>
#include <deque>

USING_NS_CC;
using namespace std;

class LineContainer : public Node{
public:
	LineContainer(int xLineCount, int yLineCount,float eachBoxWidth,float eachBoxHeight);
	static LineContainer* create(int xLineCount, int yLineCount,float eachBoxWidth,float eachBoxHeight)
    {
        LineContainer *pRet = new LineContainer(xLineCount ,yLineCount,eachBoxWidth, eachBoxHeight);
        if (pRet && pRet->init())
        {
            pRet->autorelease();
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = NULL;
            return NULL;
        }
    }

    CC_SYNTHESIZE(bool,_startDrawPath,StartDrawPath);

	virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags) override;
	void drawLineMap();
	void drawCells(Array2D<Cell> &m_map);
	void drawPath(deque<Cell*> &depCells);
	void updateMapParameter(Array2D<Cell> &m_map);
	void setPathParameters(deque<Cell*> &depCells);
private:
	Size _totalSize;
	float _eachBoxWidth;
	float _eachBoxHeight;
	Array2D<Cell> _m_map;
	deque<Cell*> _deqPathCells;
	int _goalX;
	int _goalY;
    int _xLineCount;
    int _yLineCount;
};


#endif