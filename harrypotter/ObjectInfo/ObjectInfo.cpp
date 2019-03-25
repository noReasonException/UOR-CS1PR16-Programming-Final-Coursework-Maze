//
// Created by sotiris on 3/23/2017.
//
#include "ObjectInfo.h"

ObjectInfo::ObjectInfo(char _Avatar, Coordinate &StartPosition) :position(StartPosition),alive(true),Avatar(_Avatar),OfficialAvatar(_Avatar),visible(true),killedByMistake(false){
    this->setColor(0);
}

ObjectInfo::ObjectInfo(char _Avatar):position(*new Coordinate(0,0)),alive(true),Avatar(_Avatar),OfficialAvatar(_Avatar),visible(true),killedByMistake(false) {//TODO// fix

}


Coordinate &ObjectInfo::getPosition() {
    return this->position;
}

void ObjectInfo::setPosition(Coordinate _position) {
    this->position=_position;
}

char ObjectInfo::getAvatar() {
    return this->Avatar;
}

void ObjectInfo::setAvatar(char _Avatar) {
    this->Avatar=_Avatar;
}

void ObjectInfo::setColor(DWORD color) {
    this->color=color;
}

DWORD ObjectInfo::getColor() const {
    return this->color;
}

bool ObjectInfo::isAlive() {
    return this->alive;
}

void ObjectInfo::kill() {
    this->alive= false;
    this->Avatar='X';
}

void ObjectInfo::revive() {
    this->alive=true;
    this->Avatar=this->OfficialAvatar;
}

bool ObjectInfo::isVisible() {
    return this->visible;
}

void ObjectInfo::setVisible(bool status) {
    this->visible= status;
}

bool ObjectInfo::iskilledByMistake() {
    return this->killedByMistake;

}

void ObjectInfo::setkilledByMistake() {
    this->killedByMistake=true;
}


