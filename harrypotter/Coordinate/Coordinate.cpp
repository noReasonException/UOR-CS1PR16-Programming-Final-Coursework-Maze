//
// Created by stefan on 27/3/2017.
//

#include "Coordinate.h"

std::ostream&operator<<(std::ostream &os,const Coordinate &rhs){
    os<<rhs.getX()<<"-"<<rhs.getY();
    return os;
}

bool Coordinate::operator==(const Coordinate &rhs) {
    return this->getX() == rhs.getX() && this->getY() == rhs.getY();
}

Coordinate &Coordinate::operator=(Coordinate &rhs) {
    if (*this == rhs) {
        return *this;
    }
    this->x = rhs.getX();
    this->y = rhs.getY();
    return *(new Coordinate(rhs.getX(), rhs.getY()));
}

bool Coordinate::operator!=(Coordinate &rhs) {
    return !this->operator==(rhs);

}

Coordinate::Coordinate(const Coordinate &rhs) {
    this->x=rhs.getX();
    this->y=rhs.getY();

}

Coordinate *Coordinate::getNulledInstance() {
    if(Coordinate::SiglentonObject==NULL){
        Coordinate::SiglentonObject=new Coordinate(1,1);
    }
    return Coordinate::SiglentonObject;
}
Coordinate * Coordinate::SiglentonObject=NULL;
