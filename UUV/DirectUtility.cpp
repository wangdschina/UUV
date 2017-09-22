#include "stdafx.h"
#include "DirectUtility.h"

//const int MAX_PIX_WIDTH = 1920;
//const int MAX_PIX_HEIGTH = 1080;

//const int MAX_BUFF_LEN = MAX_PIX_WIDTH*MAX_PIX_HEIGTH*12/8;
/*	目前最大支持1080P,修改MAX_BUFF_LEN改变缓冲区大小	*/
//unsigned char buffer[MAX_BUFF_LEN];

CDirectUtility::CDirectUtility(void)
{
	m_hWnd = NULL;
	m_ulPixWidth = 0;
	m_ulPixHeigth = 0;

	m_pDirect3D9 = nullptr;
	m_pDirect3DDevice = nullptr;
	m_pDirect3DSurfaceRender = nullptr;
}


CDirectUtility::~CDirectUtility(void)
{
	
}

bool CDirectUtility::InitDirect3D( HWND hwnd, ULONG ulWidth, ULONG ulHeight )
{
	InitializeCriticalSection(&m_critial);
	this->CleanUp();

	m_pDirect3D9 = Direct3DCreate9( D3D_SDK_VERSION );
	if( m_pDirect3D9 == nullptr )
		return false;

	D3DCAPS9 caps;
	m_pDirect3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	/*int vp = 0;
	if(caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) 
	{
	vp = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	}
	else 
	{
	vp = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}*/

	ZeroMemory( &m_d3dpp, sizeof(m_d3dpp) );
	m_d3dpp.Windowed = TRUE;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	
	m_d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	//m_d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;


	GetClientRect(hwnd, &m_rtViewport);

	HRESULT lRet = m_pDirect3D9->CreateDevice( D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, 
		hwnd, 
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, 
		&m_d3dpp, 
		&m_pDirect3DDevice );
	if(FAILED(lRet))
		return false;

	lRet = m_pDirect3DDevice->CreateOffscreenPlainSurface(
		ulWidth, ulHeight,
		(D3DFORMAT)MAKEFOURCC('Y', 'V', '1', '2'),
		D3DPOOL_DEFAULT,
		&m_pDirect3DSurfaceRender,
		NULL);
	if(FAILED(lRet))
		return false;

	m_hWnd = hwnd;
	m_ulPixHeigth = ulHeight;
	m_ulPixWidth = ulWidth;

	return true;
}

bool CDirectUtility::Render( UCHAR* pszData )
{
	if(m_pDirect3DSurfaceRender == nullptr)
		return false;
	D3DLOCKED_RECT d3d_rect;
	HRESULT lRet = m_pDirect3DSurfaceRender->LockRect(&d3d_rect, NULL, D3DLOCK_DONOTWAIT);
	if(FAILED(lRet))
		return false;

	//byte *pSrc = buffer;
	byte *pSrc = pszData;
	byte * pDest = (BYTE *)d3d_rect.pBits;
	int stride = d3d_rect.Pitch;
	unsigned long i = 0;

	//Copy Data
	for(i = 0; i < m_ulPixHeigth; i++)
	{
		memcpy(pDest + i * stride, pSrc + i * m_ulPixWidth, m_ulPixWidth);
	}
	for(i = 0; i < m_ulPixHeigth/2; i++)
	{
		memcpy(pDest + stride * m_ulPixHeigth + i * stride / 2, pSrc + m_ulPixWidth * m_ulPixHeigth + m_ulPixWidth * m_ulPixHeigth / 4 + i * m_ulPixWidth / 2, m_ulPixWidth / 2);
	}
	for(i = 0; i < m_ulPixHeigth/2; i++)
	{
		memcpy(pDest + stride * m_ulPixHeigth + stride * m_ulPixHeigth / 4 + i * stride / 2, pSrc + m_ulPixWidth * m_ulPixHeigth + i * m_ulPixWidth / 2, m_ulPixWidth / 2);
	}

	lRet = m_pDirect3DSurfaceRender->UnlockRect();
	if(FAILED(lRet))
		return false;

	if (m_pDirect3DDevice == nullptr)
		return false;

	m_pDirect3DDevice->Clear( 0, nullptr, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0 );
	m_pDirect3DDevice->BeginScene();
	IDirect3DSurface9 * pBackBuffer = nullptr;

	m_pDirect3DDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pBackBuffer);
	m_pDirect3DDevice->StretchRect(m_pDirect3DSurfaceRender, nullptr, pBackBuffer, &m_rtViewport, D3DTEXF_LINEAR);
	m_pDirect3DDevice->EndScene();
	m_pDirect3DDevice->Present( NULL, NULL, NULL, NULL );

	return true;
}

void CDirectUtility::CleanUp( void )
{
	EnterCriticalSection(&m_critial);

	if(m_pDirect3DSurfaceRender)
	{
		m_pDirect3DSurfaceRender->Release();
		m_pDirect3DSurfaceRender = nullptr;
	}
	if(m_pDirect3DDevice)
	{
		m_pDirect3DDevice->Release();
		m_pDirect3DDevice = nullptr;
	}
	if(m_pDirect3D9)
	{
		m_pDirect3D9->Release();
		m_pDirect3D9 = nullptr;
	}

	LeaveCriticalSection(&m_critial);
}