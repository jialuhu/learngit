/*************************************************************************
	> File Name: password.cpp
	> Author: 
	> Mail: 
	> Created Time: 二  1/ 2 13:09:28 2018
 ************************************************************************/

#include<iostream>
#include<cstring>
using namespace std;
typedef struct manage
{
    string name;
    string pass;
}manager;

class sign_in
{
private:
    manager use;
public:
    sign_in();//无参构造函数
    sign_in(string id,string pass);
    void match();//登录匹配函数
};

sign_in::sign_in()
{
    use.name = "hujialu";
    use.pass = "000000";
}

sign_in:: sign_in(string id, string pass)
{
    use.name = id;
    use.pass = pass;
}

void sign_in::match()
{
    cout << "\033[2J\033[15;5H";
    int i = 3;
    string id;
    string password;
    do{
        cout << "\t\t\t\t\t\t\033[34m请输入用户名:\033[0m\n\t\t\t\t\t\t";
        cin >> id;
        cout <<"\t\t\t\t\t\t请输入密码:\033[0m\n\t\t\t\t\t\t";
        system("stty -echo");
        cin >> password;
        system("stty echo");
        if(id == use.name && password == use.pass)
        {
            cout << "\n\t\t\t\t\t\t\033[33m登录成功!\033[0m\n\n";
            cout << "\t\t\t\t\t\t\033[33m任意键进入界面\033[0m\n";
            getchar();
            getchar();
            return;
        }
        else{
            cout << "\t\t\t\t\t\t\033[33m 您还有%d次机会重新输入!" << i << endl;
        }
    }while(i--);
}

int main()
{
    sign_in use1;
    use1.match();
    return 0;
}
