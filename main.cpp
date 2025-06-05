#include <iostream>
#include <windows.h>

using namespace std;

void PrintLastError(const char* functionName);
void GetProxyPath(HANDLE &file, char *path, int n);
int SayMyName(char *name, int n);
int get_ini_file(const char *name, HANDLE &file);

int main(){

    char name[512]={'\0'};
    char path[512]={'\0'};
    SayMyName(name, 512);

    HANDLE file;
    int status = get_ini_file(name, file);

    switch (status) {
        case -1:
            cout << "The File Was Created Please Restart The Program After It Has Been Modified" << endl;
            return 0;
            break;
        case -2:
            cout << "make sure you have permissions for the folder the executable is in" << endl;
            return 0;
            break;
        default:
            break;
    }

    GetProxyPath(file, path, 512);
    cout << "[" << path << "]" << endl;

    //its 3am and im tired so heres some pasta
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    ZeroMemory(&pi, sizeof(pi));
    si.cb = sizeof(si);

    BOOL proc_test = CreateProcess(
        path,     // Application name (can be NULL if commandLine is specified)
        NULL,         // Command line arguments (can include the application name)
        NULL,                // Process handle not inheritable
        NULL,                // Thread handle not inheritable
        FALSE,               // Set handle inheritance to FALSE
        DETACHED_PROCESS,                   // No creation flags
        NULL,                // Use parent's environment block
        NULL,                // Use parent's starting directory
        &si,                 // Pointer to STARTUPINFO structure
        &pi                  // Pointer to PROCESS_INFORMATION structure
    );

    return 1;
}
