//
// Created by mpampis on 24/4/2017.
//
#include "LeaderBoard.h"

// LeaderBoard Methods


// TO - DO add logs everywhere fml

LeaderBoard::LeaderBoard() {

    fileReader = new FileReader(LEADER_BOARD_FILE);
    fileReader->setHeaderSize(sizeof(Header));
    fileReader->setRecordSize(sizeof(Record));
	
    if (fileReader->isEmpty()) { // if the file is new
        fileReader->setHeader(&header);
    }
	
    fileReader->getHeader(&header);

    height = header.getNumOfRecords() > 25 ? header.getNumOfRecords() : DEFAULT_HEIGHT;
    width = DEFAULT_WIDTH;
}


LeaderBoard::~LeaderBoard() {
    delete fileReader;
}

BOOL LeaderBoard::addPlayer(const std::string& id) {
    if (!contain(id)) { // if record doesn't exist already on the file, then append it
        Record record(id, 0);
        fileReader->appendRecord(&record);

        header.increaseRecords();
        updateHeader();

        height = header.getNumOfRecords() > 25 ? header.getNumOfRecords() : DEFAULT_HEIGHT;

        return TRUE;
    }

    return FALSE;
}

BOOL LeaderBoard::increasePoints(const std::string& id) {
    DWORD index = linearSearch(id);

    if (index == DWORD_ERROR) { // the record doesn't exists
        return FALSE;
    }

    Record record;

    if (!fileReader->getRecordAt(index, &record)) {
        return FALSE;
    }

    record.increasePoints(1);

    Record tempRecord;
    int i;
    for (i = index - 1; i >= 0; i--) {
        if (!fileReader->getRecordAt(i, &tempRecord)) {
            return FALSE;
        }
        if (record.compareTo(tempRecord) != 1) { // if we find something bigger or equal to record
            break;
        }
    }

    i++; // Increase i by 1

    // TO - DO add check for fail
    fileReader->shiftRecords(i, index - 1, SHIFT_RIGHT);
    fileReader->setRecordAt(i, &record);

    return TRUE;
}

DWORD LeaderBoard::linearSearch(const std::string& key) {
    Record current;

    DWORD nRecords = header.getNumOfRecords();

    for (DWORD i = 0; i < nRecords; i++) {
        fileReader->getRecordAt(i, &current);

        if (current.getID() == key) {
            return i;
        }
    }

    return DWORD_ERROR;
}

BOOL LeaderBoard::contain(const std::string& id) {
    return linearSearch(id) != DWORD_ERROR;
}

BOOL LeaderBoard::updateHeader() {
    return fileReader->setHeader(&header);
}


Record LeaderBoard::getRecordAt(DWORD index) const {
    Record record;

    if (!fileReader->getRecordAt(index, &record)) {
        record.setID("ERROR");
        record.setPoints(DWORD_ERROR);
    }

    return record;
}

BOOL LeaderBoard::setRecordAt(DWORD index, const Record& record) {
    return fileReader->setRecordAt(index, &record);
}

DWORD LeaderBoard::getTotalPlayers() const{
	return header.getNumOfRecords();
}

VOID LeaderBoard::setHeight(int height) {
    this->height = height;
}

VOID LeaderBoard::setWidth(int width) {
    this->width = width;
}

int LeaderBoard::getHeight() const {
    return height;
}

int LeaderBoard::getWidth() const {
    return width;
}

// Header Methods

LeaderBoard::Header::Header(DWORD numOfRecords):numOfRecords(numOfRecords) {}
LeaderBoard::Header::Header():numOfRecords(0) {}

VOID LeaderBoard::Header::setNumOfRecords(DWORD numOfRecords) {
    this->numOfRecords = numOfRecords;
}

VOID LeaderBoard::Header::increaseRecords() {
    numOfRecords++;
}

DWORD LeaderBoard::Header::getNumOfRecords() const {
    return numOfRecords;
}

