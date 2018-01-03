/*************************************************************************
	> File Name: school.h
	> Author: 
	> Mail: 
	> Created Time: 二  1/ 2 20:35:27 2018
 ************************************************************************/

#ifndef _USER_H
#define _USER_H
#include<iostream>
#include"school.h"
using namespace std;
/*用户*/
class user
{
private:
    AdjMatrix G;
public:
    user();//构造函数
    void user_menu();//用户菜单
    const int Locate(string name);//返回下标
    void read_information();//读取城市信息
    //void display_city();//显示导航地图
    void Read();//拉取地图信息
    void debug();
    void display();//显示导航地图
    void Dijkstra(int start,int end, int dist[], int path[][MAXVEX]);
    void Shortcut();//Dijkstra
    void search();
    void prim(int start);
    void MinSpanTree();//prim
};

#endif
