#include <windows.h>
#include <psapi.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

void PrintLastError(const char* functionName);

//i have no idea what a pseudo handle is
//but i have to do this hackiness in order
//to check if it failed or not
//since INVALID_HANDLE_VALUE does not work

int check_proc_errors(HANDLE h){
    if (!GetProcessId(h)) {
        return -1;
    }
    return 1;
}



//zero the string not to run into problems
void zero_string(char *s, int n){
    for (int i=0; i<n; i++)
        s[i]='\0';
}



//replace the ecess characters with \0
int nullify_from_n_str(char *s){
    //find the location of the last dot
    char *dot_point = strrchr(s, '.');
    int dot = dot_point - s + 1; //location

    //bad spagetti
    if (s[dot+2] != 'e'){
        return -1;
    }

    for (int i=dot-1; i<dot+3; i++)
        s[i]='\0';

    return 1;
}



//this function will copy the name of the process into *name
//n is the number of characters in name
//this function will also remove the .exe at the end of the name
int SayMyName(char *name, int n){
    //here we will store the full string temoraraly
    char *s = (char*)calloc(n, sizeof(char));
    zero_string(s, n);

    //Get The Handle of myself
    HANDLE proc = GetCurrentProcess();

    //check for errors of GetCurrentProcess()
    if (!check_proc_errors(proc)){
        free(s); //dont forget to free!
        PrintLastError("GetCurrentProcess");
        return -1;
    }

    //extract the name
    DWORD get_mbn = GetModuleBaseNameA(
        proc,
        NULL,
        s,
        n
    );

    //check for errors of GetModuleBaseNameA()
    if (!get_mbn){
        free(s); //dont forget to free!
        PrintLastError("GetModuleBaseNameA");
        return -2;
    }

    //check for bruh moment where the dot isnt followed by 'exe'
    if (!nullify_from_n_str(s)){
        free(s);
        return -3;
    }

    //finally we copy the string propper
    strncpy(name, s, n);

    free(s); //were done with s
    return 1;
}
