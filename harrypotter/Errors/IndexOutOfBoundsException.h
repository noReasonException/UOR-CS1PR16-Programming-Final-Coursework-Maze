//
// Created by mpampis on 1/5/2017.
//

#ifndef HARRY_INDEXOUTOFBOUNDSEXCEPTION_H
#define HARRY_INDEXOUTOFBOUNDSEXCEPTION_H

#include <exception>
#include <stdexcept>

class IndexOutOfBoundsException : std::out_of_range {
public:
	IndexOutOfBoundsException(std::string str) :std::out_of_range(str) {}

};

#endif //HARRY_INDEXOUTOFBOUNDSEXCEPTION_H
