#pragma once

const int MAX_MEMORY_POOL = 16;

class CDirectUtility
{
public:
	CDirectUtility(void);
	~CDirectUtility(void);

	bool InitDirect3D(HWND hwnd, ULONG ulWidth, ULONG ulHeight);
	bool Render(UCHAR* pszData);
	void CleanUp(void);

private:
	HWND	m_hWnd;
	ULONG	m_ulPixWidth;
	ULONG	m_ulPixHeigth;

private:
	CRITICAL_SECTION		m_critial;

	IDirect3D9*				m_pDirect3D9;
	IDirect3DDevice9*		m_pDirect3DDevice;
	IDirect3DSurface9*		m_pDirect3DSurfaceRender;

	D3DPRESENT_PARAMETERS	m_d3dpp;

	RECT					m_rtViewport;
};

