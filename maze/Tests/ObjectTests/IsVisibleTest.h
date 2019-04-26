//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_ISVISIBLESETTERTEST_H
#define MAZE_ISVISIBLESETTERTEST_H

#include "../AbstractTest.h"

class IsVisibleTest: public AbstractTest{
public:
    IsVisibleTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "IsVisibleTest";
    }

protected:
    bool applyTest() override {
        auto testObject=new Wall(RawMapPoint(1,1));
        return testObject->setVisible(true)->isVisible();
    }
};
#endif //MAZE_ISVISIBLESETTERTEST_H
