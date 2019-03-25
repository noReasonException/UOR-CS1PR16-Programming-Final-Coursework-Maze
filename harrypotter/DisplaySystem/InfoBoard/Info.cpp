#include "Info.h"

Info::Info(PlayerInfo& playerInfo) {
	id = playerInfo.getPlayer().getId();
	avatar = playerInfo.getAvatar();
	color = playerInfo.getColor();
	
	points = 0;
	alive = true;
	lost = false;
	
}

Info::Info() {
	id = "err";
	avatar = ' ';
	color = 0;
	
	points = 0;
	alive = false;
	lost = true;
}

// Setters 



void Info::setID(const std::string& id) {
	this->id = id;
}

void Info::setAvatar(char avatar) {
	this->avatar = avatar;
}

void Info::setAlive(bool flag) {
	alive = flag;
}

void Info::setLost(bool flag) {
	lost = flag;
}

void Info::setPoints(DWORD points) {
	this->points = points;
}

void Info::increasePoints(DWORD value) {
	points += value;
}

void Info::setColor(DWORD color) {
	this->color = color;
}

// Getters

std::string Info::getID() {
	return id;
}

char Info::getAvatar() {
	return avatar;
}

bool Info::isAlive() {
	return alive;
}

bool Info::hasLost() {
	return lost;
}

DWORD Info::getPoints() {
	return points;
}

DWORD Info::getColor() {
	return color;
}

bool Info::operator==(const Info& other) const {
	return this->id == other.id;
}
