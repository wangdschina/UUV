#pragma once

class CImageControlPage : public CNotifyPump
{
public:
	CImageControlPage();
	~CImageControlPage();

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

	void ClickCloudPitchBtn();		//	云台俯仰
	void ClickCloudPitchRestBtn();	//	云台俯仰复位
	void ClickCloudRotateBtn();		//	云台旋转
	void ClickCloudRotateRestBtn();	//	云台旋转复位
	void ClickCameraFocusBtn();		//	镜头聚焦
	void ClickCameraFocusRestBtn();	//	镜头聚焦复位
	void ClickCameraZoomBtn();		//	镜头变焦
	void ClickCameraZoomRestBtn();	//	镜头变焦复位
	void ClickLightLeftBtn();		//	亮度左
	void ClickLightLeftRestBtn();	//	亮度左复位
	void ClickLightRightBtn();		//	亮度右
	void ClickLightRightRestBtn();	//	亮度右复位
	void ClickBatteryBtn();			//	电池显示
	void ClickRockerBtn();			//	摇杆显示
	void ClickOsdBtn();				//	OSD显示
	void ClickPeripBtn();			//	外设显示

private:
	IUUVObject*				m_pUUV;

private:
	CPaintManagerUI*		m_pPaintManager;
	CHorizontalLayoutUI*	m_pImageControlPanel;

	/*	云台俯仰	*/
	CSliderUI*				m_pCloudPitchSlider;
	CButtonUI*				m_pCloudPitchBtn;
	CButtonUI*				m_pCloudPitchRestBtn;
	CEditUI*				m_pCloudPitchEdit;

	/*	云台旋转	*/
	CSliderUI*				m_pCloudRotateSlider;
	CButtonUI*				m_pCloudRotateBtn;
	CButtonUI*				m_pCloudRotateRestBtn;
	CEditUI*				m_pCloudRotateEdit;

	/*	镜头聚焦	*/
	CSliderUI*				m_pCameraFocusSlider;
	CButtonUI*				m_pCameraFocusBtn;
	CButtonUI*				m_pCameraFocusRestBtn;
	CEditUI*				m_pCameraFocusEdit;

	/*	镜头变焦	*/
	CSliderUI*				m_pCameraZoomSlider;
	CButtonUI*				m_pCameraZoomBtn;
	CButtonUI*				m_pCameraZoomRestBtn;
	CEditUI*				m_pCameraZoomEdit;

	/*	亮度左	*/
	CSliderUI*				m_pLightLeftSlider;
	CButtonUI*				m_pLightLeftBtn;
	CButtonUI*				m_pLightLeftRestBtn;
	CEditUI*				m_pLightLeftEdit;

	/*	亮度右	*/
	CSliderUI*				m_pLightRightSlider;
	CButtonUI*				m_pLightRightBtn;
	CButtonUI*				m_pLightRightRestBtn;
	CEditUI*				m_pLightRightEdit;

	/*	电池显示	*/
	COptionUI*				m_pOpenBatteryOption;
	COptionUI*				m_pCloseBatteryOption;
	CButtonUI*				m_pBatteryBtn;

	/*	摇杆显示	*/
	COptionUI*				m_pOpenRockerOption;
	COptionUI*				m_pCloseRockerOption;
	CButtonUI*				m_pRockerBtn;

	/*	OSD显示	*/
	COptionUI*				m_pOpenOSDOption;
	COptionUI*				m_pCloseOSDOption;
	CButtonUI*				m_pOosdBtn;

	/*	电池显示	*/
	COptionUI*				m_pOpenPeripOption;
	COptionUI*				m_pClosePeripOption;
	CButtonUI*				m_pPeripBtn;
};

