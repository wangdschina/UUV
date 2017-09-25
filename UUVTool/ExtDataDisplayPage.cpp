#include "stdafx.h"
#include "ExtDataDisplayPage.h"

DUI_BEGIN_MESSAGE_MAP(CExtDataDisplayPage, CNotifyPump)
DUI_END_MESSAGE_MAP()

CExtDataDisplayPage::CExtDataDisplayPage(void) : 
	m_pPaintManager(nullptr), 
	m_pExtDataDisplayPanel(nullptr), 
	m_pRelativedDistEdit(nullptr), 
	m_pRelativedDirectEdit(nullptr), 
	m_pRelativedPosNorthEdit(nullptr), 
	m_pRelativedPosEastEdit(nullptr), 
	m_pLonEdit(nullptr), 
	m_pLatEdit(nullptr)
{
}


CExtDataDisplayPage::~CExtDataDisplayPage(void)
{
}

void CExtDataDisplayPage::SetPaintMagager( CPaintManagerUI* pPaintMgr )
{
	this->m_pPaintManager = pPaintMgr;
}

void CExtDataDisplayPage::InitWindow()
{
	ASSERT(m_pPaintManager != nullptr);
	m_pExtDataDisplayPanel = static_cast<CHorizontalLayoutUI*>(m_pPaintManager->FindControl(_T("extDataDisplayPanel")));
	ASSERT(m_pExtDataDisplayPanel != nullptr);

	m_pRelativedDistEdit = static_cast<CEditUI*>(m_pExtDataDisplayPanel->FindSubControl(_T("relativedDistEdit")));
	m_pRelativedDirectEdit = static_cast<CEditUI*>(m_pExtDataDisplayPanel->FindSubControl(_T("relativedDirectEdit")));
	m_pRelativedPosNorthEdit = static_cast<CEditUI*>(m_pExtDataDisplayPanel->FindSubControl(_T("relativedPosNorthEdit")));
	m_pRelativedPosEastEdit = static_cast<CEditUI*>(m_pExtDataDisplayPanel->FindSubControl(_T
("relativedPosEastEdit")));
	m_pLonEdit = static_cast<CEditUI*>(m_pExtDataDisplayPanel->FindSubControl(_T("lonEdit")));
	m_pLatEdit = static_cast<CEditUI*>(m_pExtDataDisplayPanel->FindSubControl(_T("latEdit")));
}

void CExtDataDisplayPage::ShowData( UUV_RESULT pResult )
{
	PUUV_USBL_INFO pusbl_info = static_cast<PUUV_USBL_INFO>(pResult);
	ASSERT(pusbl_info != nullptr);

	m_pRelativedDistEdit->SetText(CStringUtil::Format(_T("%f"), pusbl_info->uuv_ralatived_distannce).c_str());
	m_pRelativedDirectEdit->SetText(CStringUtil::Format(_T("%f"), pusbl_info->uuv_ralatived_direction).c_str());
	m_pRelativedPosNorthEdit->SetText(CStringUtil::Format(_T("%f"), pusbl_info->uuv_ralatived_pos_north).c_str());
	m_pRelativedPosEastEdit->SetText(CStringUtil::Format(_T("%f"), pusbl_info->uuv_ralatived_pos_east).c_str());
	m_pLonEdit->SetText(CStringUtil::Format(_T("%f"), pusbl_info->uuv_longitude).c_str());
	m_pLatEdit->SetText(CStringUtil::Format(_T("%f"), pusbl_info->uuv_latitude).c_str());
}
