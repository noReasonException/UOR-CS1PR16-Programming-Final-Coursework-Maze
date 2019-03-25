//
// Created by mpampis on 4/6/17.
//

#include "LogArea.h"

LogArea::LogArea(int height, int width) {
	this -> height = height;
	this -> width = width;
	
	hOut = CreateFile(TEXT(logFileName), GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL); // Creating a Handle for the logFile
	
	DWORD size = GetFileSize(hOut,NULL); // Getting the currentFileSize
	SetFilePointer(hOut, size, NULL, FILE_BEGIN); // Move the File Pointer on the right position for append.
	
	totalPrintedLogs = 0; // init printed Logs
}

LogArea::~LogArea() {
	CloseHandle(hOut); // Closes the handle for the file
}

// Writes a Log in the logFile
BOOL LogArea::writeLog(LPCSTR str, const SYSTEMTIME& time) {
	return writeLog(hOut, str, time);
}

// Writes a log in the hHandle
BOOL LogArea::writeLog(HANDLE& hHandle, LPCSTR str, const SYSTEMTIME& time) {
	CHAR formatBuffer[128]; // init Buffer for time header
	DWORD bytes = getTimeHeader(time, formatBuffer); // taking the time header on format buffer & also the bytes that the header consist
	DWORD tmp;
	
	if(!WriteFile(hHandle,formatBuffer,bytes,&tmp,NULL)) { // if we can't write on the file, then fml
		return FALSE; // Failed to writeLog
    }
    
	bytes = strlen(str); // bytes are equal now to the length of the str (log)
	
	LPSTR buffer = (LPSTR)malloc(bytes + 2); // Allocate memory for the new buffer + 2. Because I will need 2 more chars 'r','n'
	 
	strcpy(buffer,str); // copies the str(log) to buffer
	
	buffer[bytes] = '\r'; // Override the null terminate char '\0' with the char 'r'
	buffer[bytes +1 ] = '\n'; // Also place the 'n' char at the end of the buffer
	
	DWORD bytesActuallyWritten; // this variable contains the bytesActually written to the handle
	
	if(!WriteFile(hHandle, buffer, bytes + 2, &bytesActuallyWritten, NULL)) { // fml
		return FALSE;
    }
    
	free(buffer); // dealocate the memory for the buffer, we dont need it anymore
	
	if(bytesActuallyWritten != bytes + 2) { // if wrote less bytes that strlen(str) + 2 then we have big problem ;P
		return FALSE;
	}
	
	return TRUE; // if the method haven't terminate, then we are ok!
}

/*
BOOL LogArea::writeLog(HANDLE& hHandle, LPCWSTR str, const SYSTEMTIME& time) {
	CHAR formatBuffer[128];
	DWORD bytes = getTimeHeader(time, formatBuffer);
	WriteConsole(hHandle, formatBuffer, bytes, NULL, NULL);
	DWORD chars = wcslen(str);
	WriteConsoleW(hHandle, str, chars, NULL, NULL);
}*/

/* Place the timeHeader inside the buffer and returns a int number that represents the bytes written on buffer,
   the buffer must have suitable size
*/

int LogArea::getTimeHeader(const SYSTEMTIME& time, LPSTR lpBuffer) {
	return sprintf(lpBuffer,"[%d/%d/%d][%d:%d:%d]", time.wDay, time.wMonth, time.wYear, time.wHour, time.wMinute, time.wSecond); 
}

// Returns a DWORD of totalPrintedLogs, used from clear the logArea when it's full of logs
DWORD LogArea::getTotalPrintedLogs() {
	return totalPrintedLogs;
}
// Setter for the variable totalPrintedLogs
VOID LogArea::setTotalPrintedLogs(DWORD totalPrintedLogs) {
	this -> totalPrintedLogs = totalPrintedLogs;
}

// returns the height of the logArea
int LogArea::getHeight() {
    return height;
}
// retruns the width of the logArea
int LogArea::getWidth() {
    return width;
}
