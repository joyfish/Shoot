#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include "cocos2d.h"

USING_NS_CC;

const int topMargin = 0;
const int bottomMargin = 0;
const int leftMargin = 0;
const int rightMargin = 0;
//const int xLineCount = 28;
//const int yLineCount = 21;

const int DIRECTION[8][2]={
	{0,1},  //north
	{1,0},  //east
	{0,-1},  //south
	{-1,0},  //west
	{1,1},  //northeast
	{1,-1},  //southeast
	{-1,-1},  //southwest
	{-1,1}  //northwest
};

const float DISTANCE[8]={
	1,
	1,
	1,
	1,
	1.414f,
	1.414f,
	1.414f,
	1.414f
};

const float cellPadding = 3.0;

const Color4F CellColors[4] = {
	Color4F(1.0,1.0,1.0,1.0),         //white
	Color4F(0.66f,0.66f,0.66f,1.0),   //gray
	Color4F(0.33f,0.33f,0.33f,1.0),   //deep gray
	Color4F(0.0,0.0,0.0,1.0)          //black
};

const float drawPathSpeed = 0.1f;
#endif