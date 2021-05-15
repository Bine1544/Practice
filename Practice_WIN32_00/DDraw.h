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