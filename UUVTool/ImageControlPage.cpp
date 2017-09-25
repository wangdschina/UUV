#include "stdafx.h"
#include "ImageControlPage.h"
#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////////
///
DUI_BEGIN_MESSAGE_MAP(CImageControlPage, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_VALUECHANGED, OnValueChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_RETURN, OnReturn)
DUI_END_MESSAGE_MAP()

CImageControlPage::CImageControlPage()
{
	m_pUUV = nullptr;

	m_pPaintManager = nullptr;
	m_pImageControlPanel = nullptr;

	m_pCloudPitchSlider = nullptr;
	m_pCloudPitchBtn = nullptr;
	m_pCloudPitchRestBtn = nullptr;
	m_pCloudPitchEdit = nullptr;

	m_pCloudRotateSlider = nullptr;
	m_pCloudRotateBtn = nullptr;
	m_pCloudRotateRestBtn = nullptr;
	m_pCloudRotateEdit = nullptr;

	m_pCameraFocusSlider = nullptr;
	m_pCameraFocusBtn = nullptr;
	m_pCameraFocusRestBtn = nullptr;
	m_pCameraFocusEdit = nullptr;

	m_pCameraZoomSlider = nullptr;
	m_pCameraZoomBtn = nullptr;
	m_pCameraZoomRestBtn = nullptr;
	m_pCameraZoomEdit = nullptr;

	m_pLightLeftSlider = nullptr;
	m_pLightLeftBtn = nullptr;
	m_pLightLeftRestBtn = nullptr;
	m_pLightLeftEdit = nullptr;

	m_pLightRightSlider = nullptr;
	m_pLightRightBtn = nullptr;
	m_pLightRightRestBtn = nullptr;
	m_pLightRightEdit = nullptr;

	m_pOpenBatteryOption = nullptr;
	m_pCloseBatteryOption = nullptr;
	m_pBatteryBtn = nullptr;

	m_pOpenRockerOption = nullptr;
	m_pCloseRockerOption = nullptr;
	m_pRockerBtn = nullptr;

	m_pOpenOSDOption = nullptr;
	m_pCloseOSDOption = nullptr;
	m_pOosdBtn = nullptr;

	m_pOpenPeripOption = nullptr;
	m_pClosePeripOption = nullptr;
	m_pPeripBtn = nullptr;
}

CImageControlPage::~CImageControlPage()
{

}

void CImageControlPage::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	m_pPaintManager = pPaintMgr;
}

void CImageControlPage::InitWindow()
{
	m_pImageControlPanel = static_cast<CHorizontalLayoutUI*>(m_pPaintManager->FindControl(_T("imageControlPanel")));

	m_pCloudPitchSlider = static_cast<CSliderUI*>(m_pImageControlPanel->FindSubControl(_T("cloudPitchSlider")));
	m_pCloudPitchBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("cloudPitchBtn")));
	m_pCloudPitchRestBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("cloudPitchRestBtn")));
	m_pCloudPitchEdit = static_cast<CEditUI*>(m_pImageControlPanel->FindSubControl(_T("cloudPitchEdit")));

	m_pCloudRotateSlider = static_cast<CSliderUI*>(m_pImageControlPanel->FindSubControl(_T("cloudRotateSlider")));
	m_pCloudRotateBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("cloudRotateBtn")));
	m_pCloudRotateRestBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("cloudRotateRestBtn")));
	m_pCloudRotateEdit = static_cast<CEditUI*>(m_pImageControlPanel->FindSubControl(_T("cloudRotateEdit")));

	m_pCameraFocusSlider = static_cast<CSliderUI*>(m_pImageControlPanel->FindSubControl(_T("cameraFocusSlider")));
	m_pCameraFocusBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("cameraFocusBtn")));
	m_pCameraFocusRestBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("cameraFocusRestBtn")));
	m_pCameraFocusEdit = static_cast<CEditUI*>(m_pImageControlPanel->FindSubControl(_T("cameraFocusEdit")));

	m_pCameraZoomSlider = static_cast<CSliderUI*>(m_pImageControlPanel->FindSubControl(_T("cameraZoomSlider")));
	m_pCameraZoomBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("cameraZoomBtn")));
	m_pCameraZoomRestBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("cameraZoomRestBtn")));
	m_pCameraZoomEdit = static_cast<CEditUI*>(m_pImageControlPanel->FindSubControl(_T("cameraZoomEdit")));

	m_pLightLeftSlider = static_cast<CSliderUI*>(m_pImageControlPanel->FindSubControl(_T("lightLeftSlider")));
	m_pLightLeftBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("lightLeftBtn")));
	m_pLightLeftRestBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("lightLeftRestBtn")));
	m_pLightLeftEdit = static_cast<CEditUI*>(m_pImageControlPanel->FindSubControl(_T("lightLeftEdit")));

	m_pLightRightSlider = static_cast<CSliderUI*>(m_pImageControlPanel->FindSubControl(_T("lightRightSlider")));
	m_pLightRightBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("lightRightBtn")));
	m_pLightRightRestBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("lightRightRestBtn")));
	m_pLightRightEdit = static_cast<CEditUI*>(m_pImageControlPanel->FindSubControl(_T("lightRightEdit")));

	m_pOpenBatteryOption = static_cast<COptionUI*>(m_pImageControlPanel->FindSubControl(_T("openBatteryOption")));
	m_pCloseBatteryOption = static_cast<COptionUI*>(m_pImageControlPanel->FindSubControl(_T("closeBatteryOption")));
	m_pBatteryBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("batteryBtn")));

	m_pOpenRockerOption = static_cast<COptionUI*>(m_pImageControlPanel->FindSubControl(_T("openRockerOption")));
	m_pCloseRockerOption = static_cast<COptionUI*>(m_pImageControlPanel->FindSubControl(_T("closeRockerOption")));
	m_pRockerBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("rockerBtn")));

	m_pOpenOSDOption = static_cast<COptionUI*>(m_pImageControlPanel->FindSubControl(_T("openOSDOption")));
	m_pCloseOSDOption = static_cast<COptionUI*>(m_pImageControlPanel->FindSubControl(_T("closeOSDOption")));
	m_pOosdBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("osdBtn")));

	m_pOpenPeripOption = static_cast<COptionUI*>(m_pImageControlPanel->FindSubControl(_T("openPeripOption")));
	m_pClosePeripOption = static_cast<COptionUI*>(m_pImageControlPanel->FindSubControl(_T("closePeripOption")));
	m_pPeripBtn = static_cast<CButtonUI*>(m_pImageControlPanel->FindSubControl(_T("peripBtn")));
}

void CImageControlPage::InitUUV( IUUVObject* pUUV )
{
	m_pUUV = pUUV;
}

void CImageControlPage::OnClick( TNotifyUI& msg )
{
	if (m_pUUV == nullptr)
	{
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("UUVÊµÀýÎª¿Õ"));
		return;
	}

	if (msg.pSender == m_pCloudPitchBtn)
	{
		this->ClickCloudPitchBtn();
	}
	else if (msg.pSender == m_pCloudPitchRestBtn)
	{
		this->ClickCloudPitchRestBtn();
	}
	else if (msg.pSender == m_pCloudRotateBtn)
	{
		this->ClickCloudRotateBtn();
	}
	else if (msg.pSender == m_pCloudRotateRestBtn)
	{
		this->ClickCloudRotateRestBtn();
	}
	else if (msg.pSender == m_pCameraFocusBtn)
	{
		this->ClickCameraFocusBtn();
	}
	else if (msg.pSender == m_pCameraFocusRestBtn)
	{
		this->ClickCameraFocusRestBtn();
	}
	else if (msg.pSender == m_pCameraZoomBtn)
	{
		this->ClickCameraZoomBtn();
	}
	else if (msg.pSender == m_pCameraZoomRestBtn)
	{
		this->ClickCameraZoomRestBtn();
	}
	else if (msg.pSender == m_pLightLeftBtn)
	{
		this->ClickLightLeftBtn();
	}
	else if (msg.pSender == m_pLightLeftRestBtn)
	{
		this->ClickLightLeftRestBtn();
	}
	else if (msg.pSender == m_pLightRightBtn)
	{
		this->ClickLightRightBtn();
	}
	else if (msg.pSender == m_pLightRightRestBtn)
	{
		this->ClickLightRightRestBtn();
	}
	else if (msg.pSender == m_pBatteryBtn)
	{
		this->ClickBatteryBtn();
	}
	else if (msg.pSender == m_pRockerBtn)
	{
		this->ClickRockerBtn();
	}
	else if (msg.pSender == m_pOosdBtn)
	{
		this->ClickOsdBtn();
	}
	else if (msg.pSender == m_pPeripBtn)
	{
		this->ClickPeripBtn();
	}
}

void CImageControlPage::OnValueChanged( TNotifyUI& msg )
{
	if (msg.pSender == m_pCloudPitchSlider)
	{
		m_pCloudPitchEdit->SetText(CStringUtil::Format(_T("%d"), m_pCloudPitchSlider->GetValue()).c_str());
		this->ClickCloudPitchBtn();
	}
	else if (msg.pSender == m_pCloudRotateSlider)
	{
		m_pCloudRotateEdit->SetText(CStringUtil::Format(_T("%d"), m_pCloudRotateSlider->GetValue()).c_str());
		this->ClickCloudRotateBtn();
	}
	else if (msg.pSender == m_pCameraFocusSlider)
	{
		m_pCameraFocusEdit->SetText(CStringUtil::Format(_T("%d"), m_pCameraFocusSlider->GetValue()).c_str());
		this->ClickCameraFocusBtn();
	}
	else if (msg.pSender == m_pCameraZoomSlider)
	{
		m_pCameraZoomEdit->SetText(CStringUtil::Format(_T("%d"), m_pCameraZoomSlider->GetValue()).c_str());
		this->ClickCameraZoomBtn();
	}
	else if (msg.pSender == m_pLightLeftSlider)
	{
		m_pLightLeftEdit->SetText(CStringUtil::Format(_T("%d"), m_pLightLeftSlider->GetValue()).c_str());
		this->ClickLightLeftBtn();
	}
	else if (msg.pSender == m_pLightRightSlider)
	{
		m_pLightRightEdit->SetText(CStringUtil::Format(_T("%d"), m_pLightRightSlider->GetValue()).c_str());
		this->ClickLightRightBtn();
	}
}

void CImageControlPage::OnReturn( TNotifyUI& msg )
{
	if (msg.pSender == m_pCloudPitchEdit)
	{
		int nValue = CStringUtil::ToInt(m_pCloudPitchEdit->GetText().GetData());
		if (nValue >= m_pCloudPitchSlider->GetMinValue() && nValue <= m_pCloudPitchSlider->GetMaxValue())
		{
			m_pCloudPitchSlider->SetValue(nValue);
			this->ClickCloudPitchBtn();
		}
	}
	else if (msg.pSender == m_pCloudRotateEdit)
	{
		int nValue = CStringUtil::ToInt(m_pCloudRotateEdit->GetText().GetData());
		if (nValue >= m_pCloudRotateSlider->GetMinValue() && nValue <= m_pCloudRotateSlider->GetMaxValue())
		{
			m_pCloudRotateSlider->SetValue(nValue);
			this->ClickCloudRotateBtn();
		}
	}
	else if (msg.pSender == m_pCameraFocusEdit)
	{
		int nValue = CStringUtil::ToInt(m_pCameraFocusEdit->GetText().GetData());
		if (nValue >= m_pCameraFocusSlider->GetMinValue() && nValue <= m_pCameraFocusSlider->GetMaxValue())
		{
			m_pCameraFocusSlider->SetValue(nValue);
			this->ClickCameraFocusBtn();
		}
	}
	else if (msg.pSender == m_pCameraZoomEdit)
	{
		int nValue = CStringUtil::ToInt(m_pCameraZoomEdit->GetText().GetData());
		if (nValue >= m_pCameraZoomSlider->GetMinValue() && nValue <= m_pCameraZoomSlider->GetMaxValue())
		{
			m_pCameraZoomSlider->SetValue(nValue);
			this->ClickCameraZoomBtn();
		}
	}
	else if (msg.pSender == m_pLightLeftEdit)
	{
		int nValue = CStringUtil::ToInt(m_pLightLeftEdit->GetText().GetData());
		if (nValue >= m_pLightLeftSlider->GetMinValue() && nValue <= m_pLightLeftSlider->GetMaxValue())
		{
			m_pLightLeftSlider->SetValue(nValue);
			this->ClickLightLeftBtn();
		}
	}
	else if (msg.pSender == m_pLightRightEdit)
	{
		int nValue = CStringUtil::ToInt(m_pLightRightEdit->GetText().GetData());
		if (nValue >= m_pLightRightSlider->GetMinValue() && nValue <= m_pLightRightSlider->GetMaxValue())
		{
			m_pLightRightSlider->SetValue(nValue);
			this->ClickLightRightBtn();
		}
	}
}

void CImageControlPage::SetSliderTip( CSliderUI* pSlider )
{
	if (pSlider == nullptr)
	{
		return;
	}
	pSlider->SetToolTip(CStringUtil::Format(_T("%d"), pSlider->GetValue()).c_str());
}

void CImageControlPage::ClickCloudPitchBtn()
{
	int nErrno = ERR_SUCCESS;
	short nPitch = m_pCloudPitchSlider->GetValue();

	if(!m_pUUV->UUV_Set(UUV_CAMERA_PITCH_SET, &nPitch))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃÔÆÌ¨¸©Ñö£¬´íÎóÂë %d"), nErrno);
	}
}

void CImageControlPage::ClickCloudRotateBtn()
{
	//int nRotate = m_pCloudRotateSlider->GetValue();
	int nErrno = ERR_SUCCESS;
	short nRotate = m_pCloudRotateSlider->GetValue();
	if(!m_pUUV->UUV_Set(UUV_CAMERA_ROTATE_SET, &nRotate))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃÔÆÌ¨Ðý×ª£¬´íÎóÂë %d"), nErrno);
	}

}

void CImageControlPage::ClickCameraFocusBtn()
{
	//int nFocus = m_pCameraFocusSlider->GetValue();
	int nErrno = ERR_SUCCESS;
	unsigned char nFocus = (unsigned char)m_pCameraFocusSlider->GetValue();

	if(!m_pUUV->UUV_Set(UUV_CAMERA_FOUCUS_SET, &nFocus))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃ¾Û½¹Ê§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CImageControlPage::ClickCameraZoomBtn()
{
	//int nZoom = m_pCameraZoomSlider->GetValue();
	int nErrno = ERR_SUCCESS;
	unsigned char  nZoom = (unsigned char)m_pCameraZoomSlider->GetValue();

	if(!m_pUUV->UUV_Set(UUV_CAMERA_ZOOM_SET, &nZoom))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃ±ä±¶Ê§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CImageControlPage::ClickLightLeftBtn()
{
	int nErrno = ERR_SUCCESS;

	unsigned char nLeft = m_pLightLeftSlider->GetValue();
	UUVLIGHT_T light;
	light.lightindex =0;//´ú±í×óµÆ
	light.lum =nLeft;

	if(!m_pUUV->UUV_Set(UUV_LIGHT_VALNE_SET, &light))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃ×óµÆÁÁ¶ÈÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CImageControlPage::ClickLightRightBtn()
{
	int nErrno = ERR_SUCCESS;
	unsigned char nRight = m_pLightRightSlider->GetValue();
	UUVLIGHT_T light;
	light.lightindex =1;//1´ú±íÓÒµÆ
	light.lum =nRight;
	if(!m_pUUV->UUV_Set(UUV_LIGHT_VALNE_SET, &light))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃ×óµÆÁÁ¶ÈÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CImageControlPage::ClickCloudPitchRestBtn()
{
	m_pCloudPitchSlider->SetValue(0);
	m_pCloudPitchEdit->SetText(_T("0"));
	this->ClickCloudPitchBtn();
}

void CImageControlPage::ClickCloudRotateRestBtn()
{
	m_pCloudRotateSlider->SetValue(0);
	m_pCloudRotateEdit->SetText(_T(""));
	this->ClickCloudRotateBtn();
}

void CImageControlPage::ClickCameraFocusRestBtn()
{
	m_pCameraFocusSlider->SetValue(0);
	m_pCameraFocusEdit->SetText(_T("0"));
	this->ClickCameraFocusBtn();
}

void CImageControlPage::ClickCameraZoomRestBtn()
{
	m_pCameraZoomSlider->SetValue(0);
	m_pCameraZoomEdit->SetText(_T("0"));
	this->ClickCameraZoomBtn();
}

void CImageControlPage::ClickLightLeftRestBtn()
{
	m_pLightLeftSlider->SetValue(0);
	m_pLightLeftEdit->SetText(_T("0"));
	this->ClickLightLeftBtn();
}

void CImageControlPage::ClickLightRightRestBtn()
{
	m_pLightRightSlider->SetValue(0);
	m_pLightRightEdit->SetText(_T("0"));
	this->ClickLightRightBtn();
}

void CImageControlPage::ClickOsdBtn()
{
	int nErrno = ERR_SUCCESS;
	UUVOSD_T osd={0,0};
	if (m_pOpenOSDOption->IsSelected())
	{
		osd.osd_on=1;
	}
	else if (m_pCloseOSDOption->IsSelected())
	{
		osd.osd_on=0;
	}

	if (m_pOpenBatteryOption->IsSelected())
	{
		osd.battery_on=1;
	}
	else if (m_pCloseBatteryOption->IsSelected())
	{
		osd.battery_on=0;
	}

	if(!m_pUUV->UUV_Set(UUV_CAMERA_OSD_SET, &osd))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃÍ¼ÏñOSD¶ÈÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}


}
void CImageControlPage::ClickBatteryBtn()
{

}

void CImageControlPage::ClickRockerBtn()
{
	if (m_pOpenRockerOption->IsSelected())
	{
	}
	else if (m_pCloseRockerOption->IsSelected())
	{
	}
}



void CImageControlPage::ClickPeripBtn()
{
	if (m_pOpenPeripOption->IsSelected())
	{
	}
	else if (m_pClosePeripOption->IsSelected())
	{
	}
}
