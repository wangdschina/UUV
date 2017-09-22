#include "stdafx.h"
#include "PowerControlPage.h"
#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////////
///
DUI_BEGIN_MESSAGE_MAP(CPowerControlPage, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_END_MESSAGE_MAP()

	CPowerControlPage::CPowerControlPage()
{
	m_pUUV = nullptr;

	m_pPaintManager = nullptr;
	m_pPowerControlPanel = nullptr;

	m_pCameraPowerOption = nullptr;
	m_pPOEPowerOption = nullptr;
	m_pPowerOneBtn = nullptr;

	m_pPeripPowerOption = nullptr;
	m_pOtherPowerOption = nullptr;
	m_pPowerTwoBtn = nullptr;

	m_pLowConsumOption = nullptr;
	m_pHighConsumOption = nullptr;
	m_pPowerConsumModeBtn = nullptr;
}

CPowerControlPage::~CPowerControlPage()
{

}

void CPowerControlPage::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	m_pPaintManager = pPaintMgr;
}

void CPowerControlPage::InitWindow()
{
	m_pPowerControlPanel = static_cast<CHorizontalLayoutUI*>(m_pPaintManager->FindControl(_T("powerControlPanel")));

	m_pCameraPowerOption = static_cast<COptionUI*>(m_pPowerControlPanel->FindSubControl(_T("cameraPowerOption")));
	m_pPOEPowerOption = static_cast<COptionUI*>(m_pPowerControlPanel->FindSubControl(_T("poePowerOption")));
	m_pPowerOneBtn = static_cast<CButtonUI*>(m_pPowerControlPanel->FindSubControl(_T("powerOneBtn")));

	m_pPeripPowerOption = static_cast<COptionUI*>(m_pPowerControlPanel->FindSubControl(_T("peripPowerOption")));
	m_pOtherPowerOption = static_cast<COptionUI*>(m_pPowerControlPanel->FindSubControl(_T("otherPowerOption")));
	m_pPowerTwoBtn = static_cast<CButtonUI*>(m_pPowerControlPanel->FindSubControl(_T("powerTwoBtn")));

	m_pLowConsumOption = static_cast<COptionUI*>(m_pPowerControlPanel->FindSubControl(_T("lowConsumOption")));
	m_pHighConsumOption = static_cast<COptionUI*>(m_pPowerControlPanel->FindSubControl(_T("highConsumOption")));
	m_pPowerConsumModeBtn = static_cast<CButtonUI*>(m_pPowerControlPanel->FindSubControl(_T("powerConsumModeBtn")));
}

void CPowerControlPage::InitUUV( IUUVObject* pUUV )
{
	m_pUUV = pUUV;
}

void CPowerControlPage::OnClick( TNotifyUI& msg )
{
	if (m_pUUV == nullptr)
	{
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("UUV实例为空"));
		return;
	}

	if (msg.pSender == m_pPowerOneBtn)
	{
		this->ClickPowerOneBtn();
	}
	else if (msg.pSender == m_pPowerTwoBtn)
	{
		this->ClickPowerTwoBtn();
	}
	else if (msg.pSender == m_pPowerConsumModeBtn)
	{
		this->ClickPowerConsumModeBtn();
	}
}
//POE设备上电（图像声呐）
void CPowerControlPage::ClickPowerOneBtn()
{
	int nErrno = ERR_SUCCESS;
	UUVEXTERNALPOWER_T power={0,0};

	if (m_pPOEPowerOption->IsSelected())
	{
		power.POEpoweron=0;
	}
	else
	{
		power.POEpoweron=1;
	}
	if (m_pPeripPowerOption->IsSelected())
	{
		power.CANpoweron=0;
	}
	else
	{
		power.CANpoweron=1;
	}
	if(!m_pUUV->UUV_Set(UUV_POE_CAN_POWER_SET, &power))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("设置POE_CAN电源失败，错误码 %d"), nErrno);
	}

}
//can外挂设备上电（机械手）
void CPowerControlPage::ClickPowerTwoBtn()
{
	/*
	int nErrno = ERR_SUCCESS;
	UUVUUVEXTERNALPOWER_T power={2,1};

	if(!m_pUUV->UUV_Set(UUV_POE_CAN_POWER_SET, &power))
	{
	nErrno = m_pUUV->UUV_GetErrno();
	LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("设置POE_CAN电源失败，错误码 %d"), nErrno);
	}
	*/
}

void CPowerControlPage::ClickPowerConsumModeBtn()
{
	int nErrno = ERR_SUCCESS;
	unsigned char power=0;
	if (m_pLowConsumOption->IsSelected())
	{
		power=1;//第六位
	}
	else if (m_pHighConsumOption->IsSelected())
	{
		power=0;
	}

	if(!m_pUUV->UUV_Set(UUV_CONSUMPTION_SET, &power))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("设置功耗模式失败，错误码 %d"), nErrno);
	}

}