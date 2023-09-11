#include <iostream>
#include <windows.h>
HHOOK hook;
bool permitirInteraccion = false;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode >= 0) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            if (permitirInteraccion) {
                KBDLLHOOKSTRUCT* kbdStruct = (KBDLLHOOKSTRUCT*)lParam;
                DWORD key = kbdStruct->vkCode;
                char keyChar = MapVirtualKey(key, MAPVK_VK_TO_CHAR);
                std::cout << "Tecla presionada: " << keyChar << std::endl;
            }
            return 1;
        }
    }
    return CallNextHookEx(hook, nCode, wParam, lParam);
}
void keyboard() {
    hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
    if (hook == NULL) {
        std::cerr << "Error al establecer el hook de teclado." << std::endl;
    }
    std::cout << "Esperando 10 segundos antes de permitir interacción..." << std::endl;
    Sleep(1);
    permitirInteraccion = true;
    std::cout << "Ahora puedes interactuar con las teclas." << std::endl;
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(hook);
}