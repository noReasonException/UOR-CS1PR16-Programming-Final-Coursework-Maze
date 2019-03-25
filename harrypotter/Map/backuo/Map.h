//
// Created by mpampis on 3/23/17.
//

#ifndef HARRYPOTTER_MAP_H
#define HARRYPOTTER_MAP_H



#include <string>
#include <fstream>
#include <iostream>
#include <afxres.h>
#include "../Coordinate/Coordinate.h"
#include "../ObjectInfo/ObjectInfo.h"

class Map {
public:
    Map(const std::string& fileName);
    ~Map();
    void  draw(ObjectInfo* obj); //αλλαγη
    void  setCharAt(int row, int column, char ch);
    void  setCharAt(Coordinate position, char ch);

    char  getCharAt(int row, int column);
    char  getCharAt(Coordinate position);


    bool  existObject(int row, int column,int Move);
    int   existObject(Coordinate& position,int Move);
    void  DumbDraw(int x,int y,char elem);

    void  Clear();

    bool  existObject(int row, int column);

    bool  existObject(Coordinate position);
    void  print();
    int   getRows();
    int   getColums();
private:

    char **map;
    int  rows;
    int  columns;

};


#endif //HARRYPOTTER_MAP_H
