#pragma once
#ifndef __MYMATH_H
#define __MYMATH_H

#define MED_WIDTH_NUM 10


extern int Moving_Median_int(int in_int, int item); //��λ��

int remap(int val, int minVal, int maxVal, int minOut, int maxOut);

int getmax(int* nums, int count);

#endif