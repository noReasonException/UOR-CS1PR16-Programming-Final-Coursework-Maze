//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_APPLYACTIONOBJECTTEST_H
#define MAZE_APPLYACTIONOBJECTTEST_H

#include "../AbstractTest.h"

/***
 * We assume that the GetPointTest has already succeded
 */
class ApplyActionObjectTest: public AbstractTest{
public:
    ApplyActionObjectTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "ApplyActionObjectTest";
    }

protected:
    bool applyTest() override {
        auto map=getFactory()->getMap()->copy();
        Object* ObjectOn00=new Wall(RawMapPoint(0,0));
        map.applyActionObject(DynamicObject::moveRightActionObject(ObjectOn00));
        return ObjectOn00==map.getPoint(RawMapPoint(1,0));

    }
};
#endif //MAZE_APPLYACTIONOBJECTTEST_H
