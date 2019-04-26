//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_LOADOBJECTSTEST_H
#define MAZE_LOADOBJECTSTEST_H

#include "../AbstractTest.h"

class LoadObjectsTest: public MainLoopTests{
public:
    LoadObjectsTest(Factory *factory, MainLoop *_ml) : MainLoopTests(factory, _ml) {}

    std::string getTestName() override {
        return "LoadObjectsTest";
    }

protected:
    bool applyTest() override {
        return getMainLoop()->loadObjects();
    }
};
#endif //MAZE_LOADOBJECTSTEST_H
