#include <iostream>
#include <windows.h>
#include <string.h>
#include <stdio.h>

void PrintLastError(const char* functionName) {
    DWORD errorMessageID = GetLastError();
    if (errorMessageID == 0) {
        fprintf(stderr, "%s succeeded.\n", functionName);
        return;
    }

    LPSTR messageBuffer = NULL;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL,
                                 errorMessageID,
                                 MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                 (LPSTR)&messageBuffer,
                                 0,
                                 NULL);

    fprintf(stderr, "%s failed with error %lu: %s", functionName, errorMessageID, messageBuffer);

    LocalFree(messageBuffer);
}
