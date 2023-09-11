#include <windows.h>
void taskmanager()
{
    HWND hWin;
    hWin = FindWindowW(L"Shell_TrayWnd", NULL);
    EnableWindow(hWin, FALSE);
    while (1 == 1) {
        ShowWindow(hWin, SW_HIDE);
    }
}
