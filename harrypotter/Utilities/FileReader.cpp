//
// Created by mpampis on 24/4/2017.
//

#include "FileReader.h"


FileReader::FileReader(std::string fileName) {
    // TO - DO, change the name on CreateFile
    hFile = CreateFile(TEXT("lb.dat"), GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_WRITE_THROUGH, NULL);
    ovHeader = {0, 0, 0, 0, NULL};
    ov = { 0, 0, 0, 0, NULL };
    // TO - DO if hFile is invalid print log
}

FileReader::~FileReader() {
    CloseHandle(hFile);
}

VOID FileReader::setHeaderSize(DWORD dwHeaderSize) {
    headerSize = dwHeaderSize;
}

VOID FileReader::setRecordSize(DWORD dwRecordSize) {
    recordSize = dwRecordSize;
}

BOOL FileReader::setHeader(LPCVOID headerBuffer) {
    if (headerSize == 0) {
        // TO - DO, print LOG
        return FALSE;
    }

    return WriteFile(hFile, headerBuffer, headerSize, &bytesCount, &ovHeader) && bytesCount;
}

BOOL FileReader::getHeader(PVOID headerBuffer) {
    if (headerSize == 0) {
        // TO - DO, print LOG
        return FALSE;
    }

    return ReadFile(hFile, headerBuffer, headerSize, &bytesCount, &ovHeader) && bytesCount;
}

BOOL FileReader::appendRecord(LPCVOID recordBuffer) {
    if (recordSize == 0) {
        // TO - DO, print LOG
        return FALSE;
    }
    filePos = getFileSize(); // getting current file size

    // Setting up the ov for append
    ov.Offset = filePos.LowPart;
    ov.OffsetHigh = filePos.HighPart;

    return WriteFile(hFile, recordBuffer, recordSize, &bytesCount, &ov) && bytesCount;
}

BOOL FileReader::setRecordAt(DWORD index, LPCVOID recordBuffer) {
    if (recordSize == 0) {
        // TO - DO, print LOG
        return FALSE;
    }

    filePos.QuadPart = (LONGLONG)(index * recordSize + headerSize); // Calculate the filePos

    if (filePos.QuadPart > getFileSize().QuadPart - recordSize) { // The last record is on filesize - recordsize
        return FALSE;
    }

    ov.Offset = filePos.LowPart;
    ov.OffsetHigh = filePos.HighPart;

    return WriteFile(hFile, recordBuffer, recordSize, &bytesCount, &ov) && bytesCount;
}

BOOL FileReader::getRecordAt(DWORD index, PVOID recordBuffer) {
    if (recordSize == 0) {
        // TO - DO, print LOG
        return FALSE;
    }

    filePos.QuadPart = (LONGLONG)(index * recordSize + headerSize); // Calculate the filePos

    if (filePos.QuadPart > getFileSize().QuadPart - recordSize) { // The last record is on filesize - recordsize
        return FALSE;
    }

    ov.Offset = filePos.LowPart;
    ov.OffsetHigh = filePos.HighPart;

    return ReadFile(hFile, recordBuffer, recordSize, &bytesCount, &ov) && bytesCount;

}

LARGE_INTEGER FileReader::getFileSize() {
    LARGE_INTEGER temp;
    GetFileSizeEx(hFile, &temp);

    return temp;
}

BOOL FileReader::isEmpty() {

    return getFileSize().QuadPart == 0;
}

BOOL FileReader::shiftRecords(DWORD indexLow, DWORD indexHigh, DWORD dwFlag) {
    BOOL flag;
    switch (dwFlag) {
        case SHIFT_RIGHT:
            flag = shiftRight(indexLow, indexHigh);
            break;
        case SHIFT_LEFT:
            flag = shiftLeft(indexLow, indexHigh);
            break;
        default :
            flag = FALSE;
    }

    return flag;
}

BOOL FileReader::shiftRight(DWORD indexLow, DWORD indexHigh) {
    PVOID buffer = malloc(recordSize);
    BOOL OK;
    for (DWORD i = indexHigh; i >= indexLow; i--) {
        OK = getRecordAt(i, buffer);
        OK = OK && setRecordAt(i + 1, buffer);

        if (!OK) {
            free(buffer);
            return FALSE;
        }
    }

    free(buffer);
    return TRUE;

}

BOOL FileReader::shiftLeft(DWORD indexLow, DWORD indexHigh) {
    PVOID buffer = malloc(recordSize);
    BOOL OK;

    for (DWORD i = indexLow; i <= indexHigh; i++) {
        OK = getRecordAt(i, buffer);
        OK = OK && setRecordAt(i - 1, buffer);

        if (!OK) {
            free(buffer);
            return FALSE;
        }
    }

    free(buffer);

    return TRUE;
}