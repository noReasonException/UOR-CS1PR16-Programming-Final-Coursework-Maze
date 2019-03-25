//
// Created by mpampis on 4/6/17.
//

#ifndef HARRYPOTTER_WINDOW_H
#define HARRYPOTTER_WINDOW_H

#include <windows.h>
#include <sstream>
#include "../../Map/Map.h"
#include "../LogArea/LogArea.h"
#include "../LeaderBoard/LeaderBoard.h"
#include "../InfoBoard/InfoBoard.h"

#ifndef UNICODE

#define UNICODE
#define _UNICODE

#endif // UNICODE

#define windowHeight 850
#define windowWidth 1280
#define mapMarginTop 1
#define mapMarginLeft 55
#define logAreaMarginTop 5
#define logAreaMarginLeft 25
#define infoBoardMarginTop 1
#define infoBoardMarginLeft 10

class LogArea;
class Window {
public:
	
	 Window(Map* map, InfoBoard* infoBoard);
    ~Window();
  

    /*
     * Placing ' ' (blank character) in the obj currentPosition and redraw the avatar of the obj in the newPosition
     * inside the map
     */
    void drawOnMap(ObjectInfo& obj,  Coordinate& newPosition);

    /*
     * Simply redraw the obj avatar inside the Map on it position
     */
    void drawOnMap(ObjectInfo& obj);

    /*
     * Draw on map specific position the character ch with the default color from the Map class
     */
    void drawOnMap(char ch, int row, int column);
    void drawOnMap(char ch, const Coordinate& coordinate);

    /*
    * Draw on map specific position the character ch with specific color if only 1 arg was set for the color, uses the
    * default background color from the map and the arg for the foreground
    */

    void drawOnMap(char ch, int row, int column, DWORD foreground, DWORD background);
    void drawOnMap(char ch, const Coordinate& coordinate, DWORD foreground, DWORD background);

    void drawOnMap(char ch, int row, int column, DWORD foreground);
    void drawOnMap(char ch, const Coordinate& coordinate, DWORD foreground);
	
	VOID writeInfoLog(const std::string& log); // write a info log inside the log area
	VOID writeErrorLog(const std::string& log); // write a error log inside the log area
	VOID clearLogArea(); // clears the log area
	
	void updateInfoBoard();
	class Pair{
   	public:
   		Pair();
   		int x;
   		int y;
   };

	ArrayList<Window::Pair>* findDifferences(ArrayList<Info> *prev, ArrayList<Info> *curr);

	InfoBoard* infoBoard;
private:

	void printMap(); // Prints the Map
    void printLogArea(); // Prints the LogArea
		
	// Write a log inside the log area
	VOID writeLog(const std::string& log, DWORD dwCode);
	//VOID write(const std::string& str);
    /*
     * This method is the only way to change the currentCursorPosition attribute. Actually when you print something
     * in the screen you don't actually move the cursorPosition. So be careful with the cursorPosition
     */
    void gotoxy(int x, int y);
    void gotoxy(const Coordinate& cord);

    // Prints a box in specific position (used by printLogArea, printLeaderBoard)
    void printBox(int x, int y, int height, int width);

    // Setting the color for the new output
    void setColor(DWORD foreground, DWORD background);
    void setColor(DWORD color);
    
    void printInfoBoardID(int row, std::string& id);
    void printInfoBoardAvat(int row, char ch);
    void printInfoBoardAlive(int row, bool flag);
    void printInfoBoardStatus(int row, bool flag);
    void printInfoBoardPoints(int row, DWORD points);
    void printInfoRecord(int row, Info& info);
    void printInfoBoardDelims(int row, char delim);
    
    void clearInfoBoardRecordAt(int row, int column);
    void clearInfoBoardRecordAt(Pair pair);
	void printInfoBoard();
	
    HANDLE hConsole; // the handle for the console
    COORD* currentCursorPosition; // the current cursror position (care only change from the gotoxy function)
    DWORD defaultColor; // default color (white foreground, black background)
    Map* map;
    LogArea* logArea; 
    SYSTEMTIME time; 
    ArrayList<Info>* prevList;
    Coordinate cordInfoBoard;
    Coordinate cordLogArea; // Start point of the logArea
    LPWSTR buffer; // Buffer used by writeLog to print logs on the screen
};


#endif //HARRYPOTTER_WINDOW_H
