/*************************************************************************
	> File Name: nizhi.c
	> Author: 
	> Mail: 
	> Created Time: 日 10/22 11:28:35 2017
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define size 50

/*记录每一个非零元素的位置*/
typedef struct 
{
    int row;  //该非零元素的行位置
    int clo;  //该非零元素的列位置
    int values; //该非零元素的数字值
}T;

/*记录每一个举证的行列总数，以及每一个非零元素的总体*/
typedef struct 
{
    int rows,clos,num;//矩阵的行列数字，以及非零元素的个数
    T data[size];
}TS;

/*稀疏矩阵的输入以及三元表的提取*/
TS create(TS M)
{
    int i = 0;
    int j = 0;
    int k = 0;
    int a = 1;
    int st[size][size]={0};
    M.num = 0;
    printf("请输入稀疏矩阵元素:\n");
    for(i=0; i<M.rows; i++)
    {
        for(j=0; j<M.clos; j++)
        {
            scanf("%d",&k);
            st[i][j] = k;
            if(k!=0)
            {
                M.data[a].row = i;
                M.data[a].clo = j;
                M.data[a].values = k;
                M.num++;
                a++;
            }
        }
    }
    printf("原矩阵输出:\n");
    for(int i=0; i<M.rows;i++)
    {
        for(int j=0;j<M.clos;j++)
        {
            printf("%d\t",st[i][j]);
        }
        printf("\n");
    }
    return M;
}

/*快速定位转置法*/
TS Fast_transpose(TS M,TS T)
{
    int i = 0;
    int j = 0;
    int p,newp;
    int number[size]={0};
    int postion[size]={0};
    T.rows = M.clos;
    T.clos = M.rows;
    T.num = M.num;
    if(T.num)
    {
        for(i=1; i<M.clos; i++)
        {
            number[i] = 0;
        }
        for(int t=1; t<M.num; t++)
        {
            number[M.data[t].clo]++;
        }
        postion[1] = 1;
        for(p=2;p<M.clos;p++)
        {
            postion[p] = postion[p-1]+number[p-1];
        }
        for(p=1; p<=M.num; p++)
        {
            j = M.data[p].clo;
            newp = postion[j];
            T.data[newp].row = M.data[p].clo;
            T.data[newp].clo = M.data[p].row;
            T.data[newp].values = M.data[p].values;
            printf("newpr:%d\tnewpc:%d\tvalues:%d\n",T.data[newp].row,T.data[newp].clo,T.data[newp].values);
            postion[j]++;
        }
    }
    return T;
}

int main()
{
    TS T,M;
    int k = 0;
    printf("请输入行和列:\n");
    scanf("%d %d",&M.rows,&M.clos);
    M = create(M);
    T = Fast_transpose(M,T);
    printf("逆置后的矩阵为：\n");
    for(int i=0; i<M.clos; i++)
    {
        for(int j=0; j<M.rows; j++)
        {
            if(T.data[k].row == i&&T.data[k].clo==j)
            {
                printf("%d\t",T.data[k].values);
                k++;
            }
            else
            {
                printf("0\t");
            }
        }
        printf("\n");
    }
    return 0;
}





