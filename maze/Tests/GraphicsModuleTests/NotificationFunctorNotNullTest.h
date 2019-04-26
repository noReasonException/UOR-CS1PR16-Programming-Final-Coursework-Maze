//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_NOTIFICATIONFUNCTORNOTNULL_H
#define MAZE_NOTIFICATIONFUNCTORNOTNULL_H

#include "../AbstractTest.h"

class NotificationFunctorNotNullTest : public AbstractTest{

public:
    NotificationFunctorNotNullTest(Factory *factory) : AbstractTest(factory) {}

    bool applyTest() override {
        return getFactory()->getGraphicsEngine()->getNotificationFunctor()!= nullptr;
    }

    std::string getTestName() override {
        return "NotificationFunctorNotNullTest";
    }


};
#endif //MAZE_NOTIFICATIONFUNCTORNOTNULL_H
