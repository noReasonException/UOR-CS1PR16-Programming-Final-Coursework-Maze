//
// Created by stefan on 17/04/19.
//

#include <iostream>
#include "Logger.h"

void Logger::debug(std::string msg) {
    if(hasLogs)
        std::cout<<msg<<std::endl;
}

void Logger::info(std::string msg) {
    if(hasLogs)
        std::cout<<msg<<std::endl;

}

void Logger::warn(std::string msg) {
    if(hasLogs)
        std::cout<<msg<<std::endl;

}

void Logger::error(std::exception &e,std::initializer_list<std::string> msglist) {
    if(hasLogs){
        for (auto msg:msglist)std::cout<<" "<<msg;
        std::cout<<"what("<<e.what()<<")"<<std::endl;
    }


}

void Logger::error(std::string msg) {
    if(hasLogs)
        std::cout<<msg<<std::endl;

}

void Logger::critical(std::exception &e,std::initializer_list<std::string> msglist) {
    if(hasLogs){
        for (auto msg:msglist)std::cout<<" "<<msg;
        std::cout<<"what("<<e.what()<<")"<<std::endl;
    }

}
void Logger::critical(std::string msg) {
    std::cout<<msg<<std::endl;

}

void Logger::error(std::exception &e) {
    if(hasLogs)
        std::cout<<e.what()<<std::endl;
}

void Logger::critical(std::exception &e) {
    if(hasLogs)
        std::cout<<std::endl;
}

Logger::Logger(bool hasLogs) : hasLogs(hasLogs) {}

Logger::Logger():Logger(true) {}
