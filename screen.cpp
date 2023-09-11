#include <windows.h>
int screenWidth, screenHeight;
void circle(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(NULL);
        StretchBlt(hdc, 50, 50, screenWidth - 100, screenHeight - 100, hdc, 0, 0, screenWidth, screenHeight, SRCCOPY);
        ReleaseDC(NULL, hdc);
        Sleep(1);
    }
}
void originalCode(LPVOID lpParam) {
    while (1) {
        HDC hdc = GetDC(0);
        PatBlt(hdc, 0, 0, screenWidth, screenHeight, PATINVERT);
        Sleep(1);
        ReleaseDC(0, hdc);
    }
}
void screen() {
    screenWidth = GetSystemMetrics(SM_CXSCREEN);
    screenHeight = GetSystemMetrics(SM_CYSCREEN);
    HANDLE hThread1 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)circle, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)originalCode, NULL, 0, NULL);
    if (hThread1 == NULL || hThread2 == NULL) {
        MessageBoxW(NULL, L"Failed to create thread", L"Error", MB_ICONERROR);
    }
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}