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


BOOL g_bUp = FALSE;
BOOL g_bDown = FALSE;
BOOL g_bLeft = FALSE;
BOOL g_bRight = FALSE;

void SetDDrawCursorPos(int x, int y)
{
	g_iCursorX = x+4;
	g_iCursorY = y;
}

void OnUp()
{
	g_bUp = TRUE;
}
void OnDown()
{
	g_bDown = TRUE;
}
void OnLeft()
{
	g_bLeft = TRUE;
}
void OnRight()
{
	g_bRight = TRUE;
}

void OffUp()
{
	g_bUp = FALSE;
}
void OffDown()
{
	g_bDown = FALSE;
}
void OffLeft()
{
	g_bLeft = FALSE;
}
void OffRight()
{
	g_bRight = FALSE;
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

ULONGLONG g_PrvGameFrameTick = 0;
int g_iSpeed = 4;

void OnGameFrame()
{
	ULONGLONG CurTick = GetTickCount64();
	if (CurTick - g_PrvGameFrameTick > 16)
	{
		if (TRUE == g_bUp)
		{
			g_iCursorY -= g_iSpeed;
		}

		if (TRUE == g_bDown)
		{
			g_iCursorY += g_iSpeed;
		}

		if (TRUE == g_bLeft)
		{
			g_iCursorX -= g_iSpeed;
		}

		if (TRUE == g_bRight)
		{
			g_iCursorX += g_iSpeed;
		}
		g_PrvGameFrameTick = CurTick;
	}
	else
	{
		int a = 0;
	}
}
ULONGLONG g_FrameCount = 0;
ULONGLONG g_PrvDrawTick = 0;
DWORD g_dwFPS = 0;

void DrawRect(char* pBits, DWORD dwPitch, int sx, int sy, int iWidth, int iHeight, DWORD dwColor)
{
	if (sx < 0)
	{
		int offset = 0 - sx;
		sx = 0;
		iWidth -= offset;
	}
	if (iWidth < 0)
		return;
	if (sx + iWidth >= g_dwWidth)
	{
		iWidth -= sx + iWidth - g_dwWidth;
	}
	for (int i = 0; i<iWidth; i++)
	{
		// a
		
		int x = sx + i;
	
		// x,sy <- Á¡À» Âï´Â´Ù.
		*(DWORD*)(pBits + 4 * x + dwPitch * sy) = dwColor;
	}
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

	
	//
	int screen_width = ddsc.dwWidth-1;
	int screen_height = ddsc.dwHeight-1;

	/*
	if (g_iCursorX < 0)
	{
		g_iCursorX = 0;
	}
	if (g_iCursorX >= screen_width)
	{
		g_iCursorX = screen_width - 1;
	}
	if (g_iCursorY < 0)
	{
		g_iCursorY = 0;
	}
	if (g_iCursorY >= screen_height)
	{
		g_iCursorY = screen_height - 1;
	}
	*/
	
	/*
	char* pDest = (char*)ddsc.lpSurface + g_iCursorY * ddsc.lPitch + g_iCursorX * 4;
	*(DWORD*)pDest = dwColor;
	pDest = (char*)ddsc.lpSurface + g_iCursorY * ddsc.lPitch + (g_iCursorX + 1)* 4;
	*(DWORD*)pDest = dwColor;
	pDest = (char*)ddsc.lpSurface + (g_iCursorY+1) * ddsc.lPitch + g_iCursorX * 4;
	*(DWORD*)pDest = dwColor;
	pDest = (char*)ddsc.lpSurface + (g_iCursorY+1) * ddsc.lPitch + (g_iCursorX + 1) * 4;
	*(DWORD*)pDest = dwColor;*/
	DrawRect((char*)ddsc.lpSurface, ddsc.lPitch, g_iCursorX, g_iCursorY, 16, 1, dwColor);
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
	HDC hDC;
	BeginGDI(&hDC);
	//const WCHAR* wchTxt = g_wchInfoTxt;
	//DWORD dwLen = g_dwInfoTxtLen;

	WCHAR wchTxt[16] = {};
	DWORD dwLen = swprintf_s(wchTxt,L"%u",g_dwFPS);
	WriteText(wchTxt, dwLen, 0, 0, 0xffff0000, hDC);
	EndGDI(hDC);
	g_pDDBack->Unlock(nullptr);

	g_pDDPrimary->Blt(&g_rcWindow, g_pDDBack, nullptr, DDBLT_WAIT, nullptr);

	// check FPS
	g_FrameCount++;
	ULONGLONG CurTick = GetTickCount64();
	if (CurTick - g_PrvDrawTick >= 1000)
	{
		g_dwFPS = (DWORD)g_FrameCount;
		WCHAR	wchFPS[32];
		swprintf_s(wchFPS, L"FPS: %u\n", g_dwFPS);
		OutputDebugStringW(wchFPS);
		g_PrvDrawTick = CurTick;
		g_FrameCount = 0;

	}
	
}

BOOL GetFontSize(int* piOutWidth, int* piOutHeight, const WCHAR* wchString, DWORD dwStrLen, HDC hDC)
{
	BOOL	bResult = FALSE;
	*piOutWidth = 1;
	*piOutHeight = 1;

	SIZE	strSize;
	BOOL bGetSize = GetTextExtentPoint32W(hDC, wchString, dwStrLen, &strSize);


	if (bGetSize)
	{
		*piOutWidth = strSize.cx;
		*piOutHeight = strSize.cy;
		bResult = TRUE;
	}
	return bResult;
}

void WriteText(const WCHAR* wchTxt, DWORD dwLen, int x, int y, DWORD dwColor, HDC hDC)
{
	SetBkMode(hDC, TRANSPARENT);

	RECT	textRect, texRectSide[4];
	int		iWidth = 0;
	int		iHeight = 0;
	GetFontSize(&iWidth, &iHeight, wchTxt, dwLen, hDC);

	textRect.left = x;
	textRect.top = y;
	textRect.right = textRect.left + iWidth;
	textRect.bottom = textRect.top + iHeight;

	texRectSide[0].left = textRect.left - 1;
	texRectSide[0].top = textRect.top - 1;
	texRectSide[0].right = textRect.right - 1;
	texRectSide[0].bottom = textRect.bottom - 1;


	texRectSide[1].left = textRect.left + 1;
	texRectSide[1].top = textRect.top - 1;
	texRectSide[1].right = textRect.right + 1;
	texRectSide[1].bottom = textRect.bottom - 1;

	texRectSide[2].left = textRect.left + 1;
	texRectSide[2].top = textRect.top + 1;
	texRectSide[2].right = textRect.right + 1;
	texRectSide[2].bottom = textRect.bottom + 1;

	texRectSide[3].left = textRect.left - 1;
	texRectSide[3].top = textRect.top + 1;
	texRectSide[3].right = textRect.right - 1;
	texRectSide[3].bottom = textRect.bottom + 1;

	SetTextColor(hDC, 0x00000000);
	for (DWORD i = 0; i < 4; i++)
	{
		DrawText(hDC, wchTxt, -1, &texRectSide[i], DT_LEFT | DT_WORDBREAK);
	}

	DWORD r = (dwColor & 0x00ff0000) >> 16;
	DWORD g = (dwColor & 0x0000ff00) >> 8;
	DWORD b = (dwColor & 0x000000ff);

	COLORREF color = RGB(r, g, b);
	SetTextColor(hDC, color);
	DrawText(hDC, wchTxt, -1, &textRect, DT_LEFT | DT_WORDBREAK);


}


void UpdateBltRect()
{

	GetClientRect(g_hWndForDDraw, &g_rcWindow);
	ClientToScreen(g_hWndForDDraw, (POINT*)&g_rcWindow.left);
	ClientToScreen(g_hWndForDDraw, (POINT*)&g_rcWindow.right);
}

BOOL BeginGDI(HDC* pOutDC)
{
	BOOL	bResult = FALSE;
	HDC	hDC = nullptr;

	HRESULT hr = g_pDDBack->GetDC(&hDC);
	if (FAILED(hr))
	{
	#ifdef _DEBUG
		__debugbreak();
	#endif
		goto lb_return;
	}
	bResult = TRUE;
	*pOutDC = hDC;

lb_return:
	return bResult;
}
void DrawInfo(HDC hDC)
{
	//const WCHAR* wchTxt = g_wchInfoTxt;
	//DWORD dwLen = g_dwInfoTxtLen;

	//WriteText(wchTxt, dwLen, 0, 0, 0xffff0000, hDC);
}
void EndGDI(HDC hDC)
{
	//ProcessGDI(hDC);
	g_pDDBack->ReleaseDC(hDC);
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