//
// Created by mpampis on 4/6/17.
//

#ifndef HARRYPOTTER_LOGAREA_H
#define HARRYPOTTER_LOGAREA_H



#include "../../GameBoard/GameBoard.h"
#include <windows.h>

#define LOG_INFO_CODE 1
#define LOG_ERROR_CODE 2
#define logFileName "logs.txt"
#ifndef UNICODE

#define UNICODE
#define _UNICODE

#endif // UNICODE
class LogArea {

public:
	LogArea(int height, int width);
	~LogArea();
	
	BOOL writeLog(LPCSTR str, const SYSTEMTIME& time);
	BOOL writeLog(HANDLE& hHandle, LPCSTR, const SYSTEMTIME& time);
	BOOL writeLog(HANDLE& hHandle, LPCWSTR, const SYSTEMTIME& time);
	
	
	DWORD getTotalPrintedLogs();
    VOID setTotalPrintedLogs(DWORD totalPrintedLogs);
    int getTimeHeader(const SYSTEMTIME& time, LPSTR lpBuffer); // returns the characters that str contains
	int getHeight();
    int getWidth();

private:
	HANDLE hOut;
	DWORD totalPrintedLogs;
    int height;
    int width;
};


#endif //HARRYPOTTER_LOGAREA_H
