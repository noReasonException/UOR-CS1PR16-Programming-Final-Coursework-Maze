//
// Created by StefStef on 4/28/2017.
//

#include "Graph.h"

Graph::Graph(Map &_refMap):refMap(_refMap){

    this->msize=(refMap.getRows()*refMap.getColumns());
    this->initializer();
    this->loadGraphFromMap();

}
int Graph::toID(int x, int y) {
    return (x*(this->refMap.getColumns()))+(y);
}
Coordinate* Graph::toCoordinate(int NodeID) {
    return new Coordinate(NodeID / this->refMap.getColumns(), NodeID %this->refMap.getColumns());
}

void Graph::initializer() {
    this->AdajencyMatrix=new int*[this->msize];
    for (int i = 0; i < this->msize; ++i) {
        this->AdajencyMatrix[i]=new int[this->msize];
        for (int j = 0; j < this->msize; ++j) {
            this->AdajencyMatrix[i][j]=0;
        }
    }
}

int Graph::isConnected(int NodeSrc, int NodeDest) {
    return this->AdajencyMatrix[NodeSrc][NodeDest] ||this->AdajencyMatrix[NodeDest][NodeSrc] ;
}

void Graph::Connect(int NodeSrc, int NodeDest, int Weight) {
    this->AdajencyMatrix[NodeSrc][NodeDest]=Weight;
    this->AdajencyMatrix[NodeDest][NodeSrc]=Weight;

}

void Graph::loadGraphFromMap() {
    for (int i = 0; i < this->refMap.getRows(); ++i) {
        for (int j = 0; j < this->refMap.getColumns(); ++j) {
            if(this->refMap.getCharAt(i,j)==' '){
                this->ConnectAround(i,j);
            }
        }
    }

}

void Graph::printMatrix() {
    for (int i = 0; i < this->msize; ++i) {
        for (int j = 0; j < this->msize; ++j) {
            std::cout<<this->AdajencyMatrix[i][j]<<" |";
        }
        std::cout<<std::endl;
    }

}

void Graph::ConnectAround(int x, int y) {
    if(this->refMap.getCharAt(x-1,y)==' '){
        this->Connect(this->toID(x-1,y),this->toID(x,y));
    }
    if(this->refMap.getCharAt(x+1,y)==' '){
        this->Connect(this->toID(x+1,y),this->toID(x,y));
    }
    if(this->refMap.getCharAt(x,y-1)==' '){
        this->Connect(this->toID(x,y-1),this->toID(x,y));
    }
    if(this->refMap.getCharAt(x,y+1)==' '){
        this->Connect(this->toID(x,y+1),this->toID(x,y));
    }


}

void Graph::ClearConnections() {
    for (int i = 0; i < this->msize; ++i) {
        for (int j = 0; j < this->msize; ++j) {
            this->AdajencyMatrix[i][j]=0;
        }
    }

}

