//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_MAINLOOPTESTS_H
#define MAZE_MAINLOOPTESTS_H

#include "../../App/MainLoop/MainLoop.h"
#include "../AbstractTest.h"

class MainLoopTests:public AbstractTest{
    MainLoop*mainLoop;

protected:
    MainLoop *getMainLoop() const {
        return mainLoop;
    }

public:
    MainLoopTests(Factory *factory,MainLoop*_ml) : AbstractTest(factory),mainLoop(_ml) {}
};
#endif //MAZE_MAINLOOPTESTS_H
