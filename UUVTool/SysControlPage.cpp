#include "stdafx.h"
#include "SysControlPage.h"
#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////////
///
DUI_BEGIN_MESSAGE_MAP(CSysControlPage, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_VALUECHANGED, OnValueChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_RETURN, OnReturn)
	DUI_END_MESSAGE_MAP()

	CSysControlPage::CSysControlPage()
{
	m_pUUV = nullptr;

	m_pPaintManager = nullptr;
	m_pSysControlPanel = nullptr;

	m_pManipOpenSlider = nullptr;
	m_pManipulatorStopBtn = nullptr;
	m_pManipulatorControlBtn = nullptr;
	m_pManipOpenEdit = nullptr;

	m_pSoftRestartBtn = nullptr;
}

CSysControlPage::~CSysControlPage()
{

}

void CSysControlPage::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	m_pPaintManager = pPaintMgr;
}

void CSysControlPage::InitWindow()
{
	m_pSysControlPanel = static_cast<CHorizontalLayoutUI*>(m_pPaintManager->FindControl(_T("sysControlPanel")));

	m_pManipOpenSlider = static_cast<CSliderUI*>(m_pSysControlPanel->FindSubControl(_T("manipOpenOption")));
	m_pManipulatorControlBtn = static_cast<CButtonUI*>(m_pSysControlPanel->FindSubControl(_T("manipulatorControlBtn")));
	m_pManipulatorStopBtn = static_cast<CButtonUI*>(m_pSysControlPanel->FindSubControl(_T("manipulatorControlRestBtn")));
	m_pManipOpenEdit = static_cast<CEditUI*>(m_pSysControlPanel->FindSubControl(_T("manipOpenEdit")));

	m_pSoftRestartBtn = static_cast<CButtonUI*>(m_pSysControlPanel->FindSubControl(_T("softRestartBtn")));
}

void CSysControlPage::InitUUV( IUUVObject* pUUV )
{
	m_pUUV = pUUV;
}

void CSysControlPage::OnClick( TNotifyUI& msg )
{
	if (m_pUUV == nullptr)
	{
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("UUVÊµÀýÎª¿Õ"));
		return;
	}

	if (msg.pSender == m_pManipulatorControlBtn)
	{
		this->ClickManipControlBtn();
	}
	else if (msg.pSender == m_pManipulatorStopBtn)
	{
		this->ClickManipStopBtn();
	}
	else if (msg.pSender == m_pSoftRestartBtn)
	{
		this->ClickSoftRestartBtn();
	}

}

void CSysControlPage::OnValueChanged( TNotifyUI& msg )
{
	if (msg.pSender == m_pManipOpenSlider)
	{
		m_pManipOpenEdit->SetText(CStringUtil::Format(_T("%d"), m_pManipOpenSlider->GetValue()).c_str());
		this->ClickManipControlBtn();
	}
}

void CSysControlPage::OnReturn( TNotifyUI& msg )
{
	if (msg.pSender == m_pManipOpenEdit)
	{
		int nValue = CStringUtil::ToInt(m_pManipOpenEdit->GetText().GetData());
		if (nValue >= m_pManipOpenSlider->GetMinValue() && nValue <= m_pManipOpenSlider->GetMaxValue())
		{
			m_pManipOpenSlider->SetValue(nValue);
			this->ClickManipControlBtn();
		}
	}
}

void CSysControlPage::ClickSoftRestartBtn()
{
	int nErrno = ERR_SUCCESS;
	unsigned char power=1;

	if(!m_pUUV->UUV_Set(UUV_SYSTEM_POWER_SET, &power))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃÈíÖØÆôÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}


void CSysControlPage::ClickManipControlBtn()
{
	int nErrno = ERR_SUCCESS;	
	short nSpeed = m_pManipOpenSlider->GetValue();

	if(!m_pUUV->UUV_Set(UUV_MANIP_OPERATION_SET, &nSpeed))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃ»úÐµÊÖ²Ù×÷Ê§°Ü£¬´íÎóÂë %d"), nErrno);
	}	


}
void CSysControlPage::ClickManipStopBtn()
{
	m_pManipOpenSlider->SetValue(0);
	m_pManipOpenEdit->SetText(_T("0"));
	this->ClickManipControlBtn();
}
