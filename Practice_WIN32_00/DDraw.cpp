#include "pch.h"
#include <Windows.h>
#include "DDraw.h"

IDirectDraw7* g_pDD7 = nullptr;
IDirectDrawSurface7* g_pDDPrimary = nullptr;
IDirectDrawSurface7* g_pDDBack = nullptr;
IDirectDrawClipper* g_pClipper = nullptr;
IDirectDraw* g_pDD = nullptr;
HWND g_hWndForDDraw = nullptr;
RECT g_rcWindow = {};
DWORD g_dwWidth = 0;
DWORD g_dwHeight = 0;
int g_iCursorX = 0;
int g_iCursorY = 0;

void SetDDrawCursorPos(int x, int y)
{
	g_iCursorX = x+4;
	g_iCursorY = y;
}
void MoveLeft()
{
	g_iCursorX--;
}
void MoveRight()
{
	g_iCursorX++;
}
void MoveUp()
{
	g_iCursorY--;
}

void MoveDown()
{
	g_iCursorY++;

}
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
	
	
	if (DD_OK != g_pDD->QueryInterface(IID_IDirectDraw7, (LPVOID*)&g_pDD7))
	{
		MessageBox(hWnd, L"Fail to Create DirectDraw 4", L"Error", MB_OK);
		goto lb_return;
	}
	
	HRESULT hr = g_pDD7->SetCooperativeLevel(hWnd, DDSCL_NORMAL);
	if (FAILED(hr))
	{
		MessageBox(g_hWndForDDraw, L"Failed to Set CooperativeLevel", L"ERROR", MB_OK);
		goto lb_return;
	}
	


	// Create the primary surface.
	hr = g_pDD7->CreateSurface(&ddsd, &g_pDDPrimary, nullptr);
	if (FAILED(hr))
	{
		MessageBox(g_hWndForDDraw, L"Failed to CreateSurface", L"ERROR", MB_OK);
		goto lb_return;
	}
	
	// Create a clipper object which handles all our clipping for cases when
	// our window is partially obscured by other windows. This is not needed
	// for apps running in fullscreen mode.

	hr = g_pDD->CreateClipper(0, &g_pClipper, nullptr);
	if (FAILED(hr))
	{
		MessageBox(g_hWndForDDraw, L"Failed to Create Clipper", L"ERROR", MB_OK);
		goto lb_return;
	}
	// Associate the clipper with our window. Note that, afterwards, the
	// clipper is internally referenced by the primary surface, so it is safe
	// to release our local reference to it.
	g_pClipper->SetHWnd(0, hWnd);
	g_pDDPrimary->SetClipper(g_pClipper);
	
	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;

	UpdateBltRect();
	
	DWORD dwWidth = g_rcWindow.right - g_rcWindow.left;
	DWORD dwHeight = g_rcWindow.bottom - g_rcWindow.top;

	if (!CreateBackBuffer(dwWidth, dwHeight))
	{
#ifdef _DEBUG
		__debugbreak();
#endif
		goto lb_return;
	}
	
	bResult = TRUE;

lb_return:
	return bResult;

}

BOOL CreateBackBuffer(DWORD dwWidth, DWORD dwHeight)
{
	BOOL	bResult = FALSE;

	DDSURFACEDESC2 ddsd = {};
	ddsd.dwSize = sizeof(DDSURFACEDESC2);
	ddsd.dwFlags = DDSD_WIDTH | DDSD_HEIGHT | DDSD_CAPS;
	ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
	ddsd.dwWidth = dwWidth;
	ddsd.dwHeight = dwHeight;

	HRESULT hr = g_pDD7->CreateSurface(&ddsd, &g_pDDBack, nullptr);
	if (FAILED(hr))
	{
		MessageBox(g_hWndForDDraw, L"Failed to Create Surface", L"ERROR", MB_OK);
		goto lb_return;
	}
	g_pDDBack->GetSurfaceDesc(&ddsd);
	g_dwWidth = ddsd.dwWidth;
	g_dwHeight = ddsd.dwHeight;
	bResult = TRUE;
lb_return:
	return bResult;
}
void SetDDrawPixel(int x, int y, DWORD dwColor)
{
	DDSURFACEDESC2 ddsc;
	memset(&ddsc, 0, sizeof(DDSURFACEDESC2));
	ddsc.dwSize = sizeof(DDSURFACEDESC2);


	g_pDDBack->Lock(nullptr, &ddsc, DDLOCK_WAIT | DDLOCK_WRITEONLY, nullptr);

	char* pDest = (char*)ddsc.lpSurface + y * ddsc.lPitch + x * 4;
	*(DWORD*)pDest = dwColor;// 0xfff0f000;

	g_pDDBack->Unlock(nullptr);
}
void ClearBackbuffer()
{
	DDSURFACEDESC2 ddsc;
	memset(&ddsc, 0, sizeof(DDSURFACEDESC2));
	ddsc.dwSize = sizeof(DDSURFACEDESC2);

	g_pDDBack->Lock(nullptr, &ddsc, DDLOCK_WAIT | DDLOCK_WRITEONLY, nullptr);

	for (DWORD y = 0; y < ddsc.dwHeight; y++)
	{
		memset((char*)ddsc.lpSurface + y * ddsc.lPitch, 0, 4 * ddsc.dwWidth);
	}
	g_pDDBack->Unlock(nullptr);

}
void OnDraw()
{
	//ClearBackbuffer();

	DDSURFACEDESC2 ddsc;
	memset(&ddsc, 0, sizeof(DDSURFACEDESC2));
	ddsc.dwSize = sizeof(DDSURFACEDESC2);

	g_pDDBack->Lock(nullptr, &ddsc, DDLOCK_WAIT | DDLOCK_WRITEONLY, nullptr);
	
	for (DWORD y = 0; y < ddsc.dwHeight; y++)
	{
		memset((char*)ddsc.lpSurface + y * ddsc.lPitch, 0, 4 * ddsc.dwWidth);
	}

    
	DWORD dwColor = 0xff00ff00;

	if (g_iCursorX+1 < 0)
	{
		g_iCursorX = 0;
	}
	if (g_iCursorX+1 >= ddsc.dwWidth)
	{
		g_iCursorX = ddsc.dwWidth - 1;
	}
	if (g_iCursorY+1 < 0)
	{
		g_iCursorY = 0;
	}
	if (g_iCursorY+1 >= ddsc.dwHeight)
	{
		g_iCursorY = ddsc.dwHeight - 1;
	}
	char* pDest = (char*)ddsc.lpSurface + g_iCursorY * ddsc.lPitch + g_iCursorX * 4;
	*(DWORD*)pDest = dwColor;
	pDest = (char*)ddsc.lpSurface + g_iCursorY * ddsc.lPitch + (g_iCursorX + 1)* 4;
	*(DWORD*)pDest = dwColor;
	pDest = (char*)ddsc.lpSurface + (g_iCursorY+1) * ddsc.lPitch + g_iCursorX * 4;
	*(DWORD*)pDest = dwColor;
	pDest = (char*)ddsc.lpSurface + (g_iCursorY+1) * ddsc.lPitch + (g_iCursorX + 1) * 4;
	*(DWORD*)pDest = dwColor;
	/*
	for (DWORD y = 0; y < ddsc.dwHeight; y++)
	{
		for (DWORD x = 0; x < ddsc.dwWidth; x++)
		{
			DWORD r = rand() % 256;
			DWORD g = rand() % 256;
			DWORD b = rand() % 256;
			DWORD dwColor = (r << 16) | (g << 8) | (b << 0);
			char* pDest = (char*)ddsc.lpSurface + y*ddsc.lPitch + x*4;
			*(DWORD*)pDest = dwColor;// 0xfff0f000;
		}
	}*/
	g_pDDBack->Unlock(nullptr);

	g_pDDPrimary->Blt(&g_rcWindow, g_pDDBack, nullptr, DDBLT_WAIT, nullptr);
}

void UpdateBltRect()
{

	GetClientRect(g_hWndForDDraw, &g_rcWindow);
	ClientToScreen(g_hWndForDDraw, (POINT*)&g_rcWindow.left);
	ClientToScreen(g_hWndForDDraw, (POINT*)&g_rcWindow.right);
}


void CleanupDDraw()
{
	if (g_pDDBack)
	{
		g_pDDBack->Release();
		g_pDDBack = nullptr;
	}
	if (g_pDDPrimary)
	{
		g_pDDPrimary->SetClipper(nullptr);
		g_pDDPrimary->Release();
		g_pDDPrimary = nullptr;
	}
	if (g_pClipper)
	{
		g_pClipper->Release();
		g_pClipper = nullptr;
	}
	if (g_pDD7)
	{
		g_pDD7->Release();
		g_pDD7 = nullptr;
	}
	if (g_pDD)
	{
		g_pDD->Release();
		g_pDD = nullptr;
	}
/*	CleanupBackBuffer();

	

	
	*/
}