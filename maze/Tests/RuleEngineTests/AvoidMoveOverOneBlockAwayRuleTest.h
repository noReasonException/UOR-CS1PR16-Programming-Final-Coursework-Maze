//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_AVOIDMOVEOVERONEBLOCKAWAYRULETEST_H
#define MAZE_AVOIDMOVEOVERONEBLOCKAWAYRULETEST_H

#include "../AbstractTest.h"

class AvoidMoveOverOneBlockAwayRuleTest: public AbstractTest{
public:
    AvoidMoveOverOneBlockAwayRuleTest(Factory *factory) : AbstractTest(factory) {}

    std::string getTestName() override {
        return "AvoidMoveOverOneBlockAwayRuleTest";
    }

protected:
    bool applyTest() override {
        auto ruleEngine=getFactory()->getRuleEngine();
        auto map=getFactory()->getMap()->copy();
        auto *ghost=new Ghost(RawMapPoint(0,0));
        Action moreThanOneBlockAction=Action(MFRONT,ghost->getPosition(),RawMapPoint(map.getLenx()-1,map.getLeny()-1),ghost);


        try{
            ruleEngine->applyActionObject(moreThanOneBlockAction);
            return false;
        }catch (GenericRuleException&e){
            return true;
        }
    }
};
#endif //MAZE_AVOIDMOVEOVERONEBLOCKAWAYRULETEST_H
