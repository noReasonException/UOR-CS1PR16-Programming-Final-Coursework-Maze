#pragma once
#include <Windows.h>

#include "../../Utilities/ArrayList.h"
#include "Info.h"

#define DEFAULT_WIDTH_INFO 34
#define DEFAULT_HEIGHT_INFO 6

class InfoBoard {
public:
	InfoBoard();
	~InfoBoard();

	void addPlayer(PlayerInfo& playerInfo);
	void setAlive(const std::string& id, bool flag);
	void setLost(const std::string& id, bool flag);
	void increasePoints(const std::string& id);


	int getWidth();
	int getHeight();
	ArrayList<Info>* getList();
private:
	
	Info* findByID(const std::string& id);
	
	ArrayList<Info>* list;
	int height;
	int width;
};

