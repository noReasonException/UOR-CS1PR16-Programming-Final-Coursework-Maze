#include "InfoBoard.h"

InfoBoard::InfoBoard() {
	width = DEFAULT_WIDTH_INFO;
	height = DEFAULT_HEIGHT_INFO;
    list = new ArrayList<Info>();
}

InfoBoard::~InfoBoard() {
    delete list;
}

void InfoBoard::addPlayer(PlayerInfo& playerInfo) {
	list->add(playerInfo);
}

void InfoBoard::setAlive(const std::string& id, bool flag) {
	Info* info = findByID(id);
	if(info != NULL) {
		info->setAlive(flag);
	}
}

void InfoBoard::setLost(const std::string& id, bool flag) {
	Info* info = findByID(id);
	if(info != NULL) {
		info->setLost(flag);
	}
}

void InfoBoard::increasePoints(const std::string& id) {
	Info* info = findByID(id);
	if(info != NULL) {
		info->increasePoints(1);
	}
}


ArrayList<Info>* InfoBoard::getList() {
	return list;
}

Info* InfoBoard::findByID(const std::string& id) {
	Info tmp;
	tmp.setID(id);
	int index = list->indexOf(tmp);
	
	if(index == -1) {
		return NULL;
	}
	
	return &(list->get(index));
}

int InfoBoard::getWidth() {
	return width;
}

int InfoBoard::getHeight() {
	return height;
}
