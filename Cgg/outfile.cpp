/*************************************************************************
	> File Name: outfile.cpp
	> Author: 
	> Mail: 
	> Created Time: 一 11/20 21:21:51 2017
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int main()
{

    char arto[50];
    int year;
    double a_price;
    double d_price;

    ofstream outFile;
    outFile.open("9.c");

    cout << "enter the make and model of automobile:\n";
    cin.getline(arto, 50);
    cout << "enter in the model year:\n";
    cin >> year;
    cout << "enter the origin price:\n";
    cin >> a_price;
    d_price = a_price * 0.913;

    cout << fixed;
    cout.precision(2);
    cout.setf(ios_base::showpoint);
    cout << "make and model:" << arto << endl;
    cout << "year:" << year << endl;
    cout << "was asking :" << a_price << endl;
    cout << "now asking :" << d_price << endl;

    /*use the outFile */
    outFile << fixed;
    outFile.precision(2);
    outFile.setf(ios_base::showpoint);
    outFile << "input the file:\n";
    outFile << "make and model:" << arto <<endl;
    outFile << "year :" << year << endl;
    outFile << "was asking :" << a_price << endl;
    outFile << "now asking :" << d_price << endl;

    outFile.close();
    return 0;
}

