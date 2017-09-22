#include "stdafx.h"
#include "Queue.h"

ListQueue::ListQueue()
{
	hq=&Q;
	this->InitQueue();
}

/*显示队列中的所有的元素*/
void ListQueue::viewAllQueue()
{
	struct sNode *newP;
	//清空结构
	newP = (sNode *)malloc(sizeof(struct sNode));
	if(newP == NULL)
	{
		printf("内存空间分配失败！ ");
		exit(1);
	}
	//将首地址付给临时结构
	newP = hq->front;    
	//如果临时结构没有指向最后
	while(newP != NULL)
	{
		//打印出数据
		printf(" %d\r\n",newP->data);
		//将临时结构的指针指向下一个节点地址
		newP = newP->next;
	}
	free(newP);
	return;
}

/* 初始化链队 */
void ListQueue::InitQueue()
{
	hq->front = hq->rear = NULL;        /* 把队首和队尾指针置空 */
	hq->NodeNum =0;
	return;
}

/* 向链队中插入一个元素x 在最后插入元素*/
void ListQueue::enQueue( elemType x)
{
	/* 得到一个由newP指针所指向的新结点 */
	struct sNode *newP;
	newP = (sNode *)malloc(sizeof(struct sNode));
	if(newP == NULL){
		printf("内存空间分配失败！ ");
		exit(1);
	}
	/* 把x的值赋给新结点的值域，把新结点的指针域置空 */
	newP->data = x;
	newP->next = NULL;
	/* 若链队为空，则新结点即是队首结点又是队尾结点 */
	if(hq->rear == NULL)//判空用的尾指针
	{
		hq->front = hq->rear = newP;
		hq->NodeNum = 1;
		//printf("%d",hq->rear->lenth);
	}
	else
	{    /* 若链队非空，则依次修改队尾结点的指针域和队尾指针，使之指向新的队尾结点 */

		hq->rear = hq->rear->next = newP;        /* 注意赋值顺序哦 */
		hq->NodeNum ++;
	}
	//free(newP);
	return;
}

/* 从队列中删除一个元素 从最前面删除*/
elemType ListQueue::outQueue()
{
	struct sNode *p;
	elemType temp;
	/* 若链队为空则停止运行 */
	if(hq->front == NULL){
		printf("队列为空，无法删除！ ");
		exit(1);
	}
	temp = hq->front->data;        /* 暂存队尾元素以便返回 */
	p = hq->front;                /* 暂存队尾指针以便回收队尾结点 */
	hq->front = p->next;        /* 使队首指针指向下一个结点 */
	hq->NodeNum--;//出一个元素 ，总数减一
	/* 若删除后链队为空，则需同时使队尾指针为空 */
	if(hq->front == NULL){
		hq->rear = NULL;
		hq->NodeNum =0;
	}
	free(p);        /* 回收原队首结点 */
	return temp;    /* 返回被删除的队首元素值 */
}

int ListQueue::GetLength()
{
	return hq->NodeNum;
}
///* 读取队首元素 */
//int ListQueue::peekQueue()
//{
//    /* 若链队为空则停止运行 */
//    if(hq->front == NULL){
//        printf("队列为空，无法删除！ ");
//        exit(1);
//    }
//    return hq->front->data;        /* 返回队首元素 */
//}

/* 检查链队是否为空，若为空则返回1, 否则返回0 */
int ListQueue::emptyQueue()
{
	/* 判断队首或队尾任一个指针是否为空即可 */
	if(hq->front == NULL){
		return 1;
	}else{
		return 0;
	}
}

/* 清除链队中的所有元素 */
void ListQueue::clearQueue()
{
	struct sNode *p = hq->front;        /* 队首指针赋给p */
	/* 依次删除队列中的每一个结点，最后使队首指针为空 */
	while(p != NULL){
		hq->front = hq->front->next;
		free(p);
		p = hq->front;
	}    /* 循环结束后队首指针已经为空 */
	hq->rear = NULL;        /* 置队尾指针为空 */
	free(p);
	return;

}

elemType ListQueue::peekQueue(int index)
{
	//计数器
	int count;
	int get_lenth;
	get_lenth = 0;
	count = 0;
	elemType temp;
	struct sNode *newP;
	get_lenth = hq->NodeNum ;
	//清空结构
	/*  newP = (sNode *)malloc(sizeof(struct sNode));
	if(newP == NULL)
	{
	printf("内存空间分配失败！ ");
	exit(1);
	}*/
	//将首地址付给临时结构
	newP = hq->front;    
	if (index>get_lenth || index<0)
	{
		printf("error input data\n");
		return 0;
	}
	//如果临时结构没有指向最后
	while(newP != NULL)
	{
		if (count ==index)
		{
			//打印出数据
			temp=newP->data;
		}
		//将临时结构的指针指向下一个节点地址
		newP = newP->next;
		count++;
	}
	/*free(newP);*/
	return temp;
}
