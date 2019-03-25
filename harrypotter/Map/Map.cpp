//
// Created by mpampis on 3/23/17.
//

#include "Map.h"

Map::Map(const char fileName[], DWORD foreground=FOREGROUND_BLUE, DWORD background=BACKGROUND_BLUE):foreground(foreground),background(background) {
    std::ifstream file(fileName);
    char ch;
    file.exceptions(std::ios::badbit|std::ios::failbit);

    file >> rows;
    file >> columns;
    if(file.fail()){
        file.clear();
        std::cout<<"Invalid Map Format";
    }
    file.get();//get '\n'

    map = new char*[rows];
    this->rows=rows;
    this->columns=columns;
    file.exceptions(std::ios::failbit|std::ios::badbit);
    for(int row = 0; row < rows; row++) {
        map[row] = new char[columns]; // Creating the array little by little

        for(int column = 0; column < columns; column++) {

            map[row][column] = (char)file.get(); // Getting char by char
        }
        file.get(); // reading the '\n' in the end of the line
    }
}


// DeAllocate memory
Map::~Map() {

    for(int i = 0;i < rows;i++) {
        delete[] map[i];
    }

    delete[] map;
}


void Map::draw(ObjectInfo& obj, Coordinate& newPosition) {
    setCharAt(obj.getPosition(),' '); // Remove the old avatar from the map
    setCharAt(newPosition, obj.getAvatar()); // Redraw the avatar of the obj
}

void Map::draw(ObjectInfo& obj) {
    setCharAt(obj.getPosition(), obj.getAvatar()); // Redraw the avatar of the obj on it current position
}

void Map::setCharAt(int row, int column, char ch) {
    map[row][column] = ch;
}

void Map::setCharAt(Coordinate position, char ch) {
    setCharAt(position.getX(),position.getY(),ch);
}


char Map::getCharAt(int row, int column)const  {
    if(row<0 or column<0 or row>this->getRows()-1 or column>this->getColumns()-1) return '*';
    return map[row][column];
}


char Map::getCharAt(Coordinate position)const  {
    return getCharAt(position.getX(),position.getY());
}


bool Map::existObject(int row, int column)const  {
    return getCharAt(row,column) != ' ';
}


bool Map::existObject(Coordinate position) const  {
    return existObject(position.getX(),position.getY());
}
int Map::existObject(Coordinate &position, int Move) {
    switch (Move){
        case UP:
            return this->map[position.getX()-1][position.getY()]=='@' or this->map[position.getX()-1][position.getY()]=='*'  ;
        case DOWN:
            return this->map[position.getX()+1][position.getY()]=='@' or this->map[position.getX()+1][position.getY()]=='*'  ;
        case LEFT:
            return this->map[position.getX()][position.getY()-1]=='@' or this->map[position.getX()][position.getY()-1]=='*'  ;
        case RIGHT:
            return this->map[position.getX()][position.getY()+1]=='@' or this->map[position.getX()][position.getY()+1]=='*'  ;
    }
    return 0;
}


void Map::print() {
    for(int i = 0;i < rows;i++) {
        for(int j = 0;j < columns;j++) {
            std::cout << map[i][j];
        }
        std::cout << std::endl;
    }
}

void Map::setForeGround(DWORD foreground) {
    this -> foreground = foreground;
}

void Map::setBackGround(DWORD background) {
    this -> background = background;
}

DWORD Map::getForeGround() {
    return foreground;
}

DWORD Map::getBackGround() {
    return background;
}

int Map::getRows()const  {
    return rows;
}

int Map::getColumns()const {
    return columns;
}

