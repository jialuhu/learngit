/*************************************************************************
	> File Name: Huffman.cpp
	> Author: 
	> Mail: 
	> Created Time: 六 11/18 15:01:22 2017
 ************************************************************************/

#include<iostream>
#include<algorithm>
#include<iomanip>

#define MAXSIZE 30
using namespace std;

/*哈夫曼编码的存储方式*/
typedef struct Node 
{
    char ch;
    int weight;
    int parent,Lchirld,Rchirld;
}Huff;

void prinhuffman(Huff *HF,int m);
Huff *huffman(Huff *HF, int n, int m);
Huff *select(Huff *HF, int i, int *n, int *m);
int select_min(Huff *HF,int i);

/*创建哈夫曼树*/
Huff *cretahuffman(int n) //传入叶子节点的个数
{
    int i = 0;
    int m = 2*n-1;//计算总节点个数
    Huff *HF;
    HF = (Huff *)malloc(n*sizeof(Huff));
    /*初始化哈夫曼树的叶子节点*/
    for(i=0; i<n; i++)
    {
        cout << "please input the weight:" << endl;
        cin >> HF[i].weight;
        cout << "please intput the alphabet:" << endl;
        cin >> HF[i].ch;
        HF[i].parent = -1;
        HF[i].Lchirld = -1;
        HF[i].Rchirld = -1;
    }
    for(int j = i; j<m; j++)
    {
        HF[j].ch = '-';
        HF[j].parent = -1;
        HF[j].Lchirld = -1;
        HF[j].Rchirld = -1;
        HF[j].weight = -1;
    }
    free(HF);
    return HF;
}

/*输出哈夫曼树*/
void prinhuffman(Huff *HF,int m)
{
   cout <<setw(10)<<"alphabet" << setw(10) <<"weight" << setw(10) << "parent" << setw(10) << "Lchirld"<<setw(10) << "Rchirld" << endl; 
    for(int i=0; i<m; i++)
    {
        cout << setw(10) << HF[i].ch << setw(10) << HF[i].weight << setw(10) << HF[i].parent << setw(10) << HF[i].Lchirld << setw(10) << HF[i].Rchirld << endl;
    }
    
}

/*哈夫曼树的建立*/
Huff *huffman(Huff *HF, int n, int m)
{
    int min1 = 0,min2 = 0;
    int j = 0;
    for(j=n;j<m; j++)
    {
        HF = select(HF, j, &min1, &min2);//在第i个元素之前找出两个最小的传入min1,min2；
        HF[j].weight = HF[min1].weight+HF[min2].weight; //将新的权值填入
        HF[j].Lchirld = min1;//新的根节点记录左孩子的下标
        HF[j].Rchirld = min2;//新的根节点记录右孩子的下标
        HF[min1].parent = j;//原来叶子节点记录下自己的双亲节点
        HF[min2].parent = j;//原来的叶子节点记录下自己的双亲节点
    }
    return HF;
}

/*每次从中找出最小值*/
int select_min(Huff *HF,int i)
{
    int min_weight=0;  //叶子节点当中，权值最小的下标记录
    int weight = 0; //叶子节点当中，权值数值最小的数
    int j = 0;
    while(HF[j].parent != -1)
    {
        j++;
    }
    weight = HF[j].weight;
    min_weight = j;
    for(j=j+1; j<i; j++)
    {
        if(HF[j].parent != -1)
        {
            continue;
        }
        else
        {
           if(HF[j].weight < weight)
            {
                min_weight = j;
                weight = HF[j].weight;
            }
        }
    }
    HF[min_weight].parent = -2;
    return min_weight;  
}

Huff *select(Huff *HF, int i, int *n, int *m)
{
    *n = select_min(HF,i);
    *m = select_min(HF,i);
    return HF;
}

string Crthuffmancode(Huff *HF, int n)
{
    string st;
    int p = 0;
    for(int i=0; i<n; i++)
    {
        p = HF[i].parent; //取出叶子节点的双亲节点
        int c = i;//记住叶子节点的下标
        while(p!=-1)
        {
            if(HF[p].Lchirld == c) /*看双亲节点的左右孩子是不是下标c*/
            {
                st += "0";
            }
            if(HF[p].Rchirld == c)
            {
                st += "1";
            }
            /*c记住该节点的下标*/
            c = p;
            /*继续找该节点的双亲节点*/
            p = HF[p].parent;
        }
        reverse(st.begin(),st.end());
        cout << "字符为:"<< HF[i].ch << "\t" << "编码为:" << st << endl;
        st = "";

    }
    return st;
}


int main()
{
    /*测试哈夫曼树*/
    int n,m;
    Huff *HF;
    cout << "please intput the n:" << endl;
    cin >> n;
    m = 2*n-1;
    HF = cretahuffman(n);
    HF = huffman(HF,n,m);
    cout << "输出建立好的哈夫曼树:\n\n";
    prinhuffman(HF,m);
    cout << endl;
    Crthuffmancode(HF,n);
    return 0;
}
