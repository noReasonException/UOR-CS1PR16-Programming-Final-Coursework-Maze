//
// Created by mpampis on 24/4/2017.
//

#ifndef HARRYPOTER_LEADERBOARD_H
#define HARRYPOTER_LEADERBOARD_H


#include <windows.h>
#include "../../Utilities/FileReader.h"
#include "../../Utilities/Record.h"

#define DEFAULT_WIDTH 30
#define DEFAULT_HEIGHT 25
#define DWORD_ERROR 0xFFFFFFFF
#define LEADER_BOARD_FILE "lb.dat"

class LeaderBoard {
public:
    LeaderBoard();
    ~LeaderBoard();
    
	BOOL addPlayer(const std::string& id);
    BOOL increasePoints(const std::string& id);

    Record getRecordAt(DWORD index) const;
    
	DWORD getTotalPlayers() const;
    
	int getHeight() const;
    int getWidth() const;
    
    VOID setHeight(int height);
    VOID setWidth(int width);
	
private:

    class Header {
    public:
        Header(DWORD numOfRecords);
        Header();

        VOID setNumOfRecords(DWORD numOfRecords);
        VOID increaseRecords();
        DWORD getNumOfRecords() const;
    private:
        DWORD numOfRecords;
    }; // end of class Header




    DWORD linearSearch(const std::string& key);
    
	BOOL contain(const std::string& id);
    
    BOOL setRecordAt(DWORD index, const Record& record);
    
	BOOL updateHeader(); // updating the header on the file
      
	FileReader* fileReader;
    Header header;
    int height;
    int width;
};


#endif //HARRYPOTER__LEADERBOARD_H

