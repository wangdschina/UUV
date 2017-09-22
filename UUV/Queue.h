#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
 using namespace std;
typedef unsigned char elemType;
struct  sNode{
    elemType data;            /* 值域 */
    struct sNode *next;        /* 链接指针 */
  //  elemType lenth;   //长度
};
struct queueLK{
    struct sNode *front;    /* 队首指针 */
    struct sNode *rear;        /* 队尾指针 */
	int NodeNum;
};

class ListQueue
{
private :
	 queueLK Q;  //定义一个队列Q  
	 queueLK *hq;  //定义一个队列Q  
public :
	ListQueue();
	void InitQueue();
	void viewAllQueue();
	 void initQueue();
	 void enQueue( elemType x);
	 elemType outQueue();
	 elemType peekQueue(int index);
	 int emptyQueue();
	 void clearQueue();
	 void viewData(int x);
	int GetLength();

};