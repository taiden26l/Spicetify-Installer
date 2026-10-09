#include <windows.h>
#include <stdio.h>

int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0, exitCode;
    if (GetConsoleMode(hOut, &dwMode)) SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    printf("\x1b[32mInstalling spicetify...\x1b[0m\n\n");
    wchar_t cmd[] = L"powershell.exe -NoProfile -ExecutionPolicy Bypass -Command \"iwr -useb https://raw.githubusercontent.com/spicetify/cli/main/install.ps1 | iex\"";
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;
    if (!CreateProcessW(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) return 1;
    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &exitCode);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    if (exitCode != 0) {
        printf("\n\x1b[31m[ERROR]\x1b[0m Spicetify installation failed.\n");
        return 1;
    }
    else if (exitCode == 0) printf("\n\x1b[32mSpicetify was successfully installed!\x1b[0m\n");
    return 0;
}
