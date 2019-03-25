//
// Created by mpampis on 3/23/17.
//

#include "Map.h"
#include "../Move.h"

Map::Map(const std::string& fileName) {
    std::ifstream file(fileName.c_str());
    char ch;
    file.exceptions(std::ios::badbit|std::ios::failbit);
    file >> rows;
    file >> columns;
    file.get();
    map = new char*[rows];
    this->rows=rows;
    this->columns=columns;

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




void Map::draw(ObjectInfo *obj) {
    this->map[obj->getPosition().getX()][obj->getPosition().getY()]=obj->getAvatar();

}


void Map::setCharAt(int row, int column, char ch) {
    if(row < 0 || row >= rows || column < 0 || column >= columns) {
        std::cout << "OutOfBound: " << row << ',' << column << std::endl;
        return;
    }

    map[row][column] = ch;

}


void Map::setCharAt(Coordinate position, char ch) {
    setCharAt(position.getY(),position.getX(),ch);
}


char Map::getCharAt(int row, int column) {
    return map[row][column];
}


char Map::getCharAt(Coordinate position) {
    return getCharAt(position.getX(),position.getY());
}


bool Map::existObject(int row, int column) {
    return getCharAt(row,column) != ' ' or(getCharAt(row,column)>='A' and getCharAt(row,column)<='Z');
}


bool Map::existObject(Coordinate position) {
    return existObject(position.getY(),position.getX());
}


void Map::print() {
    std::cout<<std::endl;
    for(int i = 0;i < rows;i++) {
        for(int j = 0;j < columns;j++) {
            std::cout <<" "<<map[i][j];
        }
        std::cout << std::endl;
    }
}

int Map::getRows() {
    return this->rows;
}

int Map::getColums() {
    return this->columns;
}

void Map::DumbDraw(int x, int y, char elem) {
    this->map[x][y]=elem;
}

void Map::Clear() {
    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if(this->map[i][j]=='C' or this->map[i][j]=='F' or this->map[i][j]=='.' or (this->map[i][j]>='A' and this->map[i][j]<='Z')){
                this->map[i][j]=' ';
            }
        }
    }

}
//return 1 if move is valid
//return 0 if not valid due to wall
//return 'A' - 'Z' if not valid due to player (player representation)
int Map::existObject(Coordinate &position, int Move) {
    switch (Move){
        case UP:
            return this->map[position.getX()-1][position.getY()]=='@' or this->map[position.getX()-1][position.getY()]=='*';
        case DOWN:
            return this->map[position.getX()+1][position.getY()]=='@' or this->map[position.getX()+1][position.getY()]=='*';
        case LEFT:
            return this->map[position.getX()][position.getY()-1]=='@' or this->map[position.getX()][position.getY()-1]=='*';
        case RIGHT:
            return this->map[position.getX()][position.getY()+1]=='@' or this->map[position.getX()][position.getY()+1]=='*';
    }
    return -1;
}

/*bool Map::existObject(int row, int column, int Move) {
    return this->existObject(*new Coordinate(row,column),Move); //TODO:fix
}*/

