#include "stdafx.h"
#include "ROV_DataParse.h"
#include "BaseFunc.h"

//处理ROV发回来的原始数据，存入结构体***********************************************
bool ROV_Recv_procrec(ListQueue *listqueue,unsigned char *datapackage)
{
	bool  Receive_Success_flag=false;
	unsigned short crc_tmp;
	int State = ROV_FIND_HEADER;
	int count;
	unsigned char * p;
	unsigned char Temp_Buffer[200];
	//STAT_ROVtoRC_Last = STAT_ROVtoRC;

	while ((listqueue->GetLength()>0 && (State != ROV_FIND_HEADER)) || ((listqueue->GetLength()>=DATA_TOTAL_LEN) && (State == ROV_FIND_HEADER)))
	{
		switch (State)
		{
		case ROV_FIND_HEADER:     //寻找包头
			while (listqueue->GetLength()>=DATA_TOTAL_LEN)
			{
				for (count = 0; count < DATA_HEAD_LEN; count ++)//查包头
				{
					if (listqueue->peekQueue (count) != RCBOX_start[count])
					{
						break;
					}
				}
				if (count==DATA_HEAD_LEN)//查包头成功
				{
					State=ROV_FIND_TAIL;  //8个字节完全相符
					break;
				}
				else
				{
					listqueue->outQueue ();// 如果包头匹配不成功，需要弹出错误数据
				}
			}
			break;

		case ROV_FIND_TAIL:     //判断包尾  //寻找包头时已经确保数据长度合适，这里不做判断

			for (count = 0; count < DATA_TAIL_LEN; count ++)//查包头
			{
				if (listqueue->peekQueue (DATA_TOTAL_LEN-DATA_TAIL_LEN+count) != RCBOX_end[count])
				{
					break;
				}
			}
			if (count == DATA_TAIL_LEN)
				State = ROV_CHECK_CRC;   //8个字节完全相符
			else
			{
				State = ROV_FIND_HEADER;
				for (int temp = 0; temp < DATA_HEAD_LEN; temp++)
				{
					listqueue->outQueue ();//如果包尾的开始不相符，则需要向后搓一个继续查找
				}
			}
			break;

		case ROV_CHECK_CRC:     //验证crc，如果正常执行can发送，否则丢弃

			for(count=0;count<DATA_TOTAL_LEN;count++)
			{
				Temp_Buffer[count]= listqueue->peekQueue(count);
			}
			crc_tmp = Crc16_Check(Temp_Buffer + 8, DATA_TOTAL_LEN - 18);


			if(crc_tmp == (listqueue->peekQueue(DATA_TOTAL_LEN-10)+256*listqueue->peekQueue(DATA_TOTAL_LEN-9)))
			{//crc正确，返回整个数据包

				for (int tmp = 0; tmp <DATA_TOTAL_LEN; tmp++)
				{
					datapackage[tmp]= listqueue->outQueue();//跳过这个包
				}
				Receive_Success_flag = true;
			}
			else
			{
				for (int tmp = 0; tmp <DATA_TOTAL_LEN; tmp++)
				{
					listqueue->outQueue();//跳过这个包
				}
			}         
			State = ROV_FIND_HEADER;
			break;

		default:
			State = ROV_FIND_HEADER; //跳转到寻找包头的模式
			break;
		}
	}
	return Receive_Success_flag;

}
