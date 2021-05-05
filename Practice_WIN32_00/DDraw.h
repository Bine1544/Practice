#pragma once

BOOL InitializeDDraw(HWND hWnd);
BOOL CreateBackBuffer(DWORD dwWidth, DWORD dwHeight);
void OnDraw();
void CleanupDDraw();
void SetDDrawCursorPos(int x, int y);
void UpdateBltRect();

void MoveLeft();
void MoveRight();
void MoveUp();
void MoveDown();