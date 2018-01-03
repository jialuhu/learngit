/*************************************************************************
	> File Name: school.cpp
	> Author: 
	> Mail: 
	> Created Time: 二  1/ 2 20:15:21 2018
 ************************************************************************/

#include<iostream>
#include<fstream>
#include<cstring>
#include"password.h"
#define MAXVEX 20
#define INFINITY 32768
using namespace std;

typedef struct
{
    int NO;//城市序号
    string name;//城市名称
}Vextype;//顶点的类型

typedef struct
{
    int arc[MAXVEX][MAXVEX]; //边集
    Vextype vex[MAXVEX];//顶点集合
    int vexnum;//顶点数目
    int arcnum;//边数目
}AdjMatrix;

/*用户*/
class user
{
private:
    int visited[MAXVEX];
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
    void DFS_tranvers();//遍历DFS
    void DFS(int start, int end);//DFS 
    void useDFS();//求出两个顶点的所有简单路径
    void findpaht();//查看某地交通状况
};

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
    void add();
    void deleted();
    void menu();
    void Read();
    void deletepath();
void addpath();
};

/*管理员构造函数*/
managers::managers()
{

}

/*定位函数*/
const int managers::Locate(string name_)
{
    int i=1;
    for(i=1; i<=Graph.vexnum; i++)
    {
        if(Graph.vex[i].name==name_)
        {
            return i;
        }
    }
    return -1;
}

/*创建地图*/
void managers::create()
{
    string start,end;
    int k0,k1;
    int weight;
    cout << "\033[2J\033[10;5H\n";
    cout << "\n\t\t\t\t\t\t\t请输入地点数目和路线数目:\n\t\t\t\t\t\t\t";
    cin >> Graph.vexnum;
    cin >> Graph.arcnum;
    for(int i=1; i<=Graph.vexnum; i++)
    {
        for(int j=1; j<=Graph.vexnum; j++)
        {
            Graph.arc[i][j] = INFINITY;
        }
    }
    cout << "\n\t\t\t\t\t\t\t请输入"<< Graph.vexnum << "个地点名称:"  << endl;
    for(int i=1; i<=Graph.vexnum; i++)
    {
        cout << "\n\t\t\t\t\t\t\tNO."<< i << ":" << i;
        Graph.vex[i].NO = i;
        cin >> Graph.vex[i].name;
    }
    cout << "\t\t\t\t\t\t\t请输入"<< Graph.arcnum << "条路线的起点和终点:"<< endl;
    for(int i=0; i<Graph.arcnum; i++)
    {
        cout << "\n\t\t\t\t\t\t\t起点:\n\t\t\t\t\t\t\t";
        cin >> start;
        cout << "\n\t\t\t\t\t\t\t终点:\n\t\t\t\t\t\t\t";
        cin >> end;
        k0 = Locate(start);
        k1 = Locate(end);
        cout << "\n\t\t\t\t\t\t\t请输入两地距离:\n\t\t\t\t\t\t\t";
        cin >> weight;
        Graph.arc[k0][k1] = weight;
        Graph.arc[k1][k0] = weight;
    }
}

/*管理员调试*/
void managers::debug()
{
    int j = 0;
    int i = 1;
    printf("\033[2J\033[10;5H");
    cout << "\n\t\t\t\t\t\t\t所有地点名称如下:\n\t\t\t\t\t\t\t";
    for(i=1; i<=Graph.vexnum; i++)
    {
        cout << "NO." << i <<":" << Graph.vex[i].name << " ";
        if(i%5==0) cout << "\n";
    }
    for(i=1; i<=Graph.vexnum; i++)
    {
        for(j=1; j<=Graph.vexnum; j++)
        {
            if(Graph.arc[i][j] != INFINITY)
            {
                cout <<"\n\t\t\t\t\t\t\t"<< Graph.vex[i].name << "----" << Graph.vex[j].name << ":" << Graph.arc[i][j]  <<"km"<<endl;
            }
        }
    }

}

void managers::Read()
{
    FILE *fp;
    //AdjMatrix G;
    if((fp = fopen("massage", "rt")) == NULL){
        printf("\033[31m\033[15;0H\t\t\t\t\t\t\t抱歉，无法正常读取!\n\033[0m");
    }
    fread(&Graph, sizeof(AdjMatrix), 1, fp);
    fclose(fp);
}
/*文件存储*/
void managers::save()
{
    FILE *fp;
    
    if((fp = fopen("massage", "wt")) == NULL){
        printf("\033[31m\033[15;0H\t\t\t\t\t\t\t抱歉，无法正常存储!\n\033[0m");
        return ;
    }
    fwrite(&Graph, sizeof(AdjMatrix), 1, fp);
    fclose(fp);
}

/*添加新的路线*/
void managers::add()
{
    string city1,city2;
    int s,e,weight;
    printf("\033[2J\033[10;5H");
    printf("\n\t\t\t\t\t\t\t请输入新的起点:\n\t\t\t\t\t\t\t");
    cin >> city1;
    s = Locate(city1);
    printf("\n\t\t\t\t\t\t\t请输入新的终点:\n\t\t\t\t\t\t\t");
    cin >> city2;
    e = Locate(city2);
    printf("\t\t\t\t\t\t\t距离:\n\t\t\t\t\t\t\t");
    scanf("%d",&weight);
    printf("\n");
    Graph.arc[s][e] = weight;
    Graph.arc[e][s] = weight;
}

/*删除新路线*/
void managers::deleted()
{
    string city;
    int s,e;
    printf("\033[2J\033[10;5H");
    printf("\t\t\t\t\t\t\t请输入删除的起点:\n\t\t\t\t\t\t\t");
    cin >> city;
    s = Locate(city);
    printf("\n\t\t\t\t\t\t\t请输入删除的终点:\n\t\t\t\t\t\t\t");
    cin >> city;
    printf("\n");
    e = Locate(city);
    Graph.arc[s][e] = INFINITY;
    Graph.arc[e][s] = INFINITY;
}
/*删除地点*/
void managers::deletepath()
{
    printf("\033[2J\033[15;5H");
    int i, j;
    int k0=0;
    string path;
    cout << "\n\t\t\t\t\t\t\t\033[33m请输入要删除的地点名称:\n\t\t\t\t\t\t\t";
    cin >> path;
    k0 = Locate(path);
    for(i=k0; i<Graph.vexnum; i++)
    {
        Graph.vex[i] = Graph.vex[i+1];
    }
    for(i=k0; i<Graph.vexnum; i++)
    {
        for(j=1; j<Graph.vexnum; j++)
        {
            Graph.arc[i][j] = Graph.arc[i+1][j];
        }
    }
    for(i = k0; i<Graph.vexnum; i++)
    {
        for(j=1; j<Graph.vexnum; j++)
        {
            Graph.arc[j][i] = Graph.arc[j][i+1];
        }
    }
Graph.vexnum = Graph.vexnum-1;

}
/*增加新的地点*/
void managers::addpath()
{
    cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t"<<Graph.vexnum<<endl;
    printf("\033[2J\033[15;5H");
    int i, j, counts;
    int k0=0,k1=0;
    int weights=0;
    string path;
    string city;
    cout << "\n\t\t\t\t\t\t\t\033[33m请输入要增加的地点名称:\n\t\t\t\t\t\t\t";
    cin >> path;
    k0 = ++Graph.vexnum;
    Graph.vex[k0].name = path;
    Graph.vex[k0].NO = k0;
    for(i=1; i<=Graph.vexnum; i++)
    {
        Graph.arc[k0][i] = INFINITY;
        Graph.arc[i][k0] = INFINITY;
    }
    cout << "\n\t\t\t\t\t\t\t\033[33m与该地点相连的边共有:\n\t\t\t\t\t\t\t";
    cin >> counts;
    Graph.arcnum += counts;
    while(counts){
        cout << "\n\t\t\t\t\t\t\t\033[33m请输入与该地点相通的终点:\n\t\t\t\t\t\t\t";
        cin >> city;
        k1 = Locate(city);
        cout << "\n\t\t\t\t\t\t\t\033[33m请输入两地的距离:\n\t\t\t\t\t\t\t";
        cin >> weights;
        Graph.arc[k0][k1] = weights;
        Graph.arc[k1][k0] = weights;
        counts--;
}
}
/*管理员菜单*/
void managers::menu()
{
    int choice=0;
    printf("\033[2J\033[15;5H");
    printf("\t\t\t\t\t\t\t\033[34m 1、新建地图                    \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 2、查看地图详情                \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 3、添加新路线                  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 4、删除旧路线                  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 5、增加地点                  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 6、删除地点                  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 7、返回                        \033[0m\n\n");
    printf("\n\n\t\t\t\t\t\t\t\033[37m 请输入选择:\033[0m\n\t\t\t\t\t\t\t");
    scanf("%d",&choice);
    Read();
    printf("\n");
    switch(choice)
    {
        case 1:
        {
            create();
            save();
            printf("\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            return managers::menu();
        }
        case 2:
        {
            debug();
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            getchar();
            return managers::menu();
        }
        case 3:
        {
            add();
            save();
            printf("\t\t\t\t\t\t\t\033[34m 添加成功！\033[0m\n");
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            getchar();
            return managers::menu();
        }
        case 4:
        {
        deleted();
            save();
            printf("\t\t\t\t\t\t\t\033[34m 删除成功！\033[0m\n");
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            getchar();
            return managers::menu();
        }
        case 5:
        {
            addpath();
            cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t"<<Graph.vexnum<<endl;
            save();
            printf("\t\t\t\t\t\t\t\033[34m 添加成功！\033[0m\n");
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            getchar();
            return managers::menu();
        }
        case 6:
        {
            deletepath();
            save();
            printf("\t\t\t\t\t\t\t\033[34m 删除成功！\033[0m\n");
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            getchar();
            return managers::menu();
        }
        case 7:
        {
            return;
        }
        default:
        {
            printf("\t\t\t\t\t\t\t输入不合法字符，请重新输入，按随意键返回!\n");
            getchar();
            return;
            
        }
    }
}





//构造函数初始化
user::user()
{
}
//读文件获取地图信息
void user::Read()
{
    FILE *fp;
    if((fp = fopen("massage", "rt")) == NULL){
        printf("\033[31m\033[15;0H\t\t\t\t\t\t\t抱歉，无法正常读取!\n\033[0m");
    }
    fread(&G, sizeof(AdjMatrix), 1, fp);
    fclose(fp);
}

/*定位函数*/
const int user::Locate(string name_)
{
    int i;
    for(i=1; i<=G.vexnum; i++)
    {
        if(name_ == G.vex[i].name)
        {
            return i;
        }
    }
    return -1;
}

/*DFS_tranvers*/
void user::DFS_tranvers()
{
    int j;
    for(j=1; j <= G.vexnum; j++)
    {
        visited[j] = 0;
    }
    for(j=1; j <= G.vexnum; j++)
    {
        if(visited[j]==0)
        {
            //DFS(j);
        }
    }
}

/*求出两个顶点的所有简单路径*/
int k=0;
int flags=0;
int path[MAXVEX]={0};
int minpath[MAXVEX]={0};
int weights[MAXVEX]={0};
int mins=MAXVEX;
int c = 1;
void user::useDFS()
{
    int k0,k1;
    string city1,city2;
    cout << "\033[2J\033[10;5H\n";
    cout << "\n\t\t\t\t\t\t请输入起点城市:\n\t\t\t\t\t\t";
    cin >> city1;
    cout << "\n\t\t\t\t\t\t请输入终点城市:\n\t\t\t\t\t\t";
    cin >> city2;
    k0 = Locate(city1);
    k1 = Locate(city2);
    path[0] = k0;
    cout << "\n\n\n";
    DFS(k0,k1);
    cout << "\n\t\t\t\t\t\t\033[34m中转点最少的路径为:\033[0m\n\t\t\t\t\t\t";
    for(int i=0; i<=mins; i++)
    {
        if(i==mins)
        {
            cout << G.vex[minpath[i]].name<<endl;
            break;
        }
        cout << G.vex[minpath[i]].name << "-->";
    }
    cout << "\n\t\t\t\t\t\t\033[33m输入任意键返回\033[0m";
}
void user::DFS(int start, int end)
{
    int i,j;
    visited[start] = 1;
    for(j=1; j<=G.vexnum; j++)
    {
        if(G.arc[start][j]!=INFINITY && visited[j]==0 && j!=end)
        {
            k++;
            path[k] = j;
            DFS(j,end);
            visited[j] = 0;
            k--;
            flags = 0;
            continue;
        }
        if(G.arc[start][j]!=INFINITY && flags==0 && j==end && visited[j]==0)
        {
            k++;
            path[k] = end;
            flags = 1;
            cout << "\t\t\t\t\t\tNO."<< c++ <<"路径有:"  <<"\n\t\t\t\t\t\t";
            for(int i=0; i<=k; i++)
            {
                if(i==k)
                {
                    cout << G.vex[path[i]].name;
                    continue;
                }
                cout  << G.vex[path[i]].name <<"-->";
            }
            if(k < mins)
            {
                mins= k;
                for(int i=0; i<=k; i++)
                {
                    minpath[i] = path[i];
                }
            }
            cout << "\n";
            k--;
            return;
        }
    }
}

/*中专点最少的路径*/
void useBFS(int start, int end)
{
    
}

/*获取查询城市的详细信息*/
void user::read_information()
{
    ifstream finout;
    string city;
    char buffer[500];
    cout << "\t\t\t\t\t\t\t请输入要查询的城市名称:\n\t\t\t\t\t\t\t";
    cin >> city;
    int judge = Locate(city);
    finout.open(city.c_str());
    if(judge == -1)
       {
        cout << "\t\t\t\t\t\t\t暂时没有该城市,请重新输入,任意键返回!\n";
        getchar();
        getchar();
        return;
    }
    else{
        if(finout.is_open())
        {
            finout.read((char *)&buffer,500);
        }
    }
    finout.close();
    cout << "\n\n";
    cout << buffer << endl;
    cout << "\t\t\t\t\t\t\t输入任意键返回!\n";
    getchar();
}

/*用户调试*/
void user::debug()
{
    cout << "\033[2J\033[10;5H\n";
    cout << "\n\t\t\t\t\t\t\t该地图一共有" << G.vexnum << "个地方,"
        << G.arcnum << "条路径" << "\n\t\t\t\t\t\t\t\t";
    for(int i=1; i<=G.vexnum; i++)
    {
        cout << "\n\t\t\t\t\t\t\t" << G.vex[i].NO << ":" << G.vex[i].name << " ";
    }
    cout << "\n";
    for(int i=1; i<=G.vexnum; i++)
    {
        for(int j=1; j<=G.vexnum; j++)
        {
            if(G.arc[i][j]!=INFINITY)
            {
                cout << "\n\t\t\t\t\t\t\t" << G.vex[i].name << "--->" << G.vex[j].name << endl;
            }
        }
    }
}
//查询路径
void user::search()
{
    string city;
    int NO,i,j;
    printf("\033[2J\033[10;5H");
    printf("\n\t\t\t\t\t\t\t请输入要查询的城市名称:\n\t\t\t\t\t\t\t");
   // scanf("%s",city);
    cin >> city;
    NO = Locate(city);
    printf("\n\t\t\t\t\t\t\t打印当前城市的状况:\n\t\t\t\t\t\t\t");
    for(i=1; i<=G.vexnum; i++)
    {
        if(i==NO)
        {
            for(j=1; j<=G.vexnum; j++)
            {
                if(G.arc[i][j]!=INFINITY)
                {
                    cout << "\n\t\t\t\t\t\t\t" << G.vex[i].name << "-----" <<G.vex[j].name << ":" << G.arc[i][j] << "km" << endl;
                }
            }
        }
    }
}

//显示导航地图
void user::display()
{
    printf("\033[2J\033[10;5H");
    int i,j;
    printf("\t\t\t\t\t\t\t输出交通情况:\n");
    for(i=1; i<=G.vexnum; i++)
    {
        for(j=1; j<=G.vexnum; j++)
        {
            if(G.arc[i][j]!=INFINITY)
            {
                cout << "\t\t\t\t\t\t\t"<< G.vex[i].name <<"-----" << G.vex[j].name << ":" << G.arc[i][j] << "km\n";
            }
        }
    }
    getchar();
}
//Dijkstra
void user::Dijkstra(int start, int end, int dist[], int path[][MAXVEX])
{
    int mindist, i, j, k, t = 1;
    
    //初始化
    for(i = 1; i <= G.vexnum; i++){
        dist[i] = G.arc[start][i];
        if(G.arc[start][i] != INFINITY)
            path[i][1] = start;
    }
    path[start][0] = 1;
    
    //寻求最短路径
    for(i = 2; i <= G.vexnum; i++){
        mindist = INFINITY;
        for(j = 1; j <= G.vexnum; j++){
            if(!path[j][0] && dist[j] < mindist){
                mindist = dist[j];
                k = j;
            }
        }
        if(mindist == INFINITY)  break;
        path[k][0] = 1;
        
        //修改加入后的最短路径
        for(j = 1; j <= G.vexnum; j++){
            if(!path[j][0] && G.arc[k][j] < INFINITY && G.arc[k][j] + dist[k] < dist[j]){
                dist[j] = dist[k] + G.arc[k][j];
                
                //记录最短路径
                t = 1;
                while(path[k][t]){
                    path[j][t] = path[k][t];
                    t++;
                }
                path[j][t] = k;
                path[j][t+1] = 0;
            }
        }
    }
    if(dist[end] == INFINITY){
        cout << "\n\n\t\t\t\t\t\t\t"<<G.vex[start].name<<"----->"<<G.vex[end].name<<"  不存在通路!!!\n";
        return;
    }
    //输出最短路径
    cout << "\n\n\t\t\t\t\t\t\t"<<G.vex[start].name<<"到"<< G.vex[end].name <<"的最短路线："<<G.vex[start].name;
    for(j = 2; path[end][j]; j++)
        cout << "---->"<< G.vex[path[end][j]].name;
    cout << "--->"<< G.vex[end].name;
    printf("\n\t\t\t\t\t\t\t总路程为：%d\n", dist[end]);
    
}
/*求最短路径*/
void user::Shortcut()
{
    string city;
    int star,end;
    int dist[MAXVEX];
    int path[MAXVEX][MAXVEX]={0};
    printf("\033[2J\033[10;5H");
    printf("\t\t\t\t\t\t\t请输入起点城市名称:\n\t\t\t\t\t\t\t");
    cin >> city;
    star = Locate(city);
    printf("\t\t\t\t\t\t\t请输入终点城市名称:\n\t\t\t\t\t\t\t");
    cin >> city;
    end = Locate(city);
    Dijkstra(star,end,dist,path);
    printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m");
    getchar();
}

//prim算法求最短连通图
void user::prim(int start)
{
    struct{
        int adjvex;
        int lowcost;
    }closedge[MAXVEX];
    
    int i,e,k,m,min;
    /*开始顶点已经加入集合*/
    closedge[start].lowcost = 0;
    /*初始化lowcost数组*/
    for(i=1; i<=G.vexnum; i++)
    {
        if(i!=start)
        {
            closedge[i].adjvex = start;
            closedge[i].lowcost = G.arc[start][i];
        }
    }
    /*最小生成树符合n-1条边*/
    for(e=1; e<=G.vexnum-1; e++)
    {
        min = INFINITY;
        for(k=1; k<=G.vexnum; k++)
        {
            if(closedge[k].lowcost!=0&&closedge[k].lowcost<min)
            {
                m = k;
                min = closedge[k].lowcost;
            }
        }
        cout << "\t\t\t\t\t\t\t\033[34m从"<<G.vex[closedge[m].adjvex].name<<"-----"<<G.vex[m].name<<" "<<closedge[m].lowcost <<"km"<<"\033[0m\n";
        closedge[m].lowcost = 0;
        //开始顶点加入之后要更新closedge数组信息
        for(i=1; i<=G.vexnum;i++)
        {
            if(i!=m&&G.arc[m][i]<closedge[i].lowcost)
            {
                closedge[i].lowcost = G.arc[m][i];
                closedge[i].adjvex = m;
            }
        }
        
    }
    
}

void user::findpaht()
{
    printf("\033[2J\033[10;5H");
    int i=0;
    int j=0;
    int k;
    string city;
    cout << "\n\t\t\t\t\t\t请输入要查询交通情况的城市名称:\n\t\t\t\t\t\t";
    cin >> city;
    k = Locate(city);
    cout << "\n\t\t\t\t\t\t\033[33m" << G.vex[k].name <<"交通状况如下:\033[0m\n";
    for(i=1; i<=G.vexnum; i++)
    {
        if(G.arc[k][i] != INFINITY)
        {
            cout << "\n\t\t\t\t\t\t\033[34m" << G.vex[k].name << "--->" << G.vex[i].name << ":" << G.arc[k][i] <<"km\033[0m\n"; 
        }
    }
    printf("\n\t\t\t\t\t\t\033[34m输入任意键返回\033[0m\n");
    getchar();
    cout << "\t\t\t\t\t\t";
}

/*查询某个城市的最短连通图*/
void user::MinSpanTree()
{
    //char city[20];
    string city;
    int start;
    printf("\033[2J\033[10;5H");
    printf("\t\t\t\t\t\t\t请输入起点城市:\n\t\t\t\t\t\t\t");
    cin >> city;
    //scanf("%s",city);
    start = Locate(city);
    prim(start);
    printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m");
    getchar();
}
/*用户菜单*/
void user::user_menu()
{
    int choice=0;
    printf("\033[2J\033[15;5H");
    printf("\t\t\t\t\t\t\t\033[34m 1、查看地图                      \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 2、查看某地交通状况              \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 3、查找某地到出发的最短连通路线  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 4、查找某地到某地的最短路线      \033[0m\n\n ");
    printf("\t\t\t\t\t\t\t\033[34m 5、查看某地介绍                  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 6、查找简单路径以及最简单路径    \033[0m\n\n ");
    printf("\t\t\t\t\t\t\t\033[34m 7、返回                          \033[0m\n\n");
    printf("\n\n\t\t\t\t\t\t\t\033[37m 请输入选择:\033[0m\n\t\t\t\t\t\t\t");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1://查看地图情况
        {
            display();
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m");
            getchar();
            getchar();
            return user_menu();
        }
        case 2://查看某地交通状况
        {
            findpaht();
            getchar();
            return user_menu();
        }
        case 3://最小生成树
        {
            MinSpanTree();//最短连通图prim
            getchar();
            return user_menu();
        }
        case 4://某地到其他地方的最短单源路径
        {
            Shortcut();//最短路径Dijkstra
            getchar();
            return user_menu();
        }
        case 5://查看某地的详细信息
        {
            read_information();
            getchar();
            return;
        }
        case 6://查找某地到某地的简单路径以及最短简单路径
        {
            useDFS();
            getchar();
            getchar();
            return user_menu();
        }
        case 7:
        {
            return;
        }
        default:
        {
            printf("\t\t\t\t\t\t\t输入不合法字符，请重新输入，按随意键返回!\n");
            return user_menu();
        }
    }
}


/*第一个主界面*/
int mainmenu()
{
    int choice=0;
    printf("\033[2J\033[10;6H");
    printf("\t\t\t\t\t\t\t\033[44;37m                    \033[0m\n");
    printf("\t\t\t\t\t\t\t\033[44;37m    1、 用户登录    \033[0m\n");
    printf("\t\t\t\t\t\t\t\033[44;37m                    \033[0m\n");
    printf("\n\n\n\n");
    printf("\t\t\t\t\t\t\t\033[43;37m                    \033[0m\n");
    printf("\t\t\t\t\t\t\t\033[43;37m  2、管理员登陆登录 \033[0m\n");
    printf("\t\t\t\t\t\t\t\033[43;37m                    \033[0m\n");
    printf("\n\n\n\n");
    printf("\t\t\t\t\t\t\t\033[46;37m                    \033[0m\n");
    printf("\t\t\t\t\t\t\t\033[46;37m  3、退 出 系 统    \033[0m\n");
    printf("\t\t\t\t\t\t\t\033[46;37m                    \033[0m\n");
    printf("\n\n\t\t\t\t\t\t\t 请输入要选择的数字:\n\t\t\t\t\t\t\t");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        {
            user hu;
            hu.Read();
            hu.user_menu();
            break;
        }
        case 2:
        {
            sign_in m;
            m.match();
            managers M;
            M.menu();
            break;
        }
        case 3:
        {
            exit(0);
        }
        default:
        {
            printf("\t\t\t\t\t\t\t[33m 输入不合法输入任意键返回!\033[0m\n");
            getchar();
            getchar();
            return mainmenu();
        }
    }
    printf("\n");
    return 0;
}


int main()
{
    while (1) {
        mainmenu();
    }
}






