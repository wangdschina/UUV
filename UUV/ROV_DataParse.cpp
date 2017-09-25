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
			crc_tmp = Tcp_Crc16_Check(Temp_Buffer + 8, DATA_TOTAL_LEN - 18);


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


static UUV_F32 ByteToFloat(UUV_U8* byteArray)  
{  
    return *((float*)byteArray);  
}  

static UUV_F64 ByteToDouble(UUV_U8* byteArray)  
{  
    return *((double*)byteArray);  
}  


/** 
*  @brief       处理USBL返回的数据 
*  @param[in]   pResult    
*  @return      无
*  @remarks		该回调只用来做显示      
*  @see          
*/  
bool USBL_Recv_procrec(UUV_U8 *pdata,int datalen)
{
	bool ret = false;
	//判断数据的长度 //判断数据的包头包尾
	UUV_U16 temp_len = *(UUV_U16*)(pdata+2);
	UUV_U16 head = *(UUV_U16*)pdata;
	UUV_U8 tail = *(pdata+datalen-1);
	if((temp_len==datalen)&&(head==0xAAAA)&&(tail==0x0A))
	{
		//判断数据的校验和
		UUV_U16 crc= *(UUV_U16*)(pdata+datalen-3);
		UUV_U16 calc_crc= Udp_CalcCRC16(0, 5, datalen -8, pdata);
		if(crc==calc_crc)
		{
			 ret = true;
		}
	}
	return ret;

	//解析出目标数据
}