#include "stdafx.h"
#include "MotoControlPage.h"
#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////////
///
DUI_BEGIN_MESSAGE_MAP(CMotoControlPage, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_VALUECHANGED, OnValueChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_RETURN, OnReturn)
	DUI_END_MESSAGE_MAP()

	CMotoControlPage::CMotoControlPage()
{
	m_pUUV = nullptr;

	m_pPaintManager = nullptr;
	m_pMotoControlPanel = nullptr;

	m_pVLeftFrontSlider = nullptr;
	m_pVLeftFrontBtn = nullptr;
	m_pVLeftFrontRestBtn = nullptr;
	m_pVLeftFrontEdit = nullptr;

	m_pVRightFrontSlider = nullptr;
	m_pVRightFrontBtn = nullptr;
	m_pVRightFrontRestBtn = nullptr;
	m_pVRightFrontEdit = nullptr;

	m_pVLeftBackSlider = nullptr;
	m_pVLeftBackBtn = nullptr;
	m_pVLeftBackRestBtn = nullptr;
	m_pVLeftBackEdit = nullptr;

	m_pVRightBackSlider = nullptr;
	m_pVRightBackBtn = nullptr;
	m_pVRightBackRestBtn = nullptr;
	m_pVRightBackEdit = nullptr;

	m_pHLeftSlider = nullptr;
	m_pHLeftBtn = nullptr;
	m_pHLeftRestBtn = nullptr;
	m_pHLeftEdit = nullptr;

	m_pHRightSlider = nullptr;
	m_pHRightBtn = nullptr;
	m_pHRightRestBtn = nullptr;
	m_pHRightEdit = nullptr;
}

CMotoControlPage::~CMotoControlPage()
{

}

void CMotoControlPage::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	m_pPaintManager = pPaintMgr;
}

void CMotoControlPage::InitWindow()
{
	m_pMotoControlPanel = static_cast<CHorizontalLayoutUI*>(m_pPaintManager->FindControl(_T("motoControlPanel")));

	m_pVLeftFrontSlider = static_cast<CSliderUI*>(m_pMotoControlPanel->FindSubControl(_T("vLeftFrontSlider")));
	m_pVLeftFrontBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("vLeftFrontBtn")));
	m_pVLeftFrontRestBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("vLeftFrontRestBtn")));
	m_pVLeftFrontEdit = static_cast<CEditUI*>(m_pMotoControlPanel->FindSubControl(_T("vLeftFrontEdit")));

	m_pVRightFrontSlider = static_cast<CSliderUI*>(m_pMotoControlPanel->FindSubControl(_T("vRightFrontSlider")));
	m_pVRightFrontBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("vRightFrontBtn")));
	m_pVRightFrontRestBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("vRightFrontRestBtn")));
	m_pVRightFrontEdit = static_cast<CEditUI*>(m_pMotoControlPanel->FindSubControl(_T("vRightFrontEdit")));

	m_pVLeftBackSlider = static_cast<CSliderUI*>(m_pMotoControlPanel->FindSubControl(_T("vLeftBackSlider")));
	m_pVLeftBackBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("vLeftBackBtn")));
	m_pVLeftBackRestBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("vLeftBackRestBtn")));
	m_pVLeftBackEdit = static_cast<CEditUI*>(m_pMotoControlPanel->FindSubControl(_T("vLeftBackEdit")));

	m_pVRightBackSlider = static_cast<CSliderUI*>(m_pMotoControlPanel->FindSubControl(_T("vRightBackSlider")));
	m_pVRightBackBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("vRightBackBtn")));
	m_pVRightBackRestBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("vRightBackRestBtn")));
	m_pVRightBackEdit = static_cast<CEditUI*>(m_pMotoControlPanel->FindSubControl(_T("vRightBackEdit")));

	m_pHLeftSlider = static_cast<CSliderUI*>(m_pMotoControlPanel->FindSubControl(_T("hLeftSlider")));
	m_pHLeftBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("hLeftBtn")));
	m_pHLeftRestBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("hLeftRestBtn")));
	m_pHLeftEdit = static_cast<CEditUI*>(m_pMotoControlPanel->FindSubControl(_T("hLeftEdit")));

	m_pHRightSlider = static_cast<CSliderUI*>(m_pMotoControlPanel->FindSubControl(_T("hRightSlider")));
	m_pHRightBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("hRightBtn")));
	m_pHRightRestBtn = static_cast<CButtonUI*>(m_pMotoControlPanel->FindSubControl(_T("hRightRestBtn")));
	m_pHRightEdit = static_cast<CEditUI*>(m_pMotoControlPanel->FindSubControl(_T("hRightEdit")));
}

void CMotoControlPage::InitUUV( IUUVObject* pUUV )
{
	m_pUUV = pUUV;
}

void CMotoControlPage::OnClick( TNotifyUI& msg )
{
	if (m_pUUV == nullptr)
	{
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("UUVÊµÀýÎª¿Õ"));
		return;
	}

	if (msg.pSender == m_pVLeftFrontBtn)
	{
		this->ClickVLeftFrontBtn();
	}
	else if (msg.pSender == m_pVLeftFrontRestBtn)
	{
		this->ClickVLeftFrontRestBtn();
	}
	else if (msg.pSender == m_pVRightFrontBtn)
	{
		this->ClickVRightFrontBtn();
	}
	else if (msg.pSender == m_pVRightFrontRestBtn)
	{
		this->ClickVRightFrontRestBtn();
	}
	else if (msg.pSender == m_pVLeftBackBtn)
	{
		this->ClickVLeftBackBtn();
	}
	else if (msg.pSender == m_pVLeftBackRestBtn)
	{
		this->ClickVLeftBackRestBtn();
	}
	else if (msg.pSender == m_pVRightBackBtn)
	{
		this->ClickVRightBackBtn();
	}
	else if (msg.pSender == m_pVRightBackRestBtn)
	{
		this->ClickVRightBackRestBtn();
	}
	else if (msg.pSender == m_pHLeftBtn)
	{
		this->ClickHLeftBtn();
	}
	else if (msg.pSender == m_pHLeftRestBtn)
	{
		this->ClickHLeftRestBtn();
	}
	else if (msg.pSender == m_pHRightBtn)
	{
		this->ClickHRightBtn();
	}
	else if (msg.pSender == m_pHRightRestBtn)
	{
		this->ClickHRightRestBtn();
	}
}

void CMotoControlPage::OnValueChanged( TNotifyUI& msg )
{
	if (msg.pSender == m_pVLeftFrontSlider)
	{
		m_pVLeftFrontEdit->SetText(CStringUtil::Format(_T("%d"), m_pVLeftFrontSlider->GetValue()).c_str());
		this->ClickVLeftFrontBtn();
	}
	else if (msg.pSender == m_pVRightFrontSlider)
	{
		m_pVRightFrontEdit->SetText(CStringUtil::Format(_T("%d"), m_pVRightFrontSlider->GetValue()).c_str());
		this->ClickVRightFrontBtn();
	}
	else if (msg.pSender == m_pVLeftBackSlider)
	{
		m_pVLeftBackEdit->SetText(CStringUtil::Format(_T("%d"), m_pVLeftBackSlider->GetValue()).c_str());
		this->ClickVLeftBackBtn();
	}
	else if (msg.pSender == m_pVRightBackSlider)
	{
		m_pVRightBackEdit->SetText(CStringUtil::Format(_T("%d"), m_pVRightBackSlider->GetValue()).c_str());
		this->ClickVRightBackBtn();
	}
	else if (msg.pSender == m_pHLeftSlider)
	{
		m_pHLeftEdit->SetText(CStringUtil::Format(_T("%d"), m_pHLeftSlider->GetValue()).c_str());
		this->ClickHLeftBtn();
	}
	else if (msg.pSender == m_pHRightSlider)
	{
		m_pHRightEdit->SetText(CStringUtil::Format(_T("%d"), m_pHRightSlider->GetValue()).c_str());
		this->ClickHRightBtn();
	}
}

void CMotoControlPage::OnReturn( TNotifyUI& msg )
{
	if (msg.pSender == m_pVLeftFrontEdit)
	{
		int nValue = CStringUtil::ToInt(m_pVLeftFrontEdit->GetText().GetData());
		if (nValue >= m_pVLeftFrontSlider->GetMinValue() && nValue <= m_pVLeftFrontSlider->GetMaxValue())
		{
			m_pVLeftFrontSlider->SetValue(nValue);
			this->ClickVLeftFrontBtn();
		}
	}
	else if (msg.pSender == m_pVRightFrontEdit)
	{
		int nValue = CStringUtil::ToInt(m_pVRightFrontEdit->GetText().GetData());
		if (nValue >= m_pVRightFrontSlider->GetMinValue() && nValue <= m_pVRightFrontSlider->GetMaxValue())
		{
			m_pVRightFrontSlider->SetValue(nValue);
			this->ClickVRightFrontBtn();
		}
	}
	else if (msg.pSender == m_pVLeftBackEdit)
	{
		int nValue = CStringUtil::ToInt(m_pVLeftBackEdit->GetText().GetData());
		if (nValue >= m_pVLeftBackSlider->GetMinValue() && nValue <= m_pVLeftBackSlider->GetMaxValue())
		{
			m_pVLeftBackSlider->SetValue(nValue);
			this->ClickVLeftBackBtn();
		}
	}
	else if (msg.pSender == m_pVRightBackEdit)
	{
		int nValue = CStringUtil::ToInt(m_pVRightBackEdit->GetText().GetData());
		if (nValue >= m_pVRightBackSlider->GetMinValue() && nValue <= m_pVRightBackSlider->GetMaxValue())
		{
			m_pVRightBackSlider->SetValue(nValue);
			this->ClickVRightBackBtn();
		}
	}
	else if (msg.pSender == m_pHLeftEdit)
	{
		int nValue = CStringUtil::ToInt(m_pHLeftEdit->GetText().GetData());
		if (nValue >= m_pHLeftSlider->GetMinValue() && nValue <= m_pHLeftSlider->GetMaxValue())
		{
			m_pHLeftSlider->SetValue(nValue);
			this->ClickHLeftBtn();
		}
	}
	else if (msg.pSender == m_pHRightEdit)
	{
		int nValue = CStringUtil::ToInt(m_pHRightEdit->GetText().GetData());
		if (nValue >= m_pHRightSlider->GetMinValue() && nValue <= m_pHRightSlider->GetMaxValue())
		{
			m_pHRightSlider->SetValue(nValue);
			this->ClickHRightBtn();
		}
	}
}

void CMotoControlPage::SetSliderTip( CSliderUI* pSlider )
{
	if (pSlider == nullptr)
	{
		return;
	}
	pSlider->SetToolTip(CStringUtil::Format(_T("%d"), pSlider->GetValue()).c_str());
}

void CMotoControlPage::Send_Motor_Speed(UUVMOTOR_T motor)
{
	int nErrno = ERR_SUCCESS;
	if(!m_pUUV->UUV_Set(UUV_MOTOR_SPEED_SET, &motor))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃµç»ú%x´íÎó£¬´íÎóÂë %d"),motor.motorindex , nErrno);
	}

}
	
void CMotoControlPage::ClickVLeftFrontBtn()
{
	short nSpeed = m_pVLeftFrontSlider->GetValue();
	UUVMOTOR_T motor;
	motor.motorindex =V_L_F_MOTORINDEX;
	motor.motorspeed   =nSpeed;
	Send_Motor_Speed(motor);
}

void CMotoControlPage::ClickVRightFrontBtn()
{
	short nSpeed = m_pVRightFrontSlider->GetValue();
	UUVMOTOR_T motor;
	motor.motorindex =V_R_F_MOTORINDEX;
	motor.motorspeed   =nSpeed;
	Send_Motor_Speed(motor);
}

void CMotoControlPage::ClickVLeftBackBtn()
{
	short nSpeed = m_pVLeftBackSlider->GetValue();
	UUVMOTOR_T motor;
	motor.motorindex =V_L_B_MOTORINDEX;
	motor.motorspeed   =nSpeed;
	Send_Motor_Speed(motor);
}

void CMotoControlPage::ClickVRightBackBtn()
{
	short nSpeed = m_pVRightBackSlider->GetValue();
	UUVMOTOR_T motor;
	motor.motorindex =V_R_B_MOTORINDEX;
	motor.motorspeed   =nSpeed;
	Send_Motor_Speed(motor);
}

void CMotoControlPage::ClickHLeftBtn()
{
	short nSpeed = m_pHLeftSlider->GetValue();
	UUVMOTOR_T motor;
	motor.motorindex =H_L_MOTORINDEX;
	motor.motorspeed   =nSpeed;
	Send_Motor_Speed(motor);
}

void CMotoControlPage::ClickHRightBtn()
{
	short nSpeed = m_pHRightSlider->GetValue();
	UUVMOTOR_T motor;
	motor.motorindex =H_R_MOTORINDEX;
	motor.motorspeed   =nSpeed;
	Send_Motor_Speed(motor);
}

void CMotoControlPage::ClickVLeftFrontRestBtn()
{
	m_pVLeftFrontSlider->SetValue(0);
	m_pVLeftFrontEdit->SetText(_T("0"));
	this->ClickVLeftFrontBtn();
}

void CMotoControlPage::ClickVRightFrontRestBtn()
{
	m_pVRightFrontSlider->SetValue(0);
	m_pVRightFrontEdit->SetText(_T("0"));
	this->ClickVRightFrontBtn();
}

void CMotoControlPage::ClickVLeftBackRestBtn()
{
	m_pVLeftBackSlider->SetValue(0);
	m_pVLeftBackEdit->SetText(_T("0"));
	this->ClickVLeftBackBtn();
}

void CMotoControlPage::ClickVRightBackRestBtn()
{
	m_pVRightBackSlider->SetValue(0);
	m_pVRightBackEdit->SetText(_T("0"));
	this->ClickVRightBackBtn();
}

void CMotoControlPage::ClickHLeftRestBtn()
{
	m_pHLeftSlider->SetValue(0);
	m_pHLeftEdit->SetText(_T("0"));
	this->ClickHLeftBtn();
}

void CMotoControlPage::ClickHRightRestBtn()
{
	m_pHRightSlider->SetValue(0);
	m_pHRightEdit->SetText(_T("0"));
	this->ClickHRightBtn();
}
