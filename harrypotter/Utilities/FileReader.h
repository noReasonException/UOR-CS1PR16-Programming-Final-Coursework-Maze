//
// Created by mpampis on 24/4/2017.
//

#ifndef HARRYPOTER_FILEREADER_H
#define HARRYPOTER_FILEREADER_H

#include <iostream>
#include <windows.h>

#define SHIFT_RIGHT 1
#define SHIFT_LEFT 2

class FileReader {
public:
    FileReader(std::string fileName);
    ~FileReader();

    VOID setHeaderSize(DWORD dwHeaderSize); // Setting up the header size
    VOID setRecordSize(DWORD dwRecordSize); // Setting up the record size

    BOOL setHeader(LPCVOID headerBuffer); // Sets the header on specific header
    BOOL getHeader(PVOID headerBuffer); // Place the current header inside the headerBuffer

    BOOL appendRecord(LPCVOID recordBuffer); // Append a record in the end of the file
    BOOL setRecordAt(DWORD index, LPCVOID recordBuffer); // Make a record equal to another
    BOOL getRecordAt(DWORD index, PVOID recordBuffer); // Place the index record inside the recordBuffer

    BOOL shiftRecords(DWORD indexLow, DWORD indexHigh, DWORD dwFlag);

    LARGE_INTEGER getFileSize();
    BOOL isEmpty();

private:
    BOOL shiftRight(DWORD indexLow, DWORD indexHigh);
    BOOL shiftLeft(DWORD indexLow, DWORD indexHigh);

    HANDLE hFile; // A handle to the file
    DWORD headerSize; // the sizeof(header)
    DWORD recordSize; // the sizeof(record)

    DWORD bytesCount;
    LARGE_INTEGER filePos; // This will be used to set value on ov
    OVERLAPPED ovHeader; // This ov is for read/write in the header
    OVERLAPPED ov; // This ov will move on all records
};




#endif // HARRYPOTER_FILEREADER_H
