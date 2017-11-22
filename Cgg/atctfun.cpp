/*************************************************************************
	> File Name: atctfun.cpp
	> Author: 
	> Mail: 
	> Created Time: 三 11/22 19:54:20 2017
 ************************************************************************/

#include<iostream>
#include<cmath>
using namespace std;
struct polar
{
    double distance;
    double angle;
};
struct rect
{
    double x;
    double y;
};
polar rect_ro_polar(rect rplace);
void prin(polar pplace);
int main()
{
    rect rplace;
    polar pplace;

    cout << "enter the x and y values:\n";
    while(cin >> rplace.x >> rplace.y)
    {
        pplace = rect_ro_polar(rplace);
        prin(pplace);
    }
   // prin(pplace);
    return 0;
}

polar rect_ro_polar(rect rplace)
{
    using namespace std;
    polar answer;

    answer.distance = sqrt(rplace.x*rplace.x+rplace.y*rplace.y);//根据毕大哥达拉斯定理计算距离
    answer.angle = atan2(rplace.y,rplace.x);//计算出角度
    return answer;
}

void prin(polar pplace)
{
    const double Rad_to_deg = 57.29577951;
    cout << "distance=" << pplace.distance;
    cout << ",angle=" << pplace.angle*Rad_to_deg;
}
