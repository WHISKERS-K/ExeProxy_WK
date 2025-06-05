#include <windows.h>
#include <iostream>
#include <cstring>

using namespace std;

void GetProxyPath(HANDLE &file, char *path, int n){
    DWORD br=0;
    ReadFile(file, path, n-1, &br, NULL);

    //bruteforce for now
    for (int i=0; i<n; i++){
        if (path[i]=='\n')
            path[i]='\0';
    }
}
