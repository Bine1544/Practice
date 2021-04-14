#include "pch.h"
#include <Windows.h>
#include "DDraw.h"

IDirectDraw* g_pDD = nullptr;
HWND g_hWndForDDraw = nullptr;
BOOL InitializeDDraw(HWND hWnd)
{
	BOOL	bResult = FALSE;
	
	g_hWndForDDraw = hWnd;
	
	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;
	
	
	if (DD_OK != DirectDrawCreate(nullptr, &g_pDD, nullptr))
	{
		MessageBox(hWnd, L"Fail to Create DirectDraw", L"Error", MB_OK);
		goto lb_return;
	}
	
	/*
	if (DD_OK != m_pDD->QueryInterface(IID_IDirectDraw7, (LPVOID*)&m_pDD7))
	{
		MessageBox(hWnd, L"Fail to Create DirectDraw 4", L"Error", MB_OK);
		goto lb_return;
	}

	HRESULT hr = m_pDD7->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"Failed to Set CooperativeLevel", L"ERROR", MB_OK);
		goto lb_return;
	}



	// Create the primary surface.
	hr = m_pDD7->CreateSurface(&ddsd, &m_pDDPrimary, nullptr);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"Failed to CreateSurface", L"ERROR", MB_OK);
		goto lb_return;
	}
	// Create a clipper object which handles all our clipping for cases when
	// our window is partially obscured by other windows. This is not needed
	// for apps running in fullscreen mode.

	hr = m_pDD->CreateClipper(0, &m_pClipper, nullptr);
	if (FAILED(hr))
	{
		MessageBox(m_hWnd, L"Failed to Create Clipper", L"ERROR", MB_OK);
		goto lb_return;
	}
	// Associate the clipper with our window. Note that, afterwards, the
	// clipper is internally referenced by the primary surface, so it is safe
	// to release our local reference to it.
	m_pClipper->SetHWnd(0, hWnd);
	m_pDDPrimary->SetClipper(m_pClipper);

	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;

	OnUpdateWindowPos();

	DWORD dwWidth = m_rcWindow.right - m_rcWindow.left;
	DWORD dwHeight = m_rcWindow.bottom - m_rcWindow.top;

	if (!CreateBackBuffer(dwWidth, dwHeight))
	{
#ifdef _DEBUG
		__debugbreak();
#endif
		goto lb_return;
	}
	*/
	bResult = TRUE;

lb_return:
	return bResult;

}

void CleanupDDraw()
{
	if (g_pDD)
	{
		g_pDD->Release();
		g_pDD = nullptr;
	}
/*	CleanupBackBuffer();

	if (m_pClipper)
	{
		m_pClipper->Release();
		m_pClipper = nullptr;
	}
	if (m_pDDPrimary)
	{
		m_pDDPrimary->Release();
		m_pDDPrimary = nullptr;
	}
	if (m_pDD7)
	{
		m_pDD7->Release();
		m_pDD7 = nullptr;
	}
	
	*/
}