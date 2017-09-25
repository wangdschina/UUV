#pragma once

class CSysControlPage : public CNotifyPump
{
public:
	CSysControlPage();
	~CSysControlPage();

public:
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);
	void InitWindow();
	void InitUUV(IUUVObject* pUUV);

protected:
	DUI_DECLARE_MESSAGE_MAP()
	void OnClick(TNotifyUI& msg);
	void OnValueChanged(TNotifyUI& msg);
	void OnReturn(TNotifyUI& msg);

private:
	void ClickSoftRestartBtn();			//	软重启
	void ClickManipControlBtn();		//	机械手设置
	void ClickManipStopBtn();			//	机械手停止
	void ClickUsblNetOpenBtn();			//	USBL打开连接
	void ClickUsblNetCloseBtn();		//	USBL关闭连接

private:
	IUUVObject*				m_pUUV;

private:
	CPaintManagerUI*		m_pPaintManager;
	CHorizontalLayoutUI*	m_pSysControlPanel;

	/*	机械手控制	*/
	CSliderUI*				m_pManipOpenSlider;
	CButtonUI*				m_pManipulatorControlBtn;
	CButtonUI*				m_pManipulatorStopBtn;
	CEditUI*				m_pManipOpenEdit;

	/*	USBL操作	*/
	CButtonUI*				m_pUsblNetOpenBtn;
	CButtonUI*				m_pUsblNetCloseBtn;

	/*	软重启	*/
	CButtonUI*				m_pSoftRestartBtn;
};

