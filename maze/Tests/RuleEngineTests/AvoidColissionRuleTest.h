//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_AVOIDCOLISSIONTEST_H
#define MAZE_AVOIDCOLISSIONTEST_H

#include "../AbstractTest.h"

class AvoidCollisionRuleTest: public AbstractTest{
public:
    AvoidCollisionRuleTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "AvoidCollisionRuleTest";
    }

protected:

    /***
     * We initialize a wall and a ghost, and we attemt to hit those
     * if the rule engine approves this move, the test faills
     */
    bool applyTest() override {
        auto ruleEngine=getFactory()->getRuleEngine();
        auto map=getFactory()->getMap()->copy();
        auto wall=new Wall(RawMapPoint(0,0));
        auto *ghost=new Ghost(RawMapPoint(0,0));
        Action crashAction=DynamicObject::moveBackActionObject(ghost);

        map.overridePoint(RawMapPoint(0,0),wall);
        map.overridePoint(RawMapPoint(0,1),ghost);

        try{
            ruleEngine->applyActionObject(crashAction);
            return false;
        }catch (GenericRuleException&e){
            return true;
        }
    }
};
#endif //MAZE_AVOIDCOLISSIONTEST_H
