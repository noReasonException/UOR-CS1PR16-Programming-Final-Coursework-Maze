//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_OVERIDEPOINTTEST_H
#define MAZE_OVERIDEPOINTTEST_H

#include "../AbstractTest.h"

class OverridePointTest: public AbstractTest{
public:
    OverridePointTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "OverridePointTest";
    }

protected:
    bool applyTest() override {
        auto map=getFactory()->getMap()->copy();
        Object* ObjectOn00=map.getPoint(RawMapPoint(0,0));
        Object* ObjectOverride=new Wall(RawMapPoint(0,0));
        map.overridePoint(RawMapPoint(0,0),ObjectOverride);
        return ObjectOverride==map.getPoint(RawMapPoint(0,0));
    }
};
#endif //MAZE_OVERIDEPOINTTEST_H
