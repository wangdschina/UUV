#include "stdafx.h"
#include "DataDisplayPage.h"
#include "MainWnd.h"

//////////////////////////////////////////////////////////////////////////
///
DUI_BEGIN_MESSAGE_MAP(CDataDisplayPage, CNotifyPump)
DUI_END_MESSAGE_MAP()

CDataDisplayPage::CDataDisplayPage()
{
	m_pPaintManager = nullptr;
	m_pDataDisplayPanel = nullptr;

	m_pRollEdit = nullptr;
	m_pPitchEdit = nullptr;
	m_pHeadEdit = nullptr;
	m_pSpeedFrontBackEdit = nullptr;
	m_pSpeedTraverseEdit = nullptr;
	m_pSpeedUpDownEdit = nullptr;
	m_pWorkModeEdit = nullptr;
	m_pControlModeEdit = nullptr;
	m_pNaviModeEdit = nullptr;
	m_pDeepCurEdit = nullptr;
	m_pDeepTarEdit = nullptr;
	m_pBoardDevPowerEdit = nullptr;
	m_pPowerConsumEdit= nullptr;
	m_pTempEdit = nullptr;
	m_pSaliEdit = nullptr;
	m_pPressEdit = nullptr;
	m_pHumidityEdit = nullptr;
	m_pCloudPitchEdit = nullptr;
	m_pCloudRotateEdit = nullptr;
	m_pCameraFocusEdit = nullptr;
	m_pCameraZoomEdit = nullptr;
	m_pLigthLeftEdit = nullptr;
	m_pLightRightEdit = nullptr;
	m_pLaserEdit = nullptr;
	m_pVLeftFrontEdit = nullptr;
	m_pVLeftBackEdit = nullptr;
	m_pVRightBackEdit = nullptr;
	m_pVRightFrontEdit = nullptr;
	m_pHLeftEdit = nullptr;
	m_pHRightEdit = nullptr;
	m_pManipStateEdit = nullptr;
	m_pIlluTensorEdit = nullptr;
	m_pInputVolEdit = nullptr;
	m_pInputElecEdit = nullptr;
	m_pBatteryVolEdit = nullptr;
	m_pLoadElecEdit = nullptr;
	m_pSocStateEdit = nullptr;
	m_pSysPowerStateEdit = nullptr;
	m_pTotalPowerEdit = nullptr;
}

CDataDisplayPage::~CDataDisplayPage()
{
	
}

void CDataDisplayPage::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	m_pPaintManager = pPaintMgr;
}

void CDataDisplayPage::InitWindow()
{
	m_pDataDisplayPanel = static_cast<CHorizontalLayoutUI*>(m_pPaintManager->FindControl(_T("dataDisplayPanel")));

	m_pRollEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("rollEdit")));
	m_pPitchEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("pitchEdit")));
	m_pHeadEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("headEdit")));
	m_pSpeedFrontBackEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("speedFrontBackEdit")));
	m_pSpeedTraverseEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("speedTraverseEdit")));
	m_pSpeedUpDownEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("speedUpDownEdit")));
	m_pWorkModeEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("workModeEdit")));
	m_pControlModeEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("controlModeEdit")));
	m_pNaviModeEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("naviModeEdit")));
	m_pDeepCurEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("deepCurEdit")));
	m_pDeepTarEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("deepTarEdit")));
	m_pBoardDevPowerEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("boardDevPowerEdit")));
	m_pPowerConsumEdit= static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("powerConsumEdit")));
	m_pTempEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("tempEdit")));
	m_pSaliEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("saliEdit")));
	m_pPressEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("pressEdit")));
	m_pHumidityEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("humidityEdit")));
	m_pCloudPitchEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("cloudPitchEdit")));
	m_pCloudRotateEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("cloudRotateEdit")));
	m_pCameraFocusEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("cameraFocusEdit")));
	m_pCameraZoomEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("cameraZoomEdit")));
	m_pLigthLeftEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("ligthLeftEdit")));
	m_pLightRightEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("lightRightEdit")));
	m_pLaserEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("laserEdit")));
	m_pVLeftFrontEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("vleftFrontEdit")));
	m_pVLeftBackEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("vleftBackEdit")));
	m_pVRightBackEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("vrightBackEdit")));
	m_pVRightFrontEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("vrightFrontEdit")));
	m_pHLeftEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("hleftEdit")));
	m_pHRightEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("hrightEdit")));
	m_pManipStateEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("manipStateEdit")));
	m_pIlluTensorEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("illuTensorEdit")));
	m_pInputVolEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("inputVolEdit")));
	m_pInputElecEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("inputElecEdit")));
	m_pBatteryVolEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("batteryVolEdit")));
	m_pLoadElecEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("loadElecEdit")));
	m_pSocStateEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("socStateEdit")));
	m_pSysPowerStateEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("sysPowerStateEdit")));
	m_pTotalPowerEdit = static_cast<CEditUI*>(m_pDataDisplayPanel->FindSubControl(_T("totalPowerEdit")));
}

void CDataDisplayPage::ShowData( UUV_RESULT pResult )
{
	PUUV_STAT prov_status=(PUUV_STAT)pResult;
	m_pRollEdit->SetText(CStringUtil::Format(_T("%0.1f"), prov_status->ATT.roll*0.1).c_str());
	m_pPitchEdit->SetText(CStringUtil::Format(_T("%0.1f"), prov_status->ATT.pitch*0.1).c_str());
	m_pHeadEdit->SetText(CStringUtil::Format(_T("%0.1f"), prov_status->ATT.yaw*0.1).c_str());
	m_pSpeedFrontBackEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->ATT.forwar_backwar).c_str());
	m_pWorkModeEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->ATT.operat_mode).c_str());
	m_pControlModeEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->ATT.yewmode&0x01).c_str());
	m_pNaviModeEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->ATT.yewmode&0x02).c_str());
	m_pDeepTarEdit->SetText(CStringUtil::Format(_T("%0.2f"), prov_status->ATT.depth_aim*0.01).c_str());
	m_pTempEdit->SetText(CStringUtil::Format(_T("%0.2f"), prov_status->Temperature*0.01).c_str());
	m_pSaliEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->Salinity).c_str());
	m_pDeepCurEdit->SetText(CStringUtil::Format(_T("%0.2f"), prov_status->depth*0.01).c_str());
	m_pBoardDevPowerEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->power).c_str());
	m_pPowerConsumEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->power).c_str());
	m_pPressEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->pressure_in).c_str());
	m_pHumidityEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->humidity_in).c_str());
	m_pCloudPitchEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->camdata.elevation).c_str());
	m_pCloudRotateEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->camdata.rotate).c_str());
	m_pCameraFocusEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->camdata.focus).c_str());
	m_pCameraZoomEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->camdata.zoom).c_str());
	m_pLigthLeftEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->camdata.leftlight_lum).c_str());
	m_pLightRightEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->camdata.rightlight_lum).c_str());
	m_pVLeftFrontEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->motor.l_f_v_motor).c_str());
	m_pVLeftBackEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->motor.l_b_v_motor).c_str());
	m_pVRightBackEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->motor.r_b_v_motor).c_str());
	m_pVRightFrontEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->motor.r_f_v_motor).c_str());
	m_pHLeftEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->motor.l_h_motor).c_str());
	m_pHRightEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->motor.r_h_motor).c_str());
	m_pManipStateEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->extraman.switching).c_str());
	m_pInputVolEdit->SetText(CStringUtil::Format(_T("%0.1f"), prov_status->p_inf.Voltage_IN*0.1).c_str());
	m_pInputElecEdit->SetText(CStringUtil::Format(_T("%0.2f"), prov_status->p_inf.Current_IN*0.01).c_str());
	m_pBatteryVolEdit->SetText(CStringUtil::Format(_T("%0.2f"), prov_status->p_inf.Voltage_BATT*0.01).c_str());
	m_pLoadElecEdit->SetText(CStringUtil::Format(_T("%0.2f"), prov_status->p_inf.Current_OUT*0.01).c_str());
	m_pSysPowerStateEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->p_inf.SOC).c_str());
	m_pTotalPowerEdit->SetText(CStringUtil::Format(_T("%d"), prov_status->p_inf.Power_SYS).c_str());
	m_pSocStateEdit->SetText(_T("0"));
	
}