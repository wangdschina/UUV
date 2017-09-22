#pragma once

class CDataDisplayPage : public CNotifyPump
{
public:
	CDataDisplayPage();
	~CDataDisplayPage();

public:
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);
	void InitWindow();
	void ShowData(UUV_RESULT pResult);

protected:
	DUI_DECLARE_MESSAGE_MAP()

private:
	CPaintManagerUI*		m_pPaintManager;
	CHorizontalLayoutUI*	m_pDataDisplayPanel;

	CEditUI*				m_pRollEdit;			//	横滚角
	CEditUI*				m_pPitchEdit;			//	俯仰角
	CEditUI*				m_pHeadEdit;			//	航向角
	CEditUI*				m_pSpeedFrontBackEdit;	//	前后速度
	CEditUI*				m_pSpeedTraverseEdit;	//	横移速度
	CEditUI*				m_pSpeedUpDownEdit;		//	升降速度
	CEditUI*				m_pWorkModeEdit;		//	工作模式
	CEditUI*				m_pControlModeEdit;		//	控制模式
	CEditUI*				m_pNaviModeEdit;		//	导航模式
	CEditUI*				m_pDeepCurEdit;			//	当前深度
	CEditUI*				m_pDeepTarEdit;			//	目标深度
	CEditUI*				m_pBoardDevPowerEdit;	//	板载设备供电
	CEditUI*				m_pPowerConsumEdit;		//	板载设备供电
	CEditUI*				m_pTempEdit;			//	舱外温度
	CEditUI*				m_pSaliEdit;			//	盐度
	CEditUI*				m_pPressEdit;			//	舱内压力
	CEditUI*				m_pHumidityEdit;		//	舱内湿度
	CEditUI*				m_pCloudPitchEdit;		//	云台俯仰
	CEditUI*				m_pCloudRotateEdit;		//	云台旋转
	CEditUI*				m_pCameraFocusEdit;		//	镜头聚焦
	CEditUI*				m_pCameraZoomEdit;		//	镜头变焦
	CEditUI*				m_pLigthLeftEdit;		//	亮度左
	CEditUI*				m_pLightRightEdit;		//	亮度右
	CEditUI*				m_pLaserEdit;			//	激光
	CEditUI*				m_pVLeftFrontEdit;		//	0x50电机转速
	CEditUI*				m_pVLeftBackEdit;		//	0x51电机转速
	CEditUI*				m_pVRightBackEdit;		//	0x52电机转速
	CEditUI*				m_pVRightFrontEdit;		//	0x53电机转速
	CEditUI*				m_pHLeftEdit;			//	0x58电机转速
	CEditUI*				m_pHRightEdit;			//	0x59电机转速
	CEditUI*				m_pManipStateEdit;		//	机械手状态
	CEditUI*				m_pIlluTensorEdit;		//	照度传感器
	CEditUI*				m_pInputVolEdit;		//	输入电压
	CEditUI*				m_pInputElecEdit;		//	输入电流
	CEditUI*				m_pBatteryVolEdit;		//	电池电压
	CEditUI*				m_pLoadElecEdit;		//	负载电流
	CEditUI*				m_pSocStateEdit;		//	SOC状态
	CEditUI*				m_pSysPowerStateEdit;	//	系统电源状态
	CEditUI*				m_pTotalPowerEdit;		//	总功率
};

