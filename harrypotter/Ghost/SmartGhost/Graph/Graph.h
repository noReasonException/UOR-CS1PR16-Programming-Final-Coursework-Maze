//
// Created by StefStef on 4/28/2017.
//

#ifndef GHOST_GRAPH_H
#define GHOST_GRAPH_H


#include "../../../Map/Map.h"

class Graph {
private:
    int **AdajencyMatrix;
    Map &refMap;
    int msize;
    void initializer();
    void ConnectAround(int x,int y);
    void loadGraphFromMap();
    void Connect(int NodeSrc,int NodeDest,int Weight=1);


public :

    void ClearConnections();
    inline int getAdajencyMatrix(int x,int y){return this->AdajencyMatrix[x][y];}
    inline int getSize()const{ return msize; }
    int isConnected(int NodeSrc,int NodeDest);
    void printMatrix();
    Graph(Map &_refMap);
    int toID(int x,int y);
    Coordinate* toCoordinate(int NodeID);

};


#endif //GHOST_GRAPH_H
