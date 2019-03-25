//
// Created by mpampis on 24/4/2017.
//

#include "Record.h"


Record::Record(const std::string& id, DWORD points) {
	setID(id);
	setPoints(points);
}

Record::Record() {
	setID("");
	setPoints(0);
}

BOOL Record::setID(const std::string& newID) {
    if(newID.length() > 8) {
    	strcpy(id, "ERROR");
    	return FALSE;
	}
	
	strcpy(id, newID.c_str());
	
	return TRUE;
}

VOID Record::setPoints(DWORD points) {
    this->points = points;
}

std::string Record::getID() const {
    std::string str(id);
    
    return str;
}

DWORD Record::getPoints() const {
    return points;
}

VOID Record::increasePoints(DWORD value) {
    points += value;
}

int Record::compareTo(const Record& record) {
    if (points > record.getPoints()) {
        return 1;
    }

    if (points < record.getPoints()) {
        return -1;
    }

    return 0;
}
