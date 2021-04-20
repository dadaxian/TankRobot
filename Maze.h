#ifndef MAZE_H
#define MAZE_H
#include <Wire.h>
#include <Servo.h>
#include "HC_SR04.h"
//#include "GearMotor.h"
#include "carAction.h"
#include "HC_SR04.h"


// Software serial pin for tx
#define KS103ADDR 0x74    // Address of the 0xe8  ?????????????20??
#define Reg 0x02        // Command byte ???02??????



extern int  ltrig;
extern int  lecho;
extern int  rtrig;
extern int  recho;


extern byte highByte;   // Stores high byte from ranging
extern byte lowByte;   // Stored low byte from ranging


extern int  wideLenth[7];

extern int mazeHeadGroup[7];

int getMaxPulse(int a[], int n);


class Maze {
public:
	int RMazeSpeed;
	int LMazeSpeed;

	Maze();

	void setSpeed(int Rspeed, int Lspeed);

	void Init();

	void test();

	void goMaze();

	unsigned char GetDirection();

	int getRange();

	
};






#endif






