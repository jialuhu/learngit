/*************************************************************************
	> File Name: school.h
	> Author: 
	> Mail: 
	> Created Time: 二  1/ 2 20:35:27 2018
 ************************************************************************/

#ifndef _MANAGERS_H
#define _MANAGERS_H
#include<iostream>
#include"school.h"
using namespace std;
/*管理员*/
class managers
{
private:
    AdjMatrix Graph;
public:
    managers();
    void m_write();
    void create();
    const int Locate(string name);
    void debug();
    void save();
    void menu();
};

#endif
