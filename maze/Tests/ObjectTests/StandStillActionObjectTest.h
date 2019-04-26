//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_STANDSTILLACTIONOBJECTTEST_H
#define MAZE_STANDSTILLACTIONOBJECTTEST_H

#include "../AbstractTest.h"

class StandStillActionObjectTest: public AbstractTest{
public:
    StandStillActionObjectTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "StandStillActionObjectTest";
    }

protected:
    bool applyTest() override {
        auto testObject=new Wall(RawMapPoint(1,1));
        auto doingNothingAction=Object::standStillActionObject(testObject);
        return doingNothingAction.actionType==MSTAND &&
               doingNothingAction.from==doingNothingAction.to;
    }
};
#endif //MAZE_STANDSTILLACTIONOBJECTTEST_H
