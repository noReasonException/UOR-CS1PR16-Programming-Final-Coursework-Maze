//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_MAPEXCEPTION_H
#define MAZE_MAPEXCEPTION_H

#include <bits/exception.h>

class GenericMapException: public std::exception{
public:
    virtual ~GenericMapException()= default;
};

class InvalidActionMoveException:public GenericMapException{
    virtual ~InvalidActionMoveException()= default;

};
#endif //MAZE_MAPEXCEPTION_H
