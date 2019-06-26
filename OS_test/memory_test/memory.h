/*************************************************************************
	> File Name: memory.h
	> Author: 
	> Mail: 
	> Created Time: 三  6/26 20:14:17 2019
 ************************************************************************/

#ifndef _MEMORY_H
#define _MEMORY_H

#define PROCESS_NAME_LEN 32 //进程名称的长度
#define MIN_SLICE 10 //最小的碎片
#define DEFAULT_MEM_SIZE 1024 //默认的内存空间大小
#define DEFAULT_MEM_START 0 //默认地址起始位置

/*内存分配方法*/
#define MA_FF 0
#define MA_BF 1
#define MA_WF 3

/*描述每一个空闲块的数据结构*/
typedef struct free_block_type{
    int size;//该空闲块的大小
    int start_addr;//该空闲块的起始地址
    struct free_block_type *next;
}FBT;

/*描述每个进程被分到的内存块的数据结构*/
typedef struct allocated_block{
    int pid;//模拟进程号
    int size;//该进程所需要的空间
    int start_addr;//该进程所在的起始地址
    char process_name[PROCESS_NAME_LEN];//进程的名称
    struct allocated_block *next;
}AB;



#endif
