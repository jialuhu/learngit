/*************************************************************************
	> File Name: school.h
	> Author: 
	> Mail: 
	> Created Time: 二  1/ 2 20:35:27 2018
 ************************************************************************/

#ifndef _SCHOOL_H
#define _SCHOOL_H
#include<iostream>
using namespace std;

typedef struct
{
    int NO;//城市序号
    char name[20];//城市名称
}Vextype;//顶点的类型

typedef struct
{
    int arc[MAXVEX][MAXVEX]; //边集
    Vextype vex[MAXVEX];//顶点集合
    int vexnum;//顶点数目
    int arcnum;//边数目
}AdjMatrix;

#endif
