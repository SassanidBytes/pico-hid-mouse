#include <windows.h>
#include <iostream>
#include <string>

bool isEnemyColor(COLORREF color) {
    int r = GetRValue(color);
    int g = GetGValue(color);
    int b = GetBValue(color);
    return (r > 200 && g < 100 && b < 100);
}

struct Point { int x, y; };

Point findEnemy(int screenW, int screenH) {
    int cx = screenW / 2;
    int cy = screenH / 2;
    int radius = 200;
    
    HDC hdc = GetDC(NULL);
    
    for (int y = cy - radius; y < cy + radius; y++) {
        for (int x = cx - radius; x < cx + radius; x++) {
            COLORREF color = GetPixel(hdc, x, y);
            if (isEnemyColor(color)) {
                ReleaseDC(NULL, hdc);
                return {x - cx, y - cy};
            }
        }
    }
    
    ReleaseDC(NULL, hdc);
    return {0, 0};
}

int main() {
    HANDLE hSerial = CreateFileA("\\\\.\\COM6", GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    
    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cout << "COM6 nicht gefunden" << std::endl;
        return 1;
    }
     
    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    GetCommState(hSerial, &dcb);
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    SetCommState(hSerial, &dcb);
    
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    
    while (true) {
        // Linksklick gedrückt?
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            // Schnelle Klicks senden
            for (int i = 0; i < 5; i++) {
                std::string down = "1\n";  // Klick runter
                DWORD written;
                WriteFile(hSerial, down.c_str(), down.size(), &written, NULL);
                Sleep(20);
                
                std::string up = "0\n";    // Klick hoch
                WriteFile(hSerial, up.c_str(), up.size(), &written, NULL);
                Sleep(20);
            }
        }
        Sleep(1);
    }
    
    CloseHandle(hSerial);
    return 0;
}
