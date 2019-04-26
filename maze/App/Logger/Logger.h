//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_LOGGER_H
#define MAZE_LOGGER_H


#include <string>

/***
 * class logger
 * Every class who wants to say something to the outside world , needs to derive from this
 * @TODO support print levels
 */
class Logger {
    bool hasLogs;
public:
    /***
     * By initializing hasLogs=false the logger stays silent
     * @param hasLogs
     */
    Logger(bool hasLogs);

    Logger();
    virtual ~Logger()= default;

public:

    void debug(std::string msg);
    void info(std::string msg);
    void warn(std::string msg);
    void error(std::exception&e,std::initializer_list<std::string> msglist);
    void error(std::string msg);
    void error(std::exception&e);
    void critical(std::exception&e,std::initializer_list<std::string> msglist);
    void critical(std::string msg);
    void critical(std::exception&e);

};


#endif //MAZE_LOGGER_H
