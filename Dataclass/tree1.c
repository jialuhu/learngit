/*************************************************************************
	> File Name: tree1.c
	> Author: 
	> Mail: 
	> Created Time: 四 11/ 9 13:46:59 2017
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

#define Size 100
#define False 0
#define Ture 1

/*树的存储结构*/
typedef struct Tree 
{
    char data;
    struct Tree *Lift;
    struct Tree *Right;
}Tree,*Btree;

/*栈的建立*/
typedef struct stack
{
    int top;
    Btree data[Size];
}sepstack;

/*栈的初始化*/
sepstack *init(sepstack *stack)
{
    stack = malloc(sizeof(sepstack));
    stack -> top = -1;
    return stack;
}

/*判断栈空*/
int empty(sepstack *stack)
{
    if(stack->top == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

/*入栈操作*/
int push(sepstack *stack,Btree x)
{
    if(stack->top == (Size-1))
    {
        return 0;
    }
    else{
        stack->top++;
        stack->data[stack->top]=x;
        return 1;
    }
}

/*取出栈顶元素*/
void gettop(sepstack *stack,Btree *a)
{
//    Btree a;
    if(!empty(stack))
    {
        *a = stack->data[stack->top];
 //       return a;
    }
 //   else
   // {
   //     return 0;
   // }
}

/*弹出栈顶元素*/
void pop(sepstack *stack,Btree *a)
{
 //   Btree a;
    if(!empty(stack))
    {
        *a = stack->data[stack->top];
        stack->top--;
 //       return a;
    }
   // else{
     //   return 0;
    //}
}

/*一级指针建立二叉树*/
Btree create()
{
    char ch;
    Tree *p;
    ch = getchar();
    if(ch=='#')
    {
        return NULL;
    }
    else{
        p = (Tree *)malloc(sizeof(Tree));
        p->data = ch;
        p->Lift = create();
        p->Right = create();
        return (p);
    }
}

/*二级指针建立二叉树*/
void crea(Btree *root)
{
    char ch;
    ch = getchar();
    printf("%c",ch);
    if(ch=='#')
    {
        (*root) =  NULL;
    }
    else
    {
        *root=(Tree *)malloc(sizeof(Tree));
        (*root)->data = ch;
        if((*root)==NULL)
        {
            exit(0);
        }
        crea((&(*root)->Lift));
        crea((&(*root)->Right));
    }
}


/*先序递归遍历，根左右*/
void digui_front(Btree root)
{
    if(root == NULL)
    {
        return;
    }
    else
    {
        printf("%c\t",root->data);
        digui_front(root->Lift);
        digui_front(root->Right);
    }
}

/*先序递归遍历，左根右*/
void digui_inorder(Btree root)
{
    if(root)
    {
        digui_inorder(root->Lift);
        printf("%c\t",root->data);
        digui_inorder(root->Right);
    }
}

/*后序递归遍历，左右根*/
void digui_postorder(Btree root)
{
    if(root)
    {
        digui_postorder(root->Lift);
        digui_postorder(root->Right);
        printf("%c\t",root->data);
    }
}

/*非递归先序遍历*/
void undigui_front(Btree root)
{
    sepstack *stack;
    Btree p = root;
    stack = init(stack);
    while(p!=NULL || (!empty(stack)))
    {
        while(p!=NULL)
        {
            /*从根节点开始遍历，有就输出该节点，输出之后再入栈*/
            printf("%c\t",p->data);
            push(stack,p);
            p = p->Lift;
        }
        pop(stack,&p);
        p = p->Right;
    }
    printf("\n");
}
/*非递归中序遍历*/
void undigui_inorder(Btree root)
{
    sepstack *stack;
    Btree p = root;
    stack = init(stack);
    while(p!=NULL || (!empty(stack)))
    {
        while(p)
        {
            push(stack,p);
            p = p->Lift;
        }
        /*此时P处于空指针，需要从栈中拿出上一个节点*/
        pop(stack,&p);
        printf("%c\t",p->data);
        p = p->Right;
    }
    printf("\n");
}

void undigui_postorder(Btree root)
{
    sepstack *stack;
    stack = init(stack);
    Btree p = root;
    Btree q = NULL;
    while(p!=NULL || (!empty(stack)))
    {
        while(p)
        {
            push(stack,p);
            p = p->Lift;
        }
        gettop(stack,&p);
        if(p->Right==NULL || p->Right==q)
        {
            pop(stack,&p);
            printf("%c\t",p->data);
            q = p;
            p = NULL;
        }
        else{
            p = p->Right;
        }
    }
    printf("\n");
}
int main()
{
    Btree *p;
    p = (Btree *)malloc(sizeof(Tree));
    crea(p);
    printf("\n先序遍历:\n");
    undigui_front(*p);
    digui_front(*p);
    printf("\n中序遍历:\n");
    undigui_inorder(*p);
    digui_inorder(*p);
    printf("\n后序遍历:\n");
    undigui_postorder(*p);
    digui_postorder(*p);
    printf("\n");
    return 0;
}


