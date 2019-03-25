//
// Created by stefstef on 5/4/2017.
//

#ifndef GHOST_ALLPLAYERSAREKILLEDEXCEPTION_H
#define GHOST_ALLPLAYERSAREKILLEDEXCEPTION_H


#include <exception>
#include <stdexcept>

class AllPlayersAreKilledException : std::logic_error{
public:
    AllPlayersAreKilledException():std::logic_error("All Players Are dead :( "){}
};


#endif //GHOST_ALLPLAYERSAREKILLEDEXCEPTION_H
