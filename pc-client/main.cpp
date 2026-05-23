#include <windows.h>
#include <iostream>
#include <string>

int main() {
    // COM Port öffnen
    HANDLE hSerial = CreateFileA(
        "\\\\.\\COM6",
        GENERIC_WRITE,
        0, NULL,
        OPEN_EXISTING,
        0, NULL
    );

    if (hSerial == INVALID_HANDLE_VALUE) {
        std::cout << "Fehler: COM6 nicht gefunden" << std::endl;
        return 1;
    }

    // Baudrate einstellen
    DCB dcb = {0};
    dcb.DCBlength = sizeof(dcb);
    GetCommState(hSerial, &dcb);
    dcb.BaudRate = CBR_115200;
    dcb.ByteSize = 8;
    dcb.StopBits = ONESTOPBIT;
    dcb.Parity   = NOPARITY;
    SetCommState(hSerial, &dcb);

    // Test: Maus 50px nach rechts
    std::string cmd = "50,0\n";
    DWORD written;
    WriteFile(hSerial, cmd.c_str(), cmd.size(), &written, NULL);

    std::cout << "Gesendet: " << cmd;
    CloseHandle(hSerial);
    return 0;
}