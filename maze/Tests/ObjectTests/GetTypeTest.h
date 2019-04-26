//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_GETTYPETEST_H
#define MAZE_GETTYPETEST_H

#include "../AbstractTest.h"

class GetTypeTest: public AbstractTest{
public:
    GetTypeTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "GetTypeTest";
    }

protected:
    bool applyTest() override {
        for(auto every:*getFactory()->getObjectFactory()->loadDynamicObjects()){
            if(every->getType()!=OD_GHOST &&
               every->getType()!=OD_MOVINGWALL&&
               every->getType()!=OD_PLAYER)
                return false;

        }
        for(auto every:*getFactory()->getObjectFactory()->loadstaticObjects()){
            if(every->getType()!=OS_WALL &&
               every->getType()!=OS_PRICE)
                return false;
        }
        return true;
    }
};
#endif //MAZE_GETTYPETEST_H
