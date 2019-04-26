//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_GETPOINTTEST_H
#define MAZE_GETPOINTTEST_H

#include "../AbstractTest.h"
/**
 * We assume that there is at least 1x1 RawMap
 */
class GetPointTest: public AbstractTest{
public:
    GetPointTest(Factory *factory) : AbstractTest(factory) {

    }

    std::string getTestName() override {
        return "GetPointTest";
    }

protected:
    bool applyTest() override {
        auto map=getFactory()->getMap();
        int lenx=map->getLenx(),leny=map->getLeny();
        return map->to2DVector()[lenx-1][leny-1]==map->getPoint(RawMapPoint(lenx-1,leny-1));
    }
};
#endif //MAZE_GETPOINTTEST_H
