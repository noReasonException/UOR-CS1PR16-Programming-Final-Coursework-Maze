//
// Created by mpampis on 4/6/17.
//

#include "Window.h"

Window::Window(Map *map, InfoBoard* infoBoard):map(map),infoBoard(infoBoard) {
	FreeConsole();
	AllocConsole();
	HWND hwnd;
	
	system("cls"); // Clear the screen
 	currentCursorPosition = (COORD*) malloc(sizeof(COORD)); // Allocate memory for the currentCurs
	
	hConsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); // Open a new handle for the new Console
	
	SetConsoleMode(hConsole, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT); // Setting some consoleModes
	
    currentCursorPosition = (COORD*) malloc(sizeof(COORD)); // Allocate memory for the currentCurs
    
    SetConsoleTitle("Main Window");
    
    gotoxy(0,0);
    
    // resizing the window
	hwnd = GetConsoleWindow(); // getting agai the window

	if( hwnd != NULL ) { 
		SetWindowPos(hwnd ,0,0,0 ,windowWidth,windowHeight ,SWP_SHOWWINDOW); 
	}
    
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    GetConsoleScreenBufferInfo(hConsole, &csbiInfo);
    defaultColor = csbiInfo.wAttributes; // saving the default color

	cordInfoBoard.setX(mapMarginLeft + map->getColumns() + infoBoardMarginLeft + 1);
	cordInfoBoard.setY(infoBoardMarginTop + 1);
	
	cordLogArea.setX(logAreaMarginLeft + 2); // Setting up a position inside the window that logs will printed
	cordLogArea.setY(mapMarginTop + map -> getRows() + logAreaMarginTop + 1);
	
	buffer = (LPWSTR) malloc(sizeof(WCHAR) * 1024);
	
	logArea = new LogArea(15,100);

	prevList = infoBoard->getList()->clone();
	printMap();
	printLogArea();
	printInfoBoard();
	
}

// DeAllocate the resources
Window::~Window() {
	CloseHandle(hConsole); // Close the Console Handle
	free(buffer);
	free(currentCursorPosition);
    delete prevList;
	delete logArea;
}


// PrintOnLogArea a log & on the file, with type info
VOID Window::writeInfoLog(const std::string& log) {
	writeLog(log, LOG_INFO_CODE);
}

// PrintOnLogArea a log & on the file, with type error 
VOID Window::writeErrorLog(const std::string& log) {
	writeLog(log, LOG_ERROR_CODE);
	
}

// PrintOnLogArea a log, with dwCode type
/*
	Error logs have a small bug :(, if logArea is too small i am not doing any check if this msges can be printed inside the logArea,
	
	TO - DO
	 - Fix the above bug
	 - Do enought tests
*/

VOID Window::writeLog(const std::string& log, DWORD dwCode) {
	std::string* prefix;
	BOOL error = FALSE;
	
	DWORD tmp;
	DWORD totalLogs = logArea -> getTotalPrintedLogs(); // Getting the totalPrintedLogs in the current LogArea
	if(totalLogs == logArea -> getHeight()) { // if they are equal of the height, thats mean that the logArea is full of logs
		clearLogArea();
		totalLogs = 0;
	}
	
	switch(dwCode) {
		case LOG_INFO_CODE : // If it's info log
			prefix = new std::string("[INFO] ");
			setColor(FOREGROUND_GREEN);	// change textColor
			break;
		case LOG_ERROR_CODE : // If it's error log
			prefix = new std::string("[ERROR] ");
			setColor(FOREGROUND_RED); // change textColor
			break;
	}
	
	GetLocalTime(&time); // Getting the local time
	
	gotoxy(cordLogArea.getX(), cordLogArea.getY() + totalLogs); // Move the cursor on the right position for the next Log
	
	CHAR formatBuffer[128]; // this buffer will be used to store the timeHeader
	DWORD charsInFormatBuffer = logArea -> getTimeHeader(time, formatBuffer); 
	
	WriteConsole(hConsole, formatBuffer, charsInFormatBuffer, &tmp, NULL); // WritesOnConsole the time header for the log

	
	*prefix += log; // add on prefix string the log
	
	LPCSTR logChars = prefix -> c_str(); // Getting a pointer to chars for the whole log (timeHeader + log)
	
	DWORD nChars = strlen(logChars); // Getting the amount of characters in the log stirng
	
	/* TO - DO
		if fail to writeLog on file we havent any check :(
	*/
	if(nChars + charsInFormatBuffer > logArea -> getWidth() - 1) { // If the characters in log is greater than the width of the logArea - 1 ( -1 because i leave a space on the left side )
		logArea -> writeLog(logChars,time); // Store the log on the file
		setColor(defaultColor);
		writeLog("Too Long log, cannot be printed", LOG_ERROR_CODE); // Write this log in the console also
		return;
	}
	
	// Change the typeCode for the consoleOutput & store it on the buffer
	MultiByteToWideChar(CP_ACP, 0, logChars, -1, buffer, 1024);
	
	// Print the log in the Console
	WriteConsoleW(hConsole, buffer, nChars, &tmp, NULL);
	logArea -> setTotalPrintedLogs(++totalLogs);
	
	error = !(logArea -> writeLog(logChars,time)); // write on file
	
	if(error) { // if function failed to write on the file, try to print a error message on the console
		
		if(totalLogs == logArea -> getHeight()) { // if they are equal of the height, thats mean that the logArea is full of logs
			clearLogArea();
			totalLogs = 0;
		}
		
		gotoxy(cordLogArea.getX(), cordLogArea.getY() + totalLogs); // Move the cursor on the nextLine (remember totalLogs have incrase before, no need to incrase it again)
		
		CHAR tempBuff[] = "[ERROR] Failed to write the log on file";
		setColor(FOREGROUND_RED);
		WriteConsole(hConsole, tempBuff, strlen(tempBuff), &tmp, NULL); 
		logArea -> setTotalPrintedLogs(++totalLogs); // incrase totalLogs
	}
	
	setColor(defaultColor);
	delete prefix;
}

VOID Window::clearLogArea() {
	setColor(defaultColor);
	gotoxy(cordLogArea);
	for(int i = 0; i < logArea -> getHeight(); i++) {
		for(int j = 0; j < logArea -> getWidth() -1;j++) {
			putchar(' ');
		}
		gotoxy(currentCursorPosition -> X, currentCursorPosition -> Y + 1);
	}
}


// Prints the map
void Window::printMap() {
    gotoxy(mapMarginLeft,mapMarginTop); // Setting Cursor on specific position
    setColor(map-> getForeGround(), map -> getBackGround()); // Change the color of the text

    int rows = map -> getRows();
    int columns = map -> getColumns();

    for(int row = 0; row < rows;row++) {	
        for(int column = 0; column < columns; column++) {
        	char ch = map->getCharAt(row,column);
        	if(ch == '@' || ch == '*') {
        		ch = 219;
			}
            putchar(ch); // Prints char by char
        }
        gotoxy(currentCursorPosition -> X, currentCursorPosition -> Y + 1); // Setting the cursor on the nextLine
    }
	
	setColor(defaultColor);
}


// Prints the LogArea inside the window
void Window::printLogArea() {
    setColor(defaultColor);
    printBox(logAreaMarginLeft, logAreaMarginTop + mapMarginTop + map -> getRows(), logArea -> getHeight() + 2, logArea -> getWidth() + 2);
}


// Prints a box inside the window on specific position
void Window::printBox(int x, int y, int height, int width) {

    gotoxy(x, y);

    int rows = height; // Getting the rows/height
    int columns = width; // Getting the columns/width

    // Print first line with *
    for(int i = 0; i < columns; i++) {
        std::cout << '*';
    }

    // Go to the nextLine
    gotoxy(x,currentCursorPosition -> Y + 1);

    // Make the sides of a box
    for(int row = 1; row < rows - 1;row++) {
        std::cout << '*'; // Print char on the left side of the box
        gotoxy(currentCursorPosition -> X + columns - 1, currentCursorPosition -> Y); // Move the cursor on the right side of the box
        std::cout << '*'; // Print char on the right side of the box
        gotoxy(x, currentCursorPosition -> Y + 1); // Move the cursor on the left side on the box but in the nextLine
    }

    // Print the last line with *
    for(int i = 0; i < columns; i++) {
        std::cout << '*';
    }
}

// Sets the cursor on specific position & also changes the attributes of the currentCursorPosition
void Window::gotoxy(int x, int y) {
    // Changes the attributes of the cursorPosition
    currentCursorPosition -> X = x;
    currentCursorPosition -> Y = y;
    SetConsoleCursorPosition(hConsole, *currentCursorPosition);
}

void Window::gotoxy(const Coordinate& cord) {
	gotoxy(cord.getX(),cord.getY());
}
// Changes the color for the foreground/background
void Window::setColor(DWORD color) {
    SetConsoleTextAttribute(hConsole, color); // Changing the color for the foreground/background to the chosen one
}

void Window::setColor(DWORD foreground, DWORD background) {
    setColor(foreground | background);
}

void Window::drawOnMap(char ch, int row, int column, DWORD foreground, DWORD background) {
	
	if(row < 0 || row >= map -> getRows() || column < 0 || column >= map -> getColumns()) {
       	std::ostringstream str;
       	str << "OutOfBound -> row: " << row << " column: " << column;
       	writeErrorLog(str.str());
        return;
    }
    
    gotoxy(column + mapMarginLeft, row + mapMarginTop);
    setColor(foreground,background);
    map -> setCharAt(row,column,ch);
    putchar(ch);
}

void Window::updateInfoBoard() {
	ArrayList<Pair>* pairs = findDifferences(prevList, infoBoard->getList());

    delete prevList;
	prevList = infoBoard->getList()->clone();

    int size = pairs->getSize();
	for(int i = 0; i < size; i++) {
		Pair pair = pairs->get(i);
		Info info = prevList->get(pair.x);
		clearInfoBoardRecordAt(pair);
		switch(pair.y) {
			case 0: {
				std::string id = info.getID();
				printInfoBoardID(pair.x, id);
				break;
			}
			case 1:
				printInfoBoardAvat(pair.x, info.getAvatar());
				break;
			case 2:
				printInfoBoardAlive(pair.x, info.isAlive());
				break;
			case 3:
				printInfoBoardStatus(pair.x, info.hasLost());
				break;
			case 4:
				printInfoBoardPoints(pair.x, info.getPoints());
				break;
		}
	}

	delete pairs;
}

ArrayList<Window::Pair>* Window::findDifferences(ArrayList<Info> *prevList, ArrayList<Info> *currList) {
	if(prevList->getSize() != currList->getSize()) {
		return NULL;
	}
	
	ArrayList<Pair>* result = new ArrayList<Pair>();
	Info prevInfo,currInfo;
	Pair currPair;
	for(int i = 0; i < prevList->getSize();i++) {
		currPair.x = i;
		prevInfo = prevList->get(i);
		currInfo = currList->get(i);
		
		if(prevInfo.getID() != currInfo.getID()) {
			currPair.y = 0;
			result->add(currPair);
		}
		
		if(prevInfo.getAvatar() != currInfo.getAvatar()) {
			currPair.y = 1;
			result->add(currPair);
		}
		
		if(prevInfo.isAlive() != currInfo.isAlive()) {
			currPair.y = 2;
			result->add(currPair);
		}
		
		if(prevInfo.hasLost() != currInfo.hasLost()) {
			currPair.y = 3;
			result->add(currPair);
		}
		
		if(prevInfo.getPoints() != currInfo.getPoints()) {
			currPair.y = 4;
			result->add(currPair);
		}		
	}	
	
	return result;
}

void Window::printInfoBoard() {
	printBox(mapMarginLeft + map->getColumns() + infoBoardMarginLeft, infoBoardMarginTop, infoBoard->getHeight(), infoBoard->getWidth());
	ArrayList<Info>* list = infoBoard->getList();

	int size = list->getSize();
	
	for(int i = 0; i < size; i++) {
		Info curr = list->get(i);
		printInfoRecord(i, curr);
	}	
}

void Window::printInfoRecord(int row, Info& info) {
	std::string id = info.getID();
	printInfoBoardID(row, id);
	printInfoBoardAvat(row, info.getAvatar());
	printInfoBoardAlive(row, info.isAlive());
	printInfoBoardStatus(row, info.hasLost());
	printInfoBoardPoints(row, info.getPoints());
	
	printInfoBoardDelims(row, '|');
}

void Window::printInfoBoardDelims(int row, char delim) {
	gotoxy(cordInfoBoard.getX() + 10, cordInfoBoard.getY() + row);
	
	putchar(delim);
	
	gotoxy(currentCursorPosition->X + 4, currentCursorPosition->Y);
	
	putchar(delim);
	
	gotoxy(currentCursorPosition->X + 8, currentCursorPosition->Y);
	
	putchar(delim);
	
	gotoxy(currentCursorPosition->X + 5, currentCursorPosition->Y);
	
	putchar(delim);
}

void Window::clearInfoBoardRecordAt(int row, int column) {
	
	gotoxy(cordInfoBoard.getX(), cordInfoBoard.getY() + row);
	
	int n,x;
	
	switch(column) {
		case 0:
			x = 1;
			n = 8;
			break;
		case 1:
			x = 12;
			n = 1;
			break;
		case 2:
			x = 16;
			n = 5;
			break;
		case 3:
			x = 24;
			n = 3;
			break;
		case 4:
			x = 29;
			n = 2;
			break;
		default : return;	
	}
	
	gotoxy(currentCursorPosition->X + x, currentCursorPosition->Y);
	
	for(int i = 0; i < n; i++) {
		putchar(' ');
	}
}

void Window::clearInfoBoardRecordAt(Pair pair) {
	clearInfoBoardRecordAt(pair.x, pair.y);
}

void Window::printInfoBoardID(int row, std::string& id) {
	gotoxy(cordInfoBoard.getX() + 1, cordInfoBoard.getY() + row);
	std::cout << id;
}

void Window::printInfoBoardAvat(int row, char ch) {
	gotoxy(cordInfoBoard.getX() + 12, cordInfoBoard.getY() + row);
	putchar(ch);
}

void Window::printInfoBoardAlive(int row, bool flag) {
	gotoxy(cordInfoBoard.getX() + 16, cordInfoBoard.getY() + row);
	
	switch(flag) {
		case true :
			setColor(FOREGROUND_GREEN);
			std::cout << "Alive";
			break;
		case false :
			setColor(FOREGROUND_RED);
			std::cout << "Dead";
			break;	
	}
	
	setColor(defaultColor);
}

void Window::printInfoBoardStatus(int row, bool lost) {
	gotoxy(cordInfoBoard.getX() + 24, cordInfoBoard.getY() + row);
	
	switch(lost) {
		case true :
			setColor(FOREGROUND_RED);
			std::cout << "BAN";
			break;
		case false :
			setColor(FOREGROUND_GREEN);
			std::cout << "OK";
			break;	
	}
	
	setColor(defaultColor);
}

void Window::printInfoBoardPoints(int row, DWORD points) {
	gotoxy(cordInfoBoard.getX() + 29, cordInfoBoard.getY() + row);
	
	printf("%2d",points);
}


Window::Pair::Pair() {
	x = 0;
	y = 0;
}

void Window::drawOnMap(char ch, const Coordinate& coordinate, DWORD foreground, DWORD background) {
    drawOnMap(ch,coordinate.getX(),coordinate.getY(),foreground,background);
}


// -----------------------------------------------------------------------------------------------------------------
void Window::drawOnMap(char ch, int row, int column, DWORD foreground) {
    drawOnMap(ch, row, column, foreground, map -> getBackGround()); // Uses the default background from the map
}

void Window::drawOnMap(char ch, const Coordinate& coordinate, DWORD foreground) {
    drawOnMap(ch, coordinate.getX(), coordinate.getY(), foreground);
}



// -----------------------------------------------------------------------------------------------------------------
void Window::drawOnMap(char ch, int row, int column) {
    drawOnMap(ch, row, column, map -> getForeGround(), map -> getBackGround());
}

void Window::drawOnMap(char ch, const Coordinate& coordinate) {
    drawOnMap(ch, coordinate.getX(), coordinate.getY());
}



// -----------------------------------------------------------------------------------------------------------------
void Window::drawOnMap(ObjectInfo& obj) {
    drawOnMap(obj.getAvatar(), obj.getPosition(), obj.getColor());
}

void Window::drawOnMap(ObjectInfo& obj,  Coordinate& newPosition) {
    drawOnMap(' ', obj.getPosition());
    drawOnMap(obj.getAvatar(), newPosition, obj.getColor());
}

