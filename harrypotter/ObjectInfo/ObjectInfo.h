//
// Created by sotiris on 3/23/2017.
//

#ifndef HARRYPOTTER_OBJECTINFO_H
#define HARRYPOTTER_OBJECTINFO_H

#include "../Coordinate/Coordinate.h"
#include "iostream"
#include <windows.h>
class ObjectInfo{
protected:
    Coordinate &position;
    char Avatar;
    char OfficialAvatar;
    DWORD color;
    bool alive;
    bool killedByMistake;
    bool visible;
public:
    ObjectInfo(char _Avatar,Coordinate &StartPosition);
    ObjectInfo(char _Avatar);
    Coordinate &getPosition();
    void setPosition(Coordinate _position);
    char getAvatar();
    void setAvatar(char _Avatar);
    void setColor(DWORD color);
    DWORD getColor() const;
    bool isAlive();
    void kill();
    void revive();
    bool iskilledByMistake();
    void setkilledByMistake();
    bool isVisible();
    void setVisible(bool status);
};
#endif //HARRYPOTTER_OBJECTINFO_H