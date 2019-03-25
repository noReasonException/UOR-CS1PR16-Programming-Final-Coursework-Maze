//
// Created by mpampis on 3/23/17.
//

#ifndef HARRYPOTTER_MAP_H
#define HARRYPOTTER_MAP_H

#include <windows.h>

#include <string>
#include <fstream>
#include <iostream>
#include "../Coordinate/Coordinate.h"
#include "../ObjectInfo/ObjectInfo.h"
#include "../Move.h"
class Map {
public:
    Map(const char fileName[], DWORD foreground, DWORD background);

    ~Map();

    void draw(ObjectInfo& obj, Coordinate& newPosition);
    void draw(ObjectInfo& obj);

    void setCharAt(int row, int column, char ch);
    void setCharAt(Coordinate position, char ch);

    char getCharAt(int row, int column) const;
    char getCharAt(Coordinate position) const;

    bool existObject(int row, int column) const;
    bool existObject(Coordinate position) const;



    int   existObject(Coordinate& position,int Move);



    void print();



    DWORD getForeGround();
    DWORD getBackGround();

    int getRows()const ;
    int getColumns()const ;
    void setForeGround(DWORD foreground);
    void setBackGround(DWORD background);

    char** map; //TODO : change here
private:
    int rows;
    int columns;
    DWORD foreground;
    DWORD background;
};


#endif //HARRYPOTTER_MAP_H
