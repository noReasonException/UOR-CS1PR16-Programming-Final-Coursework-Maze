//
// Created by mpampis on 24/4/2017.
//

#ifndef HARRYPOTER_RECORD_H
#define HARRYPOTER_RECORD_H

#include <windows.h>
#include <iostream>

class Record {
public:
    Record(const std::string& id, DWORD points);
    Record();
    
    BOOL setID(const std::string& newID);
    VOID setPoints(DWORD points);
    VOID increasePoints(DWORD value);

    int compareTo(const Record& record);
    std::string getID() const;
    DWORD getPoints() const;
private:
    CHAR id[9]; // example "cs161042" (8 chars + 1 for null terminated '\0')
    DWORD points;
}; // end of class Record

#endif // HARRYPOTER_RECORD_H
