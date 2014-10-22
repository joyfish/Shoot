//
//  mAStar.h
//  Shooting
//
//  Created by wilford on 14-9-5.
//
//

#ifndef __Shooting__mAStar__
#define __Shooting__mAStar__

#include "Cell.h"
#include <deque>
#include "Array2D.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

typedef enum{
	kDistanceBase,
	kSimpleHeuristic,
	kComplexHeuristic,
	kAStar
}PathFindingType;

const PathFindingType mPathFindingType = kAStar;

typedef bool (*compareTwoCells)(Cell *c1, Cell *c2);

class mAStarPoint{
public:
    float x;
    float y;
    mAStarPoint(float x,float y){
        this->x = x;
        this->y = y;
    }
};

class mAStar{
public:
    mAStar():_m_Map(0,0){}
    
    
    mAStar(Array2D<Cell> map,float eachBoxWidth,float eachBoxHeight);
    void updateMap(Array2D<Cell> map);
    deque<mAStarPoint> getPath(float playerX,float playerY,float goalX,float goalY);
    
    int PointAtLineLeftRight(Point lineStart, Point lineEnd, Point point);
    bool IsTwoLineIntersect(Point line1Start, Point line1End, Point line2Start, Point line2End);
    bool IsLineIntersectRect(Point lineStart, Point lineEnd, Rect rect);

    bool hasUnPassableCellBetween(float playerX,float playerY,float goalX,float goalY);
    
    
private:
    Array2D<Cell> _m_Map;
    int _playerX;
    int _playerY;
    int _goalX;
    int _goalY;
    float _eachBoxWidth;
    float _eachBoxHeight;
    
	void clearCells();
	void startPathFinding(compareTwoCells compareMethod, int startX,int startY,int goalX,int goalY);
	//void fullFillPathData();
	void fullFillPlayerAndGoalData(float playerX,float playerY,float goalX,float goalY);
    
};

#endif /* defined(__Shooting__mAStar__) */
