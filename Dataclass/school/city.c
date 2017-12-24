/*************************************************************************
	> File Name: city.c
	> Author: 
	> Mail: 
	> Created Time: 四 12/21 21:04:14 2017
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"map.h"
#include"password.h"
#define MAXVEX 20
#define INFINITY 32768

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

//用户菜单
void user_menu(AdjMatrix *Graph);
//管理员菜单
void manager_menu(AdjMatrix *Graph);
//文件图存储
void Store(AdjMatrix *G);
//文件图读取
AdjMatrix Read();

//根据城市名称来确定城市下标的序号
int Locate(AdjMatrix *Graph, char *name)
{
    int i;
    for(i=1; i<=Graph->vexnum;i++)
    {
        if(!strcmp(name,Graph->vex[i].name))
        {
            return i;
        }
    }
    return -1;
}

//采用邻接矩阵创建无向图
int create(AdjMatrix *Graph)
{
    char city[20];
    int k0,k1;
    int weight;
    printf("\033[2J\033[10;5H");
    printf("\n\t\t\t\t\t\t\t请输入城市数目和路线数目:\n\t\t\t\t\t\t\t");
    scanf("%d %d",&Graph->vexnum,&Graph->arcnum);
    for(int i=1; i<=Graph->vexnum; i++)
    {
        for(int j=1; j<=Graph->vexnum;j++)
        {
            Graph->arc[i][j] = INFINITY;
        }
    }
    printf("\t\t\t\t\t\t\t请输入图中%d个城市以及它的名称:\n\t\t\t\t\t\t\t",Graph->vexnum);
    for(int i=1; i<=Graph->vexnum; i++)
    {
        printf("\n\t\t\t\t\t\t\tNO.%d:\n\t\t\t\t\t\t\t",i);
        Graph->vex[i].NO = i;
        scanf("%s",Graph->vex[i].name);
    }
    printf("\t\t\t\t\t\t\t请输入图中总共有%d条路线:\n\t\t\t\t\t\t\t",Graph->arcnum);
    for(int i=0;i<Graph->arcnum;i++)
    {
        printf("\n\t\t\t\t\t\t\t起点城市:\n\t\t\t\t\t\t\t");
        scanf("%s",city);
        k0 = Locate(Graph,city);
        printf("\n\t\t\t\t\t\t\t终点城市:\n\t\t\t\t\t\t\t");
        scanf("%s",city);
        k1 = Locate(Graph,city);
        printf("\n\t\t\t\t\t\t\t距离:\n\t\t\t\t\t\t\t");
        scanf("%d",&weight);
        Graph->arc[k0][k1] = weight;
        Graph->arc[k1][k0] = weight;
    }
    return 0;
}

//显示图
void display(AdjMatrix *Graph)
{
    printf("\033[2J\033[10;5H");
    int i,j;
    printf("\t\t\t\t\t\t\t输出交通情况:\n");
    for(i=1; i<=Graph->vexnum; i++)
    {
        for(j=1; j<=Graph->vexnum; j++)
        {
            if(Graph->arc[i][j]!=INFINITY)
            {
                printf("\t\t\t\t\t\t\t%s-----%s:%dkm\n",Graph->vex[i].name,Graph->vex[j].name,Graph->arc[i][j]);
            }
        }
    }
    //printf("\t\t\t\t\t\t\t输入任意键返回");
    getchar();
}

//查询路径
void search(AdjMatrix *Graph)
{
    char city[20];
    int NO,i,j;
    printf("\033[2J\033[10;5H");
    printf("\n\t\t\t\t\t\t\t请输入要查询的城市名称:\n\t\t\t\t\t\t\t");
    scanf("%s",city);
    city[strlen(city)+1] = '\0';
    NO = Locate(Graph,city);
    printf("\n\t\t\t\t\t\t\t打印当前城市的状况:\n\t\t\t\t\t\t\t");
    for(i=1; i<=Graph->vexnum; i++)
    {
        if(i==NO)
        {
            for(j=1; j<=Graph->vexnum; j++)
            {
                if(Graph->arc[i][j]!=INFINITY)
                {
                    printf("\n\t\t\t\t\t\t\t%s----%s:%d\n",Graph->vex[i].name,Graph->vex[j].name,Graph->arc[i][j]);
                }
            }
        }
    }
}


/*添加新的路线*/
void add(AdjMatrix *Graph)
{
    char city[20];
    int s,e,weight;
    printf("\033[2J\033[10;5H");
    printf("\n\t\t\t\t\t\t\t请输入新的起点:\n\t\t\t\t\t\t\t");
    scanf("%s",city);
    s = Locate(Graph,city);
    printf("\n\t\t\t\t\t\t\t请输入新的终点:\n\t\t\t\t\t\t\t");
    scanf("%s",city);
    e = Locate(Graph,city);
    printf("\t\t\t\t\t\t\t距离:\n\t\t\t\t\t\t\t");
    scanf("%d",&weight);
    printf("\n");
    Graph->arc[s][e] = weight;
    Graph->arc[e][s] = weight;
}

/*删除新路线*/
void delete(AdjMatrix *Graph)
{
    char city[20];
    int s,e;
    printf("\033[2J\033[10;5H");
    printf("\t\t\t\t\t\t\t请输入删除的起点:\n\t\t\t\t\t\t\t");
    scanf("%s",city);
    s = Locate(Graph,city);
    printf("\n\t\t\t\t\t\t\t请输入删除的终点:\n\t\t\t\t\t\t\t");
    scanf("%s",city);
    printf("\n");
    e = Locate(Graph,city);
    Graph->arc[s][e] = INFINITY;
    Graph->arc[e][s] = INFINITY;
}

void Dijkstra(AdjMatrix *G, int start, int end, int dist[], int path[][MAXVEX])
{
    int mindist, i, j, k, t = 1;
    
    //初始化
    for(i = 1; i <= G->vexnum; i++){
        dist[i] = G->arc[start][i];
        if(G->arc[start][i] != INFINITY)
            path[i][1] = start;
    }
    path[start][0] = 1;
    
    //寻求最短路径
    for(i = 2; i <= G->vexnum; i++){
        mindist = INFINITY;
        for(j = 1; j <= G->vexnum; j++){
            if(!path[j][0] && dist[j] < mindist){
                mindist = dist[j];
                k = j;
            }
        }
        if(mindist == INFINITY)  break;
        path[k][0] = 1;
        
        //修改加入后的最短路径
        for(j = 1; j <= G->vexnum; j++){
            if(!path[j][0] && G->arc[k][j] < INFINITY && G->arc[k][j] + dist[k] < dist[j]){
                dist[j] = dist[k] + G->arc[k][j];
                
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
        printf("\n\n\t\t\t\t\t\t\t%s----->%s  不存在通路!!!\n", G->vex[start].name, G->vex[end].name);
        return;
    }
    //输出最短路径
    printf("\n\n\t\t\t\t\t\t\t%s到%s的最短路线：%s ", G->vex[start].name, G->vex[end].name, G->vex[start].name);
    for(j = 2; path[end][j]; j++)
        printf("——>%s ", G->vex[path[end][j]].name);
    printf("——>%s", G->vex[end].name);
    printf("\n\t\t\t\t\t\t\t总路程为：%d\n", dist[end]);
    
}
/*求最短路径*/
void Shortcut(AdjMatrix *Graph)
{
    char city[20];
    int star,end;
    int dist[MAXVEX];
    int path[MAXVEX][MAXVEX]={0};
    printf("\033[2J\033[10;5H");
    printf("\t\t\t\t\t\t\t请输入起点城市名称:\n\t\t\t\t\t\t\t");
    scanf("%s",city);
    star = Locate(Graph,city);
    printf("\t\t\t\t\t\t\t请输入终点城市名称:\n\t\t\t\t\t\t\t");
    scanf("%s",city);
    end = Locate(Graph,city);
    Dijkstra(Graph,star,end,dist,path);
    printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m");
    getchar();
}

//prim算法求最短连通图
void prim(AdjMatrix *G,int start)
{
    struct{
        int adjvex;
        int lowcost;
    }closedge[MAXVEX];

    int i,e,k,m,min;
    /*开始顶点已经加入集合*/
    closedge[start].lowcost = 0;
    /*初始化lowcost数组*/
    for(i=1; i<=G->vexnum; i++)
    {
        if(i!=start)
        {
            closedge[i].adjvex = start;
            closedge[i].lowcost = G->arc[start][i];
        }
    }
    /*最小生成树符合n-1条边*/
    for(e=1; e<=G->vexnum-1; e++)
    {
        min = INFINITY;
        for(k=1; k<=G->vexnum; k++)
        {
            if(closedge[k].lowcost!=0&&closedge[k].lowcost<min)
            {
                m = k;
                min = closedge[k].lowcost;
            }
        }
        printf("\t\t\t\t\t\t\t\033[34m从%s-----%s: %d km\033[0m\n",G->vex[closedge[m].adjvex].name,G->vex[m].name,closedge[m].lowcost);
        closedge[m].lowcost = 0;
        //开始顶点加入之后要更新closedge数组信息
        for(i=1; i<=G->vexnum;i++)
        {
            if(i!=m&&G->arc[m][i]<closedge[i].lowcost)
            {
                closedge[i].lowcost = G->arc[m][i];
                closedge[i].adjvex = m;
            }
        }
        
    }

}

/*查询某个城市的最短连通图*/
void MinSpanTree(AdjMatrix *Graph)
{
    char city[20];
    int start;
    printf("\033[2J\033[10;5H");
    printf("\t\t\t\t\t\t\t请输入起点城市:\n\t\t\t\t\t\t\t");
    scanf("%s",city);
    start = Locate(Graph,city);
    prim(Graph,start);
    printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m");
    getchar();
}

/*第一个主界面*/
int mainmenu(AdjMatrix *Graph)
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
            user_menu(Graph);
            break;
        }
        case 2:
        {
            int state=0;
            state = password();
            if(state == -1) return mainmenu(Graph);
            if(state == 1)
            {
                manager_menu(Graph);
            }
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
            return mainmenu(Graph);
        }
    }
    printf("\n");
    return 0;
}

/*用户菜单*/
void user_menu(AdjMatrix *Graph)
{
    int choice=0;
    printf("\033[2J\033[15;5H");
    printf("\t\t\t\t\t\t\t\033[34m 1、查看地图                      \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 2、查看某地信息                  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 3、查找某地到出发的最短连通路线  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 4、查找某地到某地的最短路线      \033[0m\n\n ");
    printf("\t\t\t\t\t\t\t\033[34m 5、返回                          \033[0m\n\n");
    printf("\n\n\t\t\t\t\t\t\t\033[37m 请输入选择:\033[0m\n\t\t\t\t\t\t\t");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
        {
            map();
            printf("\t\t\t\t\t\t\033[33m输入任意键返回\033[0m");
            return user_menu(Graph);
        }
        case 2:
        {
            display(Graph);
            printf("\n\t\t\t\t\t\t\t输入任意键返回\n\t\t\t\t\t\t\t");
            getchar();
            return user_menu(Graph);
        }
        case 3:
        {
            MinSpanTree(Graph);//最短连通图prim
            getchar();
            return user_menu(Graph);
        }
        case 4:
        {
           Shortcut(Graph);//最短路径Dijkstra
           getchar();
            return user_menu(Graph);
        }
        case 5:
        {
            return;
        }
        default:
        {
            printf("\t\t\t\t\t\t\t输入不合法字符，请重新输入，按随意键返回!\n");
            return user_menu(Graph);
        }
    }
}

/*管理员登录菜单*/
void manager_menu(AdjMatrix *Graph)
{
    int choice=0;
    //password();
    printf("\033[2J\033[15;5H");
    printf("\t\t\t\t\t\t\t\033[34m 1、新建地图                    \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 2、查看地图详情                \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 3、添加新路线                  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 4、删除旧路线                  \033[0m\n\n");
    printf("\t\t\t\t\t\t\t\033[34m 5、返回                        \033[0m\n\n");
    printf("\n\n\t\t\t\t\t\t\t\033[37m 请输入选择:\033[0m\n\t\t\t\t\t\t\t");
    scanf("%d",&choice);
    printf("\n");
    switch(choice)
    {
        case 1:
        {
            create(Graph);
            Store(Graph);
            printf("\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            return manager_menu(Graph);
        }
        case 2:
        {
            display(Graph);
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            return manager_menu(Graph);
        }
        case 3:
        {
            add(Graph);
            Store(Graph);
            printf("\t\t\t\t\t\t\t\033[34m 添加成功！\033[0m\n");
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            getchar();
            return manager_menu(Graph);
        }
        case 4:
        {
            delete(Graph);
            Store(Graph);
            printf("\t\t\t\t\t\t\t\033[34m 删除成功！\033[0m\n");
            printf("\t\t\t\t\t\t\t\033[33m输入任意键返回\033[0m\n\t\t\t\t\t\t\t");
            getchar();
            getchar();
            return manager_menu(Graph);
            }
        case 5:
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

//存储景点及路径信息
void Store(AdjMatrix *G)
{
    FILE *fp;
    
    if((fp = fopen("message", "wt")) == NULL){
        printf("\033[31m\033[15;0H\t\t\t\t\t\t\t抱歉，无法正常存储!\n\033[0m");
        return ;
        
    }
    //printf("\033[33m\033[15;0H\t\t\t\033[31m+\033[0m   存储信息中...\n");
    fwrite(G, sizeof(AdjMatrix), 1, fp);
    fclose(fp);
    //printf("\033[2J\033[15;0H\t\t\t\t\t恭喜，存储成功!\n\n\n\033[0m");
}

//读取景点及路线信息
AdjMatrix Read()
{
    FILE *fp;
    AdjMatrix G;
    if((fp = fopen("message", "rt")) == NULL){
        printf("\033[31m\033[15;0H\t\t\t\t\t\t\t抱歉，无法正常读取!\n\033[0m");
        return G;
    }
    //printf("\033[33m\033[15;0H\t\t\t\t\t\t\t\033[31m+\033[0m   读取信息中...\n");
    fread(&G, sizeof(AdjMatrix), 1, fp);
    fclose(fp);
    //printf("\033[2J\033[15;0H\t\t\t\t\t\t\t恭喜,  读取成功!\n");
    return G;
}


int main()
{
    AdjMatrix Graph;
    int choice=1;
    Graph = Read();
    do{
        mainmenu(&Graph);
    }while(choice);
    /*do{
        printf("\n\t\t\t\t城市导航系统\t\t\t\t\t");
        printf("\n\t\t\t\t1、显示基本信息");
        printf("\n\t\t\t\t2、查询某个城市基本情况");
        printf("\n\t\t\t\t3、添加新路径");
        printf("\n\t\t\t\t4、撤销新路径");
        printf("\n\t\t\t\t5、从某个城市出发到另一个城市的最短路线查询");
        printf("\n\t\t\t\t6、从某个城市出发到其他所有城市的最短连通路线查询");
        printf("\n\t\t\t\t7、退出");
        printf("\n\t\t\t\t7、请输入选择:i\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            {
                display(&Graph);
                break;
            }
            case 2:
            {
                search(&Graph);
                break;
            }
            case 3:
            {
                add(&Graph);
                break;
            }
            case 4:
            {
                delete(&Graph);
                break;
            }
            case 5:
            {
                Shortcut(&Graph);
                break;
            }
            case 6:
            {
                MinSpanTree(&Graph);
                break;
            }
            case 7:
            {
                return 0;
            }
        }


    }while(1);*/

    return 0;
}
