#pragma once
#include "led.h"
#include "ColorJudge.h"
#include "Maze.h"
#include "GrayScaleSensor.h"
#include "GearMotor.h"
#include"Infrared.h"	
#include "keyBoard.h"

#include<math.h>
//#include "MainMap.h"

#define Normal 0x10
#define NormalError 0x11
#define None 0x12

extern unsigned char mapp[];
extern unsigned char errorClass[];
extern unsigned char mappClass[];

//类定义
extern GearMotor myGearMotor;
extern SEN2020 mySen2020;
extern Maze myMaze;
extern Tsc230 myTsc230;
extern LobotServoController myLobotServoController;
extern HC_SR04 *LHC_SR04, *RHC_SR04;
extern Infrared* ir;

//整车初始化
void CAR_Init();

//启动
void WaitingForStart();


//循迹
void trailforCM(int cm);

void Trail_Only();
//壁障
void correctDIR();
void correctDIR1();
void maze();
void Deathmaze();

void judgeColorAndProcess();
int towardsToAimMaterial(int interval, int time);
int getMaxlengthAngle(int interval, int time);

void getMaterial();
void goAndGetMaterial();
void GetNextClosedestMaterial();
void Material();
void Material2();

void getOneMaterial();

//扔物块
void DropMaterial();

//穿越太空区
void goThroughSpace();