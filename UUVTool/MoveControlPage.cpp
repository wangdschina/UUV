#include "stdafx.h"
#include "MoveControlPage.h"
#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////////
///
DUI_BEGIN_MESSAGE_MAP(CMoveControlPage, CNotifyPump)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_VALUECHANGED, OnValueChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_TEXTCHANGED, OnTextChanged)
	DUI_ON_MSGTYPE(DUI_MSGTYPE_RETURN, OnReturn)
	DUI_END_MESSAGE_MAP()

	CMoveControlPage::CMoveControlPage()
{
	m_pUUV = nullptr;

	m_pPaintManager = nullptr;
	m_pMoveControlPanel = nullptr;

	m_pSpeedSlider = nullptr;
	m_pSpeedBtn = nullptr;
	m_pSpeedRestBtn = nullptr;
	m_pSpeedEdit = nullptr;

	m_pDeepSlider = nullptr;
	m_pDeepBtn = nullptr;
	m_pDeepRestBtn = nullptr;
	m_pDeepEdit = nullptr;

	m_pPitchAngleSlider = nullptr;
	m_pPitchAngleBtn = nullptr;
	m_pPitchAngleRestBtn = nullptr;
	m_pPitchAngleEdit = nullptr;

	m_pRollAngleSlider = nullptr;
	m_pRollAngleBtn = nullptr;
	m_pRollAngleRestBtn = nullptr;
	m_pRollAngleEdit = nullptr;

	m_pHeadAngleSlider = nullptr;
	m_pHeadAngleBtn = nullptr;
	m_pHeadAngleRestBtn = nullptr;
	m_pHeadAngleEdit = nullptr;

	m_pDiffControlOption = nullptr;
	m_pGesControlOption = nullptr;
	m_pControlModeBtn = nullptr;

	m_pIneNaviOption = nullptr;
	m_pGeoNaviOption = nullptr;
	m_pNaviModeBtn = nullptr;

	m_pMoveModeStopOption = nullptr;
	m_pMoveModeDeepOption = nullptr;
	m_pMoveModeGestOption = nullptr;
	m_pMoveModeBtn = nullptr;
}

CMoveControlPage::~CMoveControlPage()
{

}

void CMoveControlPage::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	m_pPaintManager = pPaintMgr;
}

void CMoveControlPage::InitWindow()
{
	m_pMoveControlPanel = static_cast<CHorizontalLayoutUI*>(m_pPaintManager->FindControl(_T("moveControlPanel")));

	m_pSpeedSlider = static_cast<CSliderUI*>(m_pMoveControlPanel->FindSubControl(_T("speedSlider")));
	m_pSpeedBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("speedBtn")));
	m_pSpeedRestBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("speedRestBtn")));
	m_pSpeedEdit = static_cast<CEditUI*>(m_pMoveControlPanel->FindSubControl(_T("speedEdit")));

	m_pDeepSlider = static_cast<CSliderUI*>(m_pMoveControlPanel->FindSubControl(_T("deepSlider")));
	m_pDeepBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("deepBtn")));
	m_pDeepRestBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("deepRestBtn")));
	m_pDeepEdit = static_cast<CEditUI*>(m_pMoveControlPanel->FindSubControl(_T("deepEdit")));

	m_pPitchAngleSlider = static_cast<CSliderUI*>(m_pMoveControlPanel->FindSubControl(_T("pitchAngleSlider")));
	m_pPitchAngleBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("pitchAngleBtn")));
	m_pPitchAngleRestBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("pitchAngleRestBtn")));
	m_pPitchAngleEdit = static_cast<CEditUI*>(m_pMoveControlPanel->FindSubControl(_T("pitchAngleEdit")));

	m_pRollAngleSlider = static_cast<CSliderUI*>(m_pMoveControlPanel->FindSubControl(_T("rollAngleSlider")));
	m_pRollAngleBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("rollAngleBtn")));
	m_pRollAngleRestBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("rollAngleRestBtn")));
	m_pRollAngleEdit = static_cast<CEditUI*>(m_pMoveControlPanel->FindSubControl(_T("rollAngleEdit")));

	m_pHeadAngleSlider = static_cast<CSliderUI*>(m_pMoveControlPanel->FindSubControl(_T("headAngleSlider")));
	m_pHeadAngleBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("headAngleBtn")));
	m_pHeadAngleRestBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("headAngleRestBtn")));
	m_pHeadAngleEdit = static_cast<CEditUI*>(m_pMoveControlPanel->FindSubControl(_T("headAngleEdit")));

	m_pDiffControlOption = static_cast<COptionUI*>(m_pMoveControlPanel->FindSubControl(_T("diffControlOption")));
	m_pGesControlOption = static_cast<COptionUI*>(m_pMoveControlPanel->FindSubControl(_T("gesControlOption")));
	m_pControlModeBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("controlModeBtn")));

	m_pIneNaviOption = static_cast<COptionUI*>(m_pMoveControlPanel->FindSubControl(_T("ineNaviOption")));
	m_pGeoNaviOption = static_cast<COptionUI*>(m_pMoveControlPanel->FindSubControl(_T("geoNaviOption")));
	m_pNaviModeBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("naviModeBtn")));

	m_pMoveModeStopOption = static_cast<COptionUI*>(m_pMoveControlPanel->FindSubControl(_T("moveModeStopOption")));
	m_pMoveModeDeepOption = static_cast<COptionUI*>(m_pMoveControlPanel->FindSubControl(_T("moveModeDeepOption")));
	m_pMoveModeGestOption = static_cast<COptionUI*>(m_pMoveControlPanel->FindSubControl(_T("moveModeGestOption")));
	m_pMoveModeBtn = static_cast<CButtonUI*>(m_pMoveControlPanel->FindSubControl(_T("moveModeBtn")));
}

void CMoveControlPage::InitUUV( IUUVObject* pUUV )
{
	m_pUUV = pUUV;
}

void CMoveControlPage::OnClick( TNotifyUI& msg )
{
	if (m_pUUV == nullptr)
	{
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("UUVÊµÀýÎª¿Õ"));
		return;
	}

	if (msg.pSender == m_pSpeedBtn)
	{
		this->ClickSpeedBtn();
	}
	else if (msg.pSender == m_pSpeedRestBtn)
	{
		this->ClickSpeedRestBtn();
	}
	else if (msg.pSender == m_pDeepBtn)
	{
		this->ClickDeepBtn();
	}
	else if (msg.pSender == m_pDeepRestBtn)
	{
		this->ClickDeepRestBtn();
	}
	else if (msg.pSender == m_pPitchAngleBtn)
	{
		this->ClickPitchBtn();
	}
	else if (msg.pSender == m_pPitchAngleRestBtn)
	{
		this->ClickPitchRestBtn();
	}
	else if (msg.pSender == m_pRollAngleBtn)
	{
		this->ClickRollBtn();
	}
	else if (msg.pSender == m_pRollAngleRestBtn)
	{
		this->ClickRollRestBtn();
	}
	else if (msg.pSender == m_pHeadAngleBtn)
	{
		this->ClickHeadBtn();
	}
	else if (msg.pSender == m_pHeadAngleRestBtn)
	{
		this->ClickHeadRestBtn();
	}
	else if (msg.pSender == m_pControlModeBtn)
	{
		this->ClickCtrlModeBtn();
	}
	else if (msg.pSender == m_pNaviModeBtn)
	{
		this->ClickNaviModeBtn();
	}
	else if (msg.pSender == m_pMoveModeBtn)
	{
		this->ClickMoveModeBtn();
	}
}

void CMoveControlPage::OnValueChanged( TNotifyUI& msg )
{
	if (msg.pSender == m_pSpeedSlider)
	{
		m_pSpeedEdit->SetText(CStringUtil::Format(_T("%d"), m_pSpeedSlider->GetValue()).c_str());
		this->ClickSpeedBtn();
	}
	else if (msg.pSender == m_pDeepSlider)
	{
		m_pDeepEdit->SetText(CStringUtil::Format(_T("%d"), m_pDeepSlider->GetValue()).c_str());
		this->ClickDeepBtn();
	}
	else if (msg.pSender == m_pPitchAngleSlider)
	{
		m_pPitchAngleEdit->SetText(CStringUtil::Format(_T("%d"), m_pPitchAngleSlider->GetValue()).c_str());
		this->ClickPitchBtn();
	}
	else if (msg.pSender == m_pRollAngleSlider)
	{
		m_pRollAngleEdit->SetText(CStringUtil::Format(_T("%d"), m_pRollAngleSlider->GetValue()).c_str());
		this->ClickRollBtn();
	}
	else if (msg.pSender == m_pHeadAngleSlider)
	{
		m_pHeadAngleEdit->SetText(CStringUtil::Format(_T("%d"), m_pHeadAngleSlider->GetValue()).c_str());
		this->ClickHeadBtn();
	}
}
void CMoveControlPage::OnSelectChanged( TNotifyUI& msg )
{
	if (msg.pSender == m_pDiffControlOption)
	{
		m_pHeadAngleSlider->SetMinValue(-100);
		m_pHeadAngleSlider->SetMaxValue(100);
		m_pHeadAngleSlider->SetValue(0);
		m_pHeadAngleSlider->SetToolTip(_T("-100~100"));
	}
	else if (msg.pSender == m_pGesControlOption)
	{
		m_pHeadAngleSlider->SetMinValue(-1800);
		m_pHeadAngleSlider->SetMaxValue(1800);
		m_pHeadAngleSlider->SetValue(0);
		m_pHeadAngleSlider->SetToolTip(_T("-1800~1800"));
	}
}

void CMoveControlPage::OnTextChanged( TNotifyUI& msg )
{
	if (msg.pSender == m_pSpeedEdit)
	{
		//m_pSpeedSlider->SetValue(CStringUtil::ToInt(m_pSpeedEdit->GetText().GetData()));
	}
}

void CMoveControlPage::OnReturn( TNotifyUI& msg )
{
	if (msg.pSender == m_pSpeedEdit)
	{
		int nValue = CStringUtil::ToInt(m_pSpeedEdit->GetText().GetData());
		if (nValue >= m_pSpeedSlider->GetMinValue() && nValue <= m_pSpeedSlider->GetMaxValue())
		{
			m_pSpeedSlider->SetValue(nValue);
			this->ClickSpeedBtn();
		}
	}
	else if (msg.pSender == m_pDeepEdit)
	{
		int nValue = CStringUtil::ToInt(m_pDeepEdit->GetText().GetData());
		if (nValue >= m_pDeepSlider->GetMinValue() && nValue <= m_pDeepSlider->GetMaxValue())
		{
			m_pDeepSlider->SetValue(nValue);
			this->ClickDeepBtn();
		}
	}
	else if (msg.pSender == m_pPitchAngleEdit)
	{
		int nValue = CStringUtil::ToInt(m_pPitchAngleEdit->GetText().GetData());
		if (nValue >= m_pPitchAngleSlider->GetMinValue() && nValue <= m_pPitchAngleSlider->GetMaxValue())
		{
			m_pPitchAngleSlider->SetValue(nValue);
			this->ClickPitchBtn();
		}
	}
	else if (msg.pSender == m_pRollAngleEdit)
	{
		int nValue = CStringUtil::ToInt(m_pRollAngleEdit->GetText().GetData());
		if (nValue >= m_pRollAngleSlider->GetMinValue() && nValue <= m_pRollAngleSlider->GetMaxValue())
		{
			m_pRollAngleSlider->SetValue(nValue);
			this->ClickRollBtn();
		}
	}
	else if (msg.pSender == m_pHeadAngleEdit)
	{
		int nValue = CStringUtil::ToInt(m_pHeadAngleEdit->GetText().GetData());
		if (nValue >= m_pHeadAngleSlider->GetMinValue() && nValue <= m_pHeadAngleSlider->GetMaxValue())
		{
			m_pHeadAngleSlider->SetValue(nValue);
			this->ClickHeadBtn();
		}
	}
}

void CMoveControlPage::ClickSpeedBtn()
{
	int nErrno = ERR_SUCCESS;
	short nSpeed = m_pSpeedSlider->GetValue();

	if(!m_pUUV->UUV_Set(UUV_FORWARD_BACKWARD_SPEED_SET, &nSpeed))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃÇ°ºóËÙ¶ÈÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CMoveControlPage::ClickDeepBtn()
{
	int nErrno = ERR_SUCCESS;
	short nDeep = m_pDeepSlider->GetValue();

	if(!m_pUUV->UUV_Set(UUV_TARGET_DEPTH_SET, &nDeep))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃÄ¿±êÉî¶ÈÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}
}

void CMoveControlPage::ClickPitchBtn()
{
	int nErrno = ERR_SUCCESS;
	short nPitch = m_pPitchAngleSlider->GetValue();

	if(!m_pUUV->UUV_Set(UUV_ATT_PITCH_SET, &nPitch))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃ¸©ÑöÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CMoveControlPage::ClickRollBtn()
{
	int nErrno = ERR_SUCCESS;
	short nRoll = m_pRollAngleSlider->GetValue();
	if(!m_pUUV->UUV_Set(UUV_ATT_ROLL_SET, &nRoll))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃºá¹ö½ÇÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}
}

void CMoveControlPage::ClickMoveModeBtn()
{
	int nErrno = ERR_SUCCESS;
	unsigned char move_pattrn=0;
	if (m_pMoveModeStopOption->IsSelected())
	{
		move_pattrn=0;
	}
	else if (m_pMoveModeDeepOption->IsSelected())
	{
		move_pattrn=2;
	}
	else if (m_pMoveModeGestOption->IsSelected())
	{
		move_pattrn = 0xff;
	}

	if(!m_pUUV->UUV_Set(UUV_WORK_PATTERN_SET, &move_pattrn))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃ¹¤×÷Ä£Ê½Ê§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CMoveControlPage::ClickHeadBtn()
{
	int nErrno = ERR_SUCCESS;
	short nHead = m_pHeadAngleSlider->GetValue();

	if(!m_pUUV->UUV_Set(UUV_ATT_YAW_SET, &nHead))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃ¸©ÑöÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}
}

void CMoveControlPage::ClickCtrlModeBtn()
{
	int nErrno = ERR_SUCCESS;
	unsigned char yaw_control=0;
	if (m_pDiffControlOption->IsSelected())
	{
		yaw_control=0;
	}
	else if (m_pGesControlOption->IsSelected())
	{
		yaw_control=1;
	}

	if(!m_pUUV->UUV_Set(UUV_YAW_CONTROL_SET, &yaw_control))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃº½Ïò¿ØÖÆÊ§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CMoveControlPage::ClickNaviModeBtn()
{
	int nErrno = ERR_SUCCESS;
	unsigned char navigate_mode=0;
	if (m_pIneNaviOption->IsSelected())
	{
		navigate_mode=0;
	}
	else if (m_pGeoNaviOption->IsSelected())
	{
		navigate_mode=1;
	}
	if(!m_pUUV->UUV_Set(UUV_YAW_NAVIGATES_SET, &navigate_mode))
	{
		nErrno = m_pUUV->UUV_GetErrno();
		LogMsg(WT_EVENTLOG_ERROR_TYPE, _T("ÉèÖÃµ¼º½Ä£Ê½Ê§°Ü£¬´íÎóÂë %d"), nErrno);
	}

}

void CMoveControlPage::ClickSpeedRestBtn()
{
	m_pSpeedSlider->SetValue(0);
	m_pSpeedEdit->SetText(_T("0"));
	this->ClickSpeedBtn();
}

void CMoveControlPage::ClickDeepRestBtn()
{
	m_pDeepSlider->SetValue(0);
	m_pDeepEdit->SetText(_T("0"));
	this->ClickDeepBtn();
}

void CMoveControlPage::ClickPitchRestBtn()
{
	m_pPitchAngleSlider->SetValue(0);
	m_pPitchAngleEdit->SetText(_T("0"));
	this->ClickPitchBtn();
}

void CMoveControlPage::ClickRollRestBtn()
{
	m_pRollAngleSlider->SetValue(0);
	m_pRollAngleEdit->SetText(_T("0"));
	this->ClickRollBtn();
}

void CMoveControlPage::ClickHeadRestBtn()
{
	m_pHeadAngleSlider->SetValue(0);
	m_pHeadAngleEdit->SetText(_T("0"));
	this->ClickHeadBtn();
}
