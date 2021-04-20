#pragma once
#ifndef __MAINMAP_H
#define __MAINMAP_H

enum CrossType
{
	straight = 0,
	left = 1,
	right = 2,
	Tcross = 3,
	noLine = 4,
	ErrorNode=5
};
struct MapNode
{
	CrossType startCrossType;
	//CrossType nextCrossType;
	void * processfun();
	bool processFunIsEnded;
	int maxLength;
};




//this function process snesers' data from bits to lines;
void getLines();

//this function revise the car to the line 
//before run this function run function getLines() first;
void getToLine();

bool errorJudge();
CrossType getCurrentCrossType();
void CrossProcess();
//Normal Process on line
void TrailProcess();
void ProcessMap();



#endif