#ifndef UTILITY_H
#define UTILITY_H

#include "lpm_wl_lib.h"

#ifdef __unix__



#elif defined(_WIN32) || defined(WIN32)

    #include <windef.h>
    #include <windows.h>
    #include <Windows.h>
    #include <ShellAPI.h>
    #include <ShlObj.h>



#endif

#include <iostream>
#include <afxres.h>
#include <stdio.h>
#include <string>
#include <direct.h>
#include <dirent.h>
#include <fstream>
#include <sstream>
#include <string>
#include<cmath>
#include <QMessageBox>
#include <sys/types.h>
#include <sys/stat.h>
#include <iomanip>
#include <ctime>
#include <stdexcept>
#include <chrono>


inline void copy_to_clipboard(std::string message){
    const size_t len = strlen(message.c_str()) + 1;
    HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
    memcpy(GlobalLock(hMem),message.c_str(), len);
    GlobalUnlock(hMem);
    OpenClipboard(0);
    EmptyClipboard();
    SetClipboardData(CF_TEXT, hMem);
    CloseClipboard();
}



inline int time_since_launch;

#endif // UTILITY_H


