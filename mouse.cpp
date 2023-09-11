#include <Windows.h>
void mouse() {
    while (true) {
        POINT _POINT;
        GetCursorPos(&_POINT);
        DrawIcon(GetWindowDC(GetDesktopWindow()), _POINT.x - GetSystemMetrics(11) / 2, _POINT.y - GetSystemMetrics(12) / 2, LoadIconA(0, ((LPSTR)((ULONG_PTR)((WORD)(32513))))));
    }
}