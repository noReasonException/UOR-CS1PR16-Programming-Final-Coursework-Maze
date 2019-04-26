//
// Created by stefan on 19/04/19.
//

#ifndef MAZE_PRICE_H
#define MAZE_PRICE_H
#include "../StaticObject.h"

class Price: public StaticObject{


public:
    Price(RawMapPoint position) : StaticObject(position) {}
    virtual ~Price()= default;

    objectType getType() override {
        return OS_PRICE;
    }
};
#endif //MAZE_PRICE_H
