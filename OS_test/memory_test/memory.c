/*************************************************************************
	> File Name: memory.c
	> Author: 
	> Mail: 
	> Created Time: 三  6/26 20:24:06 2019
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include"memory.h"

FBT *init_free_block(int mem_size);
void display_menu();
void set_mem_size();
void set_algorithm();
void new_process();
void Kill_process();
void display_mem_usage();
void do_exit();
AB *find_process(int pid);
int free_mem(AB *ab); /*释放ab所表示的分配区*/
int dispose(AB *ab);  /*释放ab数据结构节点*/
void rearrange(int algorithm);
void rearrange_FF();
void rearrange_BF();
void rearrange_WF();
void do_exit();

int flag;
int mem_size;
static int pid = 0;
FBT *free_block;
AB *allocated_block_head = NULL;
int ma_algorithm = MA_FF;
int main()
{
    char choice;
    free_block = init_free_block(mem_size); //初始化空闲区
    for(;;){
        display_menu();    //显示菜单
        fflush(stdin);
        choice=getchar();    //获取用户输入
        switch(choice){
            case '1': set_mem_size(); break;     //设置内存大小
            case '2': set_algorithm();flag=1; break;    //设置分配算法
            case '3': new_process(); flag=1; break;    //创建新进程
            case '4': Kill_process(); flag=1; break;    //删除进程
            case '5': display_mem_usage(); flag=1; break;    //显示内存使用
            case '0': do_exit(); exit(0);        //释放链表并退出
            default: break;
        }
    }
    return 0;
}
void do_exit()
{
    return;
}
FBT *init_free_block(int mem_size)
{
    struct free_block_type *fb;
    fb=(struct free_block_type *)malloc(sizeof(struct free_block_type));
    if(fb==NULL){
        printf("No mem\n");
        return NULL;
    }
    fb->size = mem_size;
    fb->start_addr = DEFAULT_MEM_START;
    fb->next = NULL;
    return fb;
    
}

void set_mem_size()
{
    int size;
    if(flag!=0){  //防止重复设置
        printf("Cannot set memory size again\n");
    }
    printf("Total memory size =");
    scanf("%d", &size);
    if(size>0) {
        mem_size = size;
        free_block->size = mem_size;
    }
    flag=1;
    
}

void rearrange(int algorithm)
{
    switch(algorithm){
        case MA_FF: rearrange_FF(); break;
        case MA_BF: rearrange_BF(); break;
        case MA_WF: rearrange_WF(); break;
    }
}

void rearrange_FF()
{
    struct free_block_type *tmp, *work;
    printf("Rearrange free blocks for FF \n");
    tmp = free_block;
    while(tmp!=NULL)
    { work = tmp->next;
        while(work!=NULL){
            if( work->start_addr < tmp->start_addr) { /*地址递增*/
                int temp;
                temp = work->start_addr;
                work->start_addr = tmp->start_addr;
                tmp->start_addr = temp;
                temp = work->size;
                work->size = tmp->size;
                tmp->size = temp;
            }
            else            work=work->next;
        }
        tmp=tmp->next;
    }
}
void rearrange_BF(){
    struct free_block_type *tmp, *work;
    printf("Rearrange free blocks for FF \n");
    tmp = free_block;
    while(tmp!=NULL)
    { work = tmp->next;
        while(work!=NULL){
            if( work->size < tmp->size) { /*地址递增*/
                int temp;
                temp = work->start_addr;
                work->start_addr = tmp->start_addr;
                tmp->start_addr = temp;
                temp = work->size;
                work->size = tmp->size;
                tmp->size = temp;
            }
            else            work=work->next;
        }
        tmp=tmp->next;
    }
    //请自行补充
}
void rearrange_WF(){
    struct free_block_type *tmp, *work;
    printf("Rearrange free blocks for FF \n");
    tmp = free_block;
    while(tmp!=NULL)
    { work = tmp->next;
        while(work!=NULL){
            if( work->size > tmp->size) { /*地址递增*/
                int temp;
                temp = work->start_addr;
                work->start_addr = tmp->start_addr;
                tmp->start_addr = temp;
                temp = work->size;
                work->size = tmp->size;
                tmp->size = temp;
            }
            else            work=work->next;
        }
        tmp=tmp->next;
    }
    //请自行补充
}

    
void set_algorithm()
{
    int algorithm;
    printf("\t1 - First Fit\n");
    printf("\t2 - Best Fit \n");
    printf("\t3 - Worst Fit \n");
    scanf("%d", &algorithm);
    if(algorithm>=1 && algorithm <=3) ma_algorithm=algorithm;
    //按指定算法重新排列空闲区链表
    rearrange(ma_algorithm);
}

int allocate_mem(struct allocated_block *ab)
{
    /*1.找到的该块空间足够并且，剩下的空间大于不可分割空间的话，可以就地分割该区域*/
    /*2.找到的该块空间足够，但是剩余的空间小于不可分割空间的话，就将整块空间给出*/
    /*3.找不到某块空间足够，但是空闲空间的和大于所请求的空间,进行空间合并，再分配*/
    /*4.以上条件都不满足，则找不到满足的空间，返回-1*/
    struct free_block_type *fbt, *pre;
    int request_size=ab->size;
    fbt = pre = free_block;
    int sum = 0;
    while(fbt!=NULL)
    {
        /*属于以上情况1和情况2*/
        if(fbt->size>=request_size)
        {
            printf("111111222222\n");
            ab->start_addr = fbt->start_addr;
            /*分配后空闲空间足够大，并且剩余的空间大于最小分割空间,则就该区域分割*/
            if(fbt->size-request_size > MIN_SLICE)
            { 
                fbt->size = fbt->size - ab->size; 
                fbt->start_addr = fbt->start_addr + request_size; 
            }
            /*剩余的空间小于最小可分割空间,则将整块空间给出*/ 
            else {
                if(fbt == free_block)
                {
                    free_block = free_block->next;
                    free(fbt);

                }
                else
                {
                    pre->next = fbt->next;
                    free(fbt);
                }
            }
            return 1;
        }
        /*试探是否属于情况3、情况4*/
        else
        { /*分割后空闲区成为小碎片，一起分配*/ sum = fbt->size + sum;//统计空闲区域是否有可能满足所请求的空间大小
             pre = fbt;
             fbt = fbt->next;
             sum = sum + fbt->size;
        }
        pre = fbt;
        fbt = fbt->next;
    }
    /*属于情况3的范围，可以合并空间后进行分配*/
    if(sum >= request_size)
    {
        printf("情况3\n");
        return -1;        
    }
    else
    {
        /*属于情况4，无法分配合适的空间*/
        return -1;
    }
    return -1;
}

void new_process()
{
    struct allocated_block *ab;
    int size;
    int ret;
    ab=(struct allocated_block *)malloc(sizeof(struct allocated_block));
    if(!ab) exit(0);
    ab->next = NULL;
    pid++;
    sprintf(ab->process_name, "PROCESS-%02d", pid);
    ab->pid = pid;
    
    printf("Memory for %s:", ab->process_name);
    scanf("%d", &size);
    
    if(size>0) ab->size=size;
    
    ret = allocate_mem(ab);  
    /* 从空闲区分配内存，ret==1表示分配ok*/
    /*如果此时allocated_block_head尚未赋值，则赋值*/
    if((ret==1) &&(allocated_block_head == NULL)){
        allocated_block_head=ab;
    }
    /*分配成功，将该已分配块的描述插入已分配链表*/
    else if (ret==1) {
        printf("cheng gong\n");
        ab->next=allocated_block_head;
        allocated_block_head=ab;
    }
    else if(ret==-1){ /*分配不成功*/
        printf("Allocation fail\n");
        free(ab);
    }
}
/*删除进程，归还分配的存储空间，并删除描述该进程内存分配的节点*/
void Kill_process()
{
    struct allocated_block *ab;
    int pid;
    printf("Kill Process, pid=");
    scanf("%d", &pid);
    ab=find_process(pid);
    if(ab!=NULL)
    {
        free_mem(ab); 
        dispose(ab);
    }
    else{
        printf("NULL &&\n");
    }
}

AB *find_process(int pid)
{
    AB *tmp = allocated_block_head;
    while(tmp != NULL)
    {
        if(tmp->pid == pid)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    printf("Conn't find pid\n");
    return NULL;
}

/*将ab所表示的已分配区归还，并进行可能的合并*/
int free_mem(struct allocated_block *ab)
{
    int algorithm = ma_algorithm;
    struct free_block_type *fbt, *pre, *work;
    
    fbt=(struct free_block_type*) malloc(sizeof(struct free_block_type));
    if(!fbt) return -1;
    fbt->size = ab->size;
    fbt->start_addr = ab->start_addr;
    /*插入到空闲区链表的头部并将空闲区按地址递增的次序排列*/
    fbt->next = free_block;
    free_block=fbt;
    rearrange(MA_FF);
    fbt=free_block;
    while(fbt!=NULL)
    {
        work = fbt->next;
        if(work!=NULL)
        {
            /*如果当前空闲区与后面的空闲区相连，则合并*/
            if(fbt->start_addr+fbt->size == work->start_addr)
            {
                fbt->size += work->size;
                fbt->next = work->next;
                free(work);
                continue;
            }
        }
        fbt = fbt->next;
    }
    rearrange(algorithm); /*重新按当前的算法排列空闲区*/
    return 1;
}
/*释放ab数据结构节点*/
int dispose(struct allocated_block *free_ab)
{
    struct allocated_block *pre, *ab;
    
    if(free_ab == allocated_block_head)
    { /*如果要释放第一个节点*/
        allocated_block_head = allocated_block_head->next;
        free(free_ab);
        return 1;
    }
    
    pre = allocated_block_head;
    ab = allocated_block_head->next;
    
    while(ab!=free_ab){ pre = ab;  ab = ab->next; }
    pre->next = ab->next;
    free(ab);
    return 2;
}


void display_menu()
{
    printf("\n");
    printf("1 - Set memory size (default=%d)\n", DEFAULT_MEM_SIZE);
    printf("2 - Select memory allocation algorithm\n");
    printf("3 - New process \n");
    printf("4 - Terminate a process \n");
    printf("5 - Display memory usage \n");
    printf("0 - Exit\n");
}
void display_mem_usage()
{
    struct free_block_type *fbt=free_block;
    struct allocated_block *ab=allocated_block_head;
    if(fbt==NULL) return;
    printf("----------------------------------------------------------\n");
    
    /* 显示空闲区 */
    printf("Free Memory:\n");
    printf("%20s %20s\n", "      start_addr", "       size");
    while(fbt!=NULL)
    {
        printf("%20d %20d\n", fbt->start_addr, fbt->size);
        fbt=fbt->next;
    }
    /* 显示已分配区 */
    printf("\nUsed Memory:\n");
    printf("%10s %20s %10s %10s\n", "PID", "ProcessName", "start_addr", " size");
    while(ab!=NULL){
        printf("%10d %20s %10d %10d\n", ab->pid, ab->process_name, ab->start_addr, ab->size);
        ab=ab->next;
    }
    printf("----------------------------------------------------------\n");
}

