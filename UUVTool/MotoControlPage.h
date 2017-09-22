#pragma once

class CMotoControlPage : public CNotifyPump
{
public:
	CMotoControlPage();
	~CMotoControlPage();

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
	void SetSliderTip(CSliderUI* pSlider);

	void ClickVLeftFrontBtn();		//	垂直左前
	void ClickVLeftFrontRestBtn();	//	垂直左前复位
	void ClickVRightFrontBtn();		//	垂直右前
	void ClickVRightFrontRestBtn();	//	垂直右前复位
	void ClickVLeftBackBtn();		//	垂直左后
	void ClickVLeftBackRestBtn();	//	垂直左后复位
	void ClickVRightBackBtn();		//	垂直右后
	void ClickVRightBackRestBtn();	//	垂直右后复位
	void ClickHLeftBtn();			//	水平左
	void ClickHLeftRestBtn();		//	水平左复位
	void ClickHRightBtn();			//	水平右
	void ClickHRightRestBtn();		//	水平右复位

	//added by houmb
	void Send_Motor_Speed(UUVMOTOR_T motor);
private:
	IUUVObject*				m_pUUV;

private:
	CPaintManagerUI*		m_pPaintManager;
	CHorizontalLayoutUI*	m_pMotoControlPanel;

	/*	垂直左前	*/
	CSliderUI*				m_pVLeftFrontSlider;
	CButtonUI*				m_pVLeftFrontBtn;
	CButtonUI*				m_pVLeftFrontRestBtn;
	CEditUI*				m_pVLeftFrontEdit;

	/*	垂直右前	*/
	CSliderUI*				m_pVRightFrontSlider;
	CButtonUI*				m_pVRightFrontBtn;
	CButtonUI*				m_pVRightFrontRestBtn;
	CEditUI*				m_pVRightFrontEdit;

	/*	垂直左后	*/
	CSliderUI*				m_pVLeftBackSlider;
	CButtonUI*				m_pVLeftBackBtn;
	CButtonUI*				m_pVLeftBackRestBtn;
	CEditUI*				m_pVLeftBackEdit;

	/*	垂直右后	*/
	CSliderUI*				m_pVRightBackSlider;
	CButtonUI*				m_pVRightBackBtn;
	CButtonUI*				m_pVRightBackRestBtn;
	CEditUI*				m_pVRightBackEdit;

	/*	水平左	*/
	CSliderUI*				m_pHLeftSlider;
	CButtonUI*				m_pHLeftBtn;
	CButtonUI*				m_pHLeftRestBtn;
	CEditUI*				m_pHLeftEdit;

	/*	水平右	*/
	CSliderUI*				m_pHRightSlider;
	CButtonUI*				m_pHRightBtn;
	CButtonUI*				m_pHRightRestBtn;
	CEditUI*				m_pHRightEdit;
};

