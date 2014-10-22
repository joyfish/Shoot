//
//  mAStar.cpp
//  Shooting
//
//  Created by wilford on 14-9-5.
//
//

#include "mAStar.h"
#include "Constants.h"

int g_goalX;
int g_goalY;

bool compareTwoCellsByDistance(Cell *c1, Cell *c2){
	if(c1->getDistance() <= c2->getDistance()){
		return false;
	}else{
		return true;
	}
}

bool comparebyWhichNearerGoalSimpleWay(Cell *c1, Cell *c2){
	int distanceOfC1AndGoal = abs(g_goalX - c1->getX()) + abs(g_goalY - c1->getY());
	int distanceOfC2AndGoal = abs(g_goalX - c2->getX()) + abs(g_goalY - c2->getY());
	if(distanceOfC1AndGoal <= distanceOfC2AndGoal){
		return false;
	}else{
		return true;
	}
}

float distanceBetweenTwoCells(float c1X,float c1Y, float c2X, float c2Y){
    
	return sqrt(pow(c2X - c1X,2) + pow(c2Y - c1Y,2));
}

bool comparebyWhichNearerGoalPhysicWay(Cell *c1, Cell *c2){
	float distanceOfC1AndGoal = distanceBetweenTwoCells((float)c1->getX(),(float)c1->getY(),(float)g_goalX,(float) g_goalY);
    
	float distanceOfC2AndGoal = distanceBetweenTwoCells((float)c2->getX(),(float)c2->getY(),(float)g_goalX,(float) g_goalY);
	if(distanceOfC1AndGoal <= distanceOfC2AndGoal){
		return false;
	}else{
		return true;
	}
}

bool comparebyDistanceBetweenStartAndGoal(Cell *c1, Cell *c2){
	float distanceOfC1AndGoal = c1->getDistance() +
    distanceBetweenTwoCells((float)c1->getX(),(float)c1->getY(),(float)g_goalX,(float) g_goalY);
    
	float distanceOfC2AndGoal = c2->getDistance() +
    distanceBetweenTwoCells((float)c2->getX(),(float)c2->getY(),(float)g_goalX,(float) g_goalY);
	if(distanceOfC1AndGoal <= distanceOfC2AndGoal){
		return false;
	}else{
		return true;
	}
}

//void mAStar::fullFillPathData()
//{
//	_vecPathCell.clear();
//	Cell* cell = _m_Map.Get(_goalX,_goalY);
//	while(cell->getLastX() != -1){
//		_vecPathCell.push_front(cell);
//		cell = _m_Map.Get(cell->getLastX(),cell->getLastY());
//	}
//	_vecPathCell.push_front(_m_Map.Get(_playerX, _playerY));
//}

void mAStar::fullFillPlayerAndGoalData(float playerX,float playerY,float goalX,float goalY){
    
	_playerX = playerX  / _eachBoxWidth;
	_playerY = playerY / _eachBoxHeight;
    
	_goalX =  goalX / _eachBoxWidth;
	_goalY =  goalY / _eachBoxHeight;
    
	g_goalX = _goalX;
	g_goalY = _goalY;
}

mAStar::mAStar(Array2D<Cell> map,float eachBoxWidth,float eachBoxHeight)
:_m_Map(map),_eachBoxWidth(eachBoxWidth),_eachBoxHeight(eachBoxHeight)
{
}

void mAStar::updateMap(Array2D<Cell> map){
    _m_Map = map;
}

deque<mAStarPoint> mAStar::getPath(float playerX, float playerY, float goalX, float goalY){
    deque<mAStarPoint> vecPathPoint;
    fullFillPlayerAndGoalData(playerX,playerY,goalX, goalY);
    if(_playerX >= 0 && _playerX < _m_Map.Width() && _playerY >=0 && _playerY <= _m_Map.Height()
       && _goalX >= 0 && _goalX < _m_Map.Width() && _goalY >=0 && _goalY <= _m_Map.Height()){
        clearCells();
        switch (mPathFindingType){
            case kDistanceBase:
                startPathFinding(compareTwoCellsByDistance,_playerX,_playerY,_goalX,_goalY);
                break;
            case kSimpleHeuristic:
                startPathFinding(comparebyWhichNearerGoalSimpleWay,_playerX,_playerY,_goalX,_goalY);
                break;
            case kComplexHeuristic:
                startPathFinding(comparebyWhichNearerGoalPhysicWay,_playerX,_playerY,_goalX,_goalY);
                break;
            case kAStar:
                startPathFinding(comparebyDistanceBetweenStartAndGoal,_playerX,_playerY,_goalX,_goalY);
                break;
		};
        
        Cell* cell = _m_Map.Get(_goalX,_goalY);
        while(cell->getLastX() != -1){
            vecPathPoint.push_front(mAStarPoint(cell->getX()*_eachBoxWidth+_eachBoxWidth/2,cell->getY()*_eachBoxHeight+_eachBoxHeight/2));
            cell = _m_Map.Get(cell->getLastX(),cell->getLastY());
        }
        //vecPathPoint.push_front(mAStarPoint(playerX*_eachBoxHeight,playerY));
    }
    return vecPathPoint;
}

void mAStar::clearCells(){
	//init map
	for(int i = 0; i < _m_Map.Width(); ++i){
		for(int j = 0; j < _m_Map.Height(); ++j){
			Cell *cell = _m_Map.Get(i,j);
			cell->setMarked(false);
			cell->setDistance(0);
			cell->setLastX(-1);
			cell->setLastY(-1);
			cell->setDrawProgress(false);
			_m_Map.Set(i,j,cell);
		}
	}
}

void mAStar::startPathFinding(compareTwoCells compareMethod, int startX,int startY,int goalX,int goalY){
	Cell *startCell = _m_Map.Get(startX, startY);
	vector<Cell*> vecCells;
	vecCells.push_back(startCell);
	make_heap(vecCells.begin(),vecCells.end(),compareMethod);
	startCell->setMarked(true);
	Cell *nowProcessCell;
    
    
	while(vecCells.size() != 0){
		pop_heap(vecCells.begin(),vecCells.end(),compareMethod);
		nowProcessCell = vecCells.back();
		vecCells.pop_back();
        
		//_vecCommandCell.push_back(nowProcessCell);//just record the finding progress
        
		if(nowProcessCell->getX() == _goalX && nowProcessCell->getY() == _goalY){//the goal is reach
			return;
		}
        
		for(int i = 0; i < 8; ++i){ //check eight direction
            
			int indexX = nowProcessCell->getX() + DIRECTION[i][0];
			int indexY = nowProcessCell->getY() + DIRECTION[i][1];
            
			if(indexX >= 0 && indexX < _m_Map.Width() && indexY >= 0 && indexY < _m_Map.Height()
               && _m_Map.Get(indexX,indexY)->getPassable() == true){//check is a OK cell or not
                Cell *cell = _m_Map.Get(indexX,indexY);
                float beforeDistance = DISTANCE[i] * cell->getWeight() + _m_Map.Get(nowProcessCell->getX(),
                                                                                    nowProcessCell->getY())->getDistance();//calculate the distance
                if(cell->getMarked() == false){
                    cell->setMarked(true);
                    cell->setLastX(nowProcessCell->getX());
                    cell->setLastY(nowProcessCell->getY());
                    cell->setDistance(beforeDistance);
                    vecCells.push_back(cell);//only push the unmarked cell into the vector
                    push_heap(vecCells.begin(),vecCells.end(),compareMethod);
                }else{// if find a lower distance, update it
                    if(beforeDistance < cell->getDistance()){
                        cell->setDistance(beforeDistance);
                        cell->setLastX(nowProcessCell->getX());
                        cell->setLastY(nowProcessCell->getY());
                        make_heap(vecCells.begin(),vecCells.end(),compareMethod);//distance change,so make heap again
                    }
                }
			}
            
		}
	}
}


int mAStar::PointAtLineLeftRight(Point lineStart, Point lineEnd, Point point){
    lineStart.x -= point.x;
    lineStart.y -= point.y;
    lineEnd.x -= point.x;
    lineEnd.y -= point.y;
    
    int nRet = lineStart.x * lineEnd.y - lineStart.y * lineEnd.x;
    if (nRet == 0)
        return 0;
    else if (nRet > 0)
        return 1;
    else if (nRet < 0)
        return -1;
    
    return 0;
}

bool mAStar::IsTwoLineIntersect(Point line1Start, Point line1End, Point line2Start, Point line2End){
    int nLine1Start = PointAtLineLeftRight(line2Start, line2End, line1Start);
    int nLine1End = PointAtLineLeftRight(line2Start, line2Start, line1End);
    if (nLine1Start * nLine1End > 0)
        return false;
    
    int nLine2Start = PointAtLineLeftRight(line1Start, line1End, line2Start);
    int nLine2End = PointAtLineLeftRight(line1Start, line1End, line2End);
    
    if (nLine2Start * nLine2End > 0)
        return false;
    
    return true;
}

bool mAStar::IsLineIntersectRect(Point lineStart, Point lineEnd, Rect rect){
    // Two point both are in rect
    if (rect.containsPoint(lineStart) && rect.containsPoint(lineEnd))
        return true;
    
    // One point is in rect, another not.
    if (rect.containsPoint(lineStart) && !rect.containsPoint(lineEnd))
        return true;
    if (!rect.containsPoint(lineStart) && rect.containsPoint(lineEnd))
        return true;
    
    // Two point both aren't in rect
    if (IsTwoLineIntersect(lineStart, lineEnd, Point(rect.getMinX(), rect.getMinY()), Point(rect.getMinX(), rect.getMaxX())))
        return true;
    if (IsTwoLineIntersect(lineStart, lineEnd, Point(rect.getMinX(), rect.getMaxY()), Point(rect.getMaxX(), rect.getMaxY())))
        return true;
    if (IsTwoLineIntersect(lineStart, lineEnd, Point(rect.getMaxX(), rect.getMaxY()), Point(rect.getMaxX(),rect.getMinY())))
        return true;
    if (IsTwoLineIntersect(lineStart, lineEnd, Point(rect.getMaxX(), rect.getMinY()), Point(rect.getMinX(), rect.getMinY())))
        return true;
    return false;
}
