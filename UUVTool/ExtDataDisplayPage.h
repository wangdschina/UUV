#pragma once

class CExtDataDisplayPage :	public CNotifyPump
{
public:
	CExtDataDisplayPage(void);
	~CExtDataDisplayPage(void);

public:
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);
	void InitWindow();
	void ShowData(UUV_RESULT pResult);

protected:
	DUI_DECLARE_MESSAGE_MAP()

private:
	CPaintManagerUI*		m_pPaintManager;
	CHorizontalLayoutUI*	m_pExtDataDisplayPanel;

	CEditUI*				m_pRelativedDistEdit;			//	相对基阵距离
	CEditUI*				m_pRelativedDirectEdit;			//	相对基阵角度
	CEditUI*				m_pRelativedPosNorthEdit;		//	相对基阵偏北
	CEditUI*				m_pRelativedPosEastEdit;		//	相对基阵偏东
	CEditUI*				m_pLonEdit			;			//	经度
	CEditUI*				m_pLatEdit;						//	纬度
};

