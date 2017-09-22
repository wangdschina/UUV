#pragma once

class CPowerControlPage : public CNotifyPump
{
public:
	CPowerControlPage();
	~CPowerControlPage();

public:
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);
	void InitWindow();
	void InitUUV(IUUVObject* pUUV);

protected:
	DUI_DECLARE_MESSAGE_MAP()
	void OnClick(TNotifyUI& msg);

private:
	void ClickPowerOneBtn();			//	板载供电控制一
	void ClickPowerTwoBtn();			//	板载供电控制二
	void ClickPowerConsumModeBtn();		//	俯/仰角度

private:
	IUUVObject*			m_pUUV;

private:
	CPaintManagerUI*		m_pPaintManager;
	CHorizontalLayoutUI*	m_pPowerControlPanel;

	/*	板载供电控制一	*/
	COptionUI*				m_pCameraPowerOption;
	COptionUI*				m_pPOEPowerOption;
	CButtonUI*				m_pPowerOneBtn;

	/*	板载供电控制二	*/
	COptionUI*				m_pPeripPowerOption;
	COptionUI*				m_pOtherPowerOption;
	CButtonUI*				m_pPowerTwoBtn;

	/*	功耗模式	*/
	COptionUI*				m_pLowConsumOption;
	COptionUI*				m_pHighConsumOption;
	CButtonUI*				m_pPowerConsumModeBtn;
};

