#pragma once

BOOL InitializeDDraw(HWND hWnd);
BOOL CreateBackBuffer(DWORD dwWidth, DWORD dwHeight);
void OnDraw();
void OnGameFrame();
void CleanupDDraw();
void SetDDrawCursorPos(int x, int y);
void UpdateBltRect();

void OnUp();
void OnDown();
void OnRight();
void OnLeft();

void OffUp();
void OffDown();
void OffRight();
void OffLeft();

void MoveLeft();
void MoveRight();
void MoveUp();
void MoveDown();

BOOL GetFontSize(int* piOutWidth, int* piOutHeight, const WCHAR* wchString, DWORD dwStrLen, HDC hDC);
void WriteText(const WCHAR* wchTxt, DWORD dwLen, int x, int y, DWORD dwColor, HDC hDC);
BOOL BeginGDI(HDC* pOutDC);
void DrawInfo(HDC hDC);
void EndGDI(HDC hDC);

void DrawRect(char* pBits, DWORD dwPitch, int sx, int sy, int iWidth, int iHeight, DWORD dwColor);
void DrawImage(char* pDestBits, DWORD dwPitch, char* pSrcImage, DWORD dwSrcImageWidth, DWORD dwSrcImageHeight, int iDestX, int iDestY);