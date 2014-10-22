#include "LineContainer.h"
#include "Constants.h"



LineContainer::LineContainer(int xLineCount,int yLineCount,float eachBoxWidth,float eachBoxHeight)
:_xLineCount(xLineCount),_yLineCount(yLineCount),
_m_map(xLineCount,yLineCount)
{
    _totalSize = Size(xLineCount*eachBoxWidth,yLineCount*eachBoxHeight);
    _eachBoxWidth = eachBoxWidth;
    _eachBoxHeight = eachBoxHeight;
}

void LineContainer::draw(Renderer *renderer, const Mat4& transform, uint32_t flags){
	
	//draw white background
    DrawPrimitives::drawSolidRect(Point(0.0,0.0),Point(_totalSize.width,_totalSize.height),Color4F(1.0,1.0,1.0,1.0));

	drawCells(_m_map);

	drawLineMap();

//	if(_startDrawPath){
//		drawPath(_deqPathCells);
//	}
	

}


void LineContainer::updateMapParameter(Array2D<Cell> &m_map){
	_m_map = m_map;
}

void LineContainer::setPathParameters(deque<Cell*> &m_map){
	_deqPathCells = m_map;
	_startDrawPath = true;
}

void LineContainer::drawLineMap(){
	

	//draw black background
	DrawPrimitives::setDrawColor4F(0.0,0.0,0.0,1.0);
	float startPointX = leftMargin;
	float startPointY = bottomMargin;
	float endPointX = _totalSize.width - rightMargin;
	float endPointY = bottomMargin;
	for(int i = 0; i <= _yLineCount; ++i){
		 DrawPrimitives::drawLine(Point(startPointX,startPointY),Point(endPointX,endPointY));//draw horizontal line
		startPointY += _eachBoxHeight;
		endPointY = startPointY;
	}

	startPointX = leftMargin;
	startPointY = bottomMargin;
	endPointX = leftMargin;
	endPointY = _totalSize.height - topMargin;
	for(int i = 0; i <= _xLineCount; ++i){
		DrawPrimitives::drawLine(Point(startPointX,startPointY),Point(endPointX,endPointY));//draw vertical line
		startPointX += _eachBoxWidth;
		endPointX = startPointX;
	}
}

void LineContainer::drawCells(Array2D<Cell> &m_map){
	Cell *cell;
	int startX,startY,endX,endY;
	for(int i = 0; i < _xLineCount; ++i){
		for(int j = 0; j < _yLineCount; ++j){
			cell = m_map.Get(i,j);
			startX = leftMargin + cell->getX() * _eachBoxWidth + cellPadding;
			startY = bottomMargin + cell->getY() * _eachBoxHeight + cellPadding;
			endX = leftMargin + (cell->getX() + 1) * _eachBoxWidth - cellPadding;
			endY = bottomMargin + (cell->getY() + 1) * _eachBoxHeight - cellPadding;

            DrawPrimitives::drawSolidRect(Point(startX,startY),Point(endX,endY),CellColors[cell->getWeight() - 1]);
			if(cell->getDrawProgress()){
				DrawPrimitives::drawSolidRect(Point(startX,startY),Point(endX,endY),Color4F(0.0f,1.0f,0.6f,0.5f));
			}
		}
	}
}


void LineContainer::drawPath(deque<Cell*> &depCells){
    DrawPrimitives::setDrawColor4F(0.0,0.0,0.0,1.0);
	//Cell* cell;
	float startX,startY,endX,endY;
	for(deque<Cell*>::iterator itr = depCells.begin(); itr != depCells.end(); ++itr){
		startX = leftMargin + _eachBoxWidth * (*itr)->getX() + _eachBoxWidth / 2;
		startY = bottomMargin + _eachBoxHeight * (*itr)->getY() + _eachBoxHeight / 2;	
		++itr;
		if(itr != depCells.end()){
			endX = leftMargin + _eachBoxWidth * (*itr)->getX() + _eachBoxWidth / 2;
			endY = bottomMargin + _eachBoxHeight * (*itr)->getY() + _eachBoxHeight / 2;	
            DrawPrimitives::drawLine(Point(startX,startY),Point(endX,endY));
		}
		--itr;
	}

}

