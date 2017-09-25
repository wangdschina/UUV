#pragma once

#include "MoveControlPage.h"
#include "ImageControlPage.h"
#include "PowerControlPage.h"
#include "MotoControlPage.h"
#include "SysControlPage.h"
#include "DataDisplayPage.h"
#include "ExtDataDisplayPage.h"

#define WM_LOGOUTPUT		(WM_USER+1001)

struct LOG_ITEM_DATA
{
	WT_EVENTLOG_TYPE emType;
	SYSTEMTIME stTime;
	tstring strMsg;
};

class CMainWndDlg : public WindowImplBase
{
public:
	CMainWndDlg(void);
	~CMainWndDlg(void);

public:
	LPCTSTR		GetWindowClassName() const;
	CDuiString	GetSkinFile();
	CDuiString	GetSkinFolder();
	void		OnFinalMessage(HWND hWnd);
	LRESULT		OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void		InitWindow();
	CControlUI* CreateControl(LPCTSTR pstrClassName);
	LRESULT		HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void		Notify(TNotifyUI& msg);

public:
	static void CALLBACK LogMsgShow(WT_EVENTLOG_TYPE emType, SYSTEMTIME stTime, LPCTSTR lpszMsg);

protected:
	LRESULT OnLogOutput(WPARAM wParam, LPARAM lParam);

public:
	static void CALLBACK UUVResultShow(UUV_RESULT pResult);
	static void CALLBACK UUVUSBLDataCallBack(UUV_RESULT pResult);
	static void CALLBACK UUVVideoFrame(UUV_RESULT pResult);

	static void CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);


protected:
	DUI_DECLARE_MESSAGE_MAP()
	void OnWindowInit(TNotifyUI& msg);
	void OnClick(TNotifyUI& msg);

private:
	void InitConfig();
	void InitMediaWnd();
	void InitUUV();

private:
	/*	操作栏	*/
	void ClickNetOpenBtn();
	void ClickNetCloseBtn();
	void ClickNetStateBtn();

	/*	视频流操作	*/
	void ClickVideoSnopBtn();
	void ClickVideoStreamFDOpenBtn();
	void ClickVideoStreamFDColseBtn();

private:
	void ProcessVideoFrame(UUV_RESULT pResult);

private:
	CWndUI*			m_pMediaWnd;
	IUUVObject*		m_pUUV;
	bool			m_bOpenFD;
	bool			m_bOpenSnop;

private:
	CMoveControlPage	m_moveControlPage;
	CImageControlPage	m_iamgeControlPage;
	CPowerControlPage	m_powerControlPage;
	CMotoControlPage	m_motoControlPage;
	CSysControlPage		m_sysControlPage;
	CDataDisplayPage	m_dataDisplayPage;
	CExtDataDisplayPage m_extDataDisplayPage;

private:
	/*	标题栏	*/
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;

	/*	网络操作栏	*/
	CButtonUI*	m_pNetOpenBtn;
	CButtonUI*	m_pNetCloseBtn;
	CButtonUI*	m_pNetStateBtn;

	/*	播放区域	*/
	CControlUI* m_pMediaCtrl;
	
	/*	视频栏	*/
	CButtonUI*	m_pVideoSnopBtn;
	CButtonUI*	m_pVideoOpenFaceDetectBtn;
	CButtonUI*	m_pVideoCloseFaceDetectBtn;

	/*	日志栏	*/
	CRichEditUI*	m_pLogRichEdit;

	/*	状态栏	*/
	CLabelUI*		m_pNetStateLabel;

private:
	UINT_PTR		m_timerNetState;
};

extern CMainWndDlg* g_pMainWndDlg;

