//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_AGGRESSIVEINITIALIZATIONTEST_H
#define MAZE_AGGRESSIVEINITIALIZATIONTEST_H

#include "../AbstractTest.h"
#include "MainLoopTests.h"

class AggressiveInitializationTest: public MainLoopTests{
public:
    AggressiveInitializationTest(Factory *factory,MainLoop*_ml) : MainLoopTests(factory,_ml) {}

    std::string getTestName() override {
        return "AggressiveInitializationTest";
    }

protected:
    bool applyTest() override {
        return getMainLoop()->aggresiveInitialization();
    }
};
#endif //MAZE_AGGRESSIVEINITIALIZATIONTEST_H
