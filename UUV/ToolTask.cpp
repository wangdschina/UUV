#include "stdafx.h"
#include "ToolTask.h"
#include "ROVSharkMax.h"

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/time.h"
};


CToolTask::CToolTask( const std::string& name ) : 
	Task(name)
{

}


CToolTask::~CToolTask(void)
{
}

int64_t CParseTask::m_dwLastFrameRealTime = av_gettime();
CParseTask::CParseTask() : 
	CToolTask("Parse")
{
	m_bD3dInited = false;
}

CParseTask::~CParseTask()
{

}

unsigned char pszData[1920*1080*3/2] = { 0x00 };
void CParseTask::runTask()
{
	av_register_all();
	avformat_network_init();
	AVFormatContext	*pFormatCtx = avformat_alloc_context();
	pFormatCtx->interrupt_callback.callback = AVInterruptCallBackFun;	// 中断回调
	pFormatCtx->interrupt_callback.opaque = this;

	AVDictionary *options = NULL;  
	//av_dict_set(&options, "buffer", "655360", 0);
	//av_dict_set(&options, "probesize", "409600", 0);
	//av_dict_set(&options, "max_delay", "100000", 0);
	//av_dict_set(&options, "bufsize", "655360", 0);
	//av_dict_set(&options, "max_streams", "1000000", 0);
	if (g_pRovSharkMax->m_unCount <= 1)
	{
		av_dict_set(&options, "stimeout", "3000000", 0);  //设置超时断开连接时间 
	}
	
	av_dict_set(&options, "rtsp_transport", "tcp", 0);
	m_dwLastFrameRealTime = av_gettime();
	if(avformat_open_input(&pFormatCtx, "rtsp://192.168.99.51/1", NULL, &options) != 0)
	{
		avformat_close_input(&pFormatCtx);
		av_dict_free(&options);
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("打开输入流失败"));
		return;
	}
	av_dict_free(&options);
	if(avformat_find_stream_info(pFormatCtx, NULL) < 0)
	{
		avformat_close_input(&pFormatCtx);
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("查询流信息失败"));
		return;
	}

	int videoindex = -1;

	for(int i = 0; i < pFormatCtx->nb_streams; ++i) 
	{
		if(pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
		{
			videoindex = i;
			break;
		}
	}
	if(videoindex == -1)
	{
		avformat_close_input(&pFormatCtx);
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("未找到视频流信息"));
		return;
	}
	AVCodecContext* pCodecCtx = pFormatCtx->streams[videoindex]->codec;
	AVCodec* pCodec = avcodec_find_decoder(pCodecCtx->codec_id);
	if(pCodec == NULL)
	{
		avcodec_close(pCodecCtx);
		avformat_close_input(&pFormatCtx);
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("查询解码器失败"));
		return;
	}
	if(avcodec_open2(pCodecCtx, pCodec, NULL) < 0)
	{
		avcodec_close(pCodecCtx);
		avformat_close_input(&pFormatCtx);
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("打开解码器失败"));
		return;
	}
	
	if(!(m_bD3dInited = CROVSharkMax::m_dxUtility.InitDirect3D(CROVSharkMax::m_hWnd, pCodecCtx->width, pCodecCtx->height)))
	{
		LogMsg(WT_EVENTLOG_WARNING_TYPE, _T("初始化渲染界面失败"));
		//return;
	}

	AVFrame* pFrame = av_frame_alloc();
	AVFrame* pFrameYUV = av_frame_alloc();
	uint8_t* out_buffer = (uint8_t*)av_malloc(avpicture_get_size(PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height));
	avpicture_fill((AVPicture*)pFrameYUV, out_buffer, PIX_FMT_YUV420P, pCodecCtx->width, pCodecCtx->height);

	struct SwsContext* img_convert_ctx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt, 
		pCodecCtx->width, pCodecCtx->height, PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL); 

	AVPacket* packet = (AVPacket*)av_malloc(sizeof(AVPacket));
	/* 解码 h264 流文件 */
	while (!isCancelled())
	{
		if(av_read_frame(pFormatCtx, packet) >= 0)
		{
			m_dwLastFrameRealTime = av_gettime();
			if(packet->stream_index == videoindex)
			{
				int ret, got_picture;
				ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture, packet);
				if(ret < 0)
				{
					LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("解码错误"));
					break;
				}
				if(got_picture)
				{
					sws_scale(img_convert_ctx, (const uint8_t* const*)pFrame->data, pFrame->linesize, 0, pCodecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
					pFrameYUV->height = pCodecCtx->height;
					pFrameYUV->width = pCodecCtx->width;
					if (CROVSharkMax::m_pVideoHandler)
					{
						CROVSharkMax::m_pVideoHandler(static_cast<UUV_RESULT>(pFrameYUV));
					}

					if (m_bD3dInited/*::IsWindow(CROVSharkMax::m_hWnd)*/)
					{
						//unsigned char* pszData = new unsigned char[(pCodecCtx->width)*(pCodecCtx->height) + (pCodecCtx->width)*(pCodecCtx->height)/4 + (pCodecCtx->width)*(pCodecCtx->height)/4];
						memcpy(pszData, pFrameYUV->data[0], (pCodecCtx->width)*(pCodecCtx->height));
						memcpy(pszData + (pCodecCtx->width)*(pCodecCtx->height), pFrameYUV->data[1], (pCodecCtx->width)*(pCodecCtx->height)/4);
						memcpy(pszData +(pCodecCtx->width)*(pCodecCtx->height) + (pCodecCtx->width)*(pCodecCtx->height)/4, pFrameYUV->data[2], (pCodecCtx->width)*(pCodecCtx->height)/4);

						CROVSharkMax::m_dxUtility.Render(pszData);
						//delete [] pszData;
						//pszData = nullptr;
					}
				}
			}
			av_free_packet(packet);
		}
	}

	if (!packet)
	{
		av_free_packet(packet);
		packet = nullptr;
	}

	sws_freeContext(img_convert_ctx);

	//--------------
	av_free(out_buffer);
	av_frame_free(&pFrameYUV);
	av_frame_free(&pFrame);
	avcodec_close(pCodecCtx);
	avformat_close_input(&pFormatCtx);

	CROVSharkMax::m_dxUtility.CleanUp();
}

int CParseTask::AVInterruptCallBackFun( void* ctx )
{
	CParseTask* pThis = static_cast<CParseTask*>(ctx);
	if (!pThis)
	{
		return 1;
	}

	if ((av_gettime() - pThis->m_dwLastFrameRealTime) > 5*1000*1000)
	{
		pThis->m_dwLastFrameRealTime = av_gettime();
		g_pRovSharkMax->VideoStream_Open();

		return 1;	//exit
	}

	return 0;	//continue
}