//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_GETTERSTEST_H
#define MAZE_GETTERSTEST_H

#include "../AbstractTest.h"

class GettersTest: public AbstractTest{
public:
    GettersTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "GettersTest";
    }

protected:
    bool applyTest() override {
        auto map=getFactory()->getMap();
        return map->getLenx()==map->lenx&&map->getLeny()==map->leny;
    }
};
#endif //MAZE_GETTERSTEST_H
