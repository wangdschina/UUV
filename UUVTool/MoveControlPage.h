#pragma once

class CMoveControlPage : public CNotifyPump
{
public:
	CMoveControlPage();
	~CMoveControlPage();

public:
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);
	void InitWindow();
	void InitUUV(IUUVObject* pUUV);

protected:
	DUI_DECLARE_MESSAGE_MAP()
	void OnClick(TNotifyUI& msg);
	void OnValueChanged(TNotifyUI& msg);
	void OnSelectChanged(TNotifyUI& msg);
	void OnTextChanged(TNotifyUI& msg);
	void OnReturn(TNotifyUI& msg);

private:
	void ClickSpeedBtn();		//	前进/后退
	void ClickSpeedRestBtn();	//	前进/后退复位
	void ClickDeepBtn();		//	深度
	void ClickDeepRestBtn();	//	深度复位
	void ClickPitchBtn();		//	俯/仰角度
	void ClickPitchRestBtn();	//	俯/仰角度复位
	void ClickRollBtn();		//	横滚角度
	void ClickRollRestBtn();	//	横滚角度复位
	void ClickHeadBtn();		//	航向角度	
	void ClickHeadRestBtn();	//	航向角度复位
	void ClickCtrlModeBtn();	//	控制模式
	void ClickNaviModeBtn();	//	导航模式
	void ClickMoveModeBtn();	//	运动模式

private:
	IUUVObject*			m_pUUV;

private:
	CPaintManagerUI*		m_pPaintManager;
	CHorizontalLayoutUI*	m_pMoveControlPanel;

	/*	前进/后退	*/
	CSliderUI*				m_pSpeedSlider;
	CButtonUI*				m_pSpeedBtn;
	CButtonUI*				m_pSpeedRestBtn;
	CEditUI*				m_pSpeedEdit;

	/*	深度	*/
	CSliderUI*				m_pDeepSlider;
	CButtonUI*				m_pDeepBtn;
	CButtonUI*				m_pDeepRestBtn;
	CEditUI*				m_pDeepEdit;

	/*	俯/仰角度	*/
	CSliderUI*				m_pPitchAngleSlider;
	CButtonUI*				m_pPitchAngleBtn;
	CButtonUI*				m_pPitchAngleRestBtn;
	CEditUI*				m_pPitchAngleEdit;

	/*	横滚角度	*/
	CSliderUI*				m_pRollAngleSlider;
	CButtonUI*				m_pRollAngleBtn;
	CButtonUI*				m_pRollAngleRestBtn;
	CEditUI*				m_pRollAngleEdit;

	/*	航向角度	*/
	CSliderUI*				m_pHeadAngleSlider;
	CButtonUI*				m_pHeadAngleBtn;
	CButtonUI*				m_pHeadAngleRestBtn;
	CEditUI*				m_pHeadAngleEdit;

	/*	控制模式	*/
	COptionUI*				m_pDiffControlOption;
	COptionUI*				m_pGesControlOption;
	CButtonUI*				m_pControlModeBtn;

	/*	导航模式	*/
	COptionUI*				m_pIneNaviOption;
	COptionUI*				m_pGeoNaviOption;
	CButtonUI*				m_pNaviModeBtn;

	/*	运动模式	*/
	COptionUI*				m_pMoveModeStopOption;
	COptionUI*				m_pMoveModeDeepOption;
	COptionUI*				m_pMoveModeGestOption;
	CButtonUI*				m_pMoveModeBtn;
};

