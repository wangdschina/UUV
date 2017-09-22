#pragma once
#include "Queue.h"

const unsigned char RCBOX_start[8]=
    {
    'S','T','R','C',0x01,0x00,0x00,0x00
    };  //数据包起始标志
const unsigned char RCBOX_end[8]=
    {
    'E','D','R','C',0x01,0x00,0x00,0x00
    };  //数据包结束标志
const unsigned char DISP_start[8]=
    {
    'S','T','R','C',0x01,0x00,0x00,0x00
    };  //数据包起始标志
const unsigned char DISP_end[8]=
    {
    'E','D','R','C',0x01,0x00,0x00,0x00
    };  //数据包结束标志

enum PARSE_NODE
{
   ROV_FIND_HEADER=0,
   ROV_FIND_TAIL,
   ROV_CHECK_CRC,

};

const unsigned char DATA_TOTAL_LEN=114;
const unsigned char DATA_HEAD_LEN=8;
const unsigned char DATA_TAIL_LEN=8;
//处理ROV发回来的原始数据，存入结构体***********************************************
extern bool ROV_Recv_procrec(ListQueue *listqueue,unsigned char *datapackage);