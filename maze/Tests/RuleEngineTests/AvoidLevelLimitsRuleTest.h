//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_AVOIDLEVELLIMITSTEST_H
#define MAZE_AVOIDLEVELLIMITSTEST_H

#include "../AbstractTest.h"

class AvoidLevelLimitsRuleTest: public AbstractTest{
public:
    AvoidLevelLimitsRuleTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "AvoidLevelLimitsRuleTest";
    }

protected:
    bool applyTest() override {
        auto ruleEngine=getFactory()->getRuleEngine();
        auto map=getFactory()->getMap()->copy();
        auto *ghost=new Ghost(RawMapPoint(0,0));
        Action outOfScopeAction=DynamicObject::moveBackActionObject(ghost);


        try{
            ruleEngine->applyActionObject(outOfScopeAction);
            return false;
        }catch (GenericRuleException&e){
            return true;
        }
    }
};
#endif //MAZE_AVOIDLEVELLIMITSTEST_H
