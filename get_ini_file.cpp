#include <iostream>
#include <windows.h>
using namespace std;

void zero_string(char *s, int n);
void PrintLastError(const char* functionName);


//i brute force add .ini at the end of the name
void concat_ini(char *name, int n){
    name[n-5]='.';
    name[n-4]='i';
    name[n-3]='n';
    name[n-2]='i';
    name[n-1]='\0';
}


int create_and_truncate_ini(const char *name, HANDLE &file){
    file = CreateFileA(
        name,
        GENERIC_READ,
        0, //i have no clue what shared mode is lmao too tired too look it up rn
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (file == INVALID_HANDLE_VALUE){
        PrintLastError("CreateFileA");
        return -1;
    }

    //for now idk what i could add to the file by default so lets just close it;
    CloseHandle(file);

    return 1;
}

//THIS FUNCTION CHECKS IF THE FILE EXISTS
//AND IF IT DOESN'T IT INFORMS THE PROGRAM TO QUIT AFTER IT CREATES THE FILE
//IF IT *DOES* EXIST IT WILL pass the handle to &file
// -1 the file does not exist
// -2 some other fucked up error
// 1 success :3
int open_existing(const char *name, HANDLE &file){
    file = CreateFileA(
        name,
        GENERIC_READ,
        0, //i have no clue what shared mode is lmao too tired too look it up rn
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    //error checking
    if (file == INVALID_HANDLE_VALUE){
        if (GetLastError() == ERROR_FILE_NOT_FOUND){
            return -1; // IF THE FILES DOESN'T EXIST
        } else {
            PrintLastError("CreateFileA");
            return -2; //FAILURE
        }
    }

    return 1; //OTHERWISE ITS OK!
}



//main function of this module
// [-1] file does not exist and we have to quit
// [-2] some other obscure error
// [1] everything works perfectly

int get_ini_file(const char *name, HANDLE &file){
    int n = strlen(name)+5; // n is the size of the name plus ".ini"
    char *name_plus = (char*)calloc(n, sizeof(char));
    zero_string(name_plus, n); // we null the string
    strncpy(name_plus, name, n-5); // we copy the original name first
    concat_ini(name_plus, n); // then we add the ".ini"

    //cout << "name_plus is " <<name_plus << endl;

    switch (open_existing(name_plus, file)) {
        //best case, everything works
        case 1:
            cout << "success!!!" << endl;
            break;

        //this one is if the file doesnt exist
        //we have to report to the program to quit and create the file
        case -1:
            cout << "file does not exist!!!" << endl;

            //critical failure
            if (!create_and_truncate_ini(name_plus, file)){
                free(name_plus); // remember to free name_plus
                return -1;
            }

            free(name_plus); // remember to free name_plus
            return 2;
            break;

        //if everything fails we do this
        case -2:
            cout << "computer has exploded" << endl;
            free(name_plus); // remember to free name_plus
            return -1;
            break;
        default:
            break;
    }

    free(name_plus); // remember to free name_plus
    return 1;
}
