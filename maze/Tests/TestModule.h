//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_TESTMODULE_H
#define MAZE_TESTMODULE_H

#include "../App/Logger/Logger.h"
#include "AbstractTest.h"
#include "GraphicsModuleTests/NotificationFunctorNotNullTest.h"
#include "MainLoopTests/AggressiveInitializationTest.h"
#include "MainLoopTests/LoadObjectsTest.h"
#include "ObjectTests/GetTypeTest.h"
#include "ObjectTests/IsVisibleTest.h"
#include "ObjectTests/StandStillActionObjectTest.h"
#include "RawMapTests/ApplyActionObjectTest.h"
#include "RawMapTests/GetPointTest.h"
#include "RawMapTests/GettersTest.h"
#include "RawMapTests/OverridePointTest.h"
#include "RuleEngineTests/AvoidColissionRuleTest.h"
#include "RuleEngineTests/AvoidLevelLimitsRuleTest.h"
#include "RuleEngineTests/AvoidMoveOverOneBlockAwayRuleTest.h"

/***
 * The Testing Module
 *
 * This is a simple class containing all the tests , by calling
 * .passAllTests() all the tests run , if every test returns true , the tests are passed and we are
 * ready to go!
 */
class TestModule : public Logger{
    Factory*factory;
    MainLoop*loop;
public:
    TestModule(Factory*_factory,MainLoop*_loop,bool haveLogs) : Logger(haveLogs),factory(_factory),loop(_loop) {}

    TestModule(Factory*_factory,MainLoop*_loop):TestModule(_factory,_loop,true){}

public:
    /***
     * Checks againist all tests
     * @return true on success
     */
    bool passAllTests(){
        return
            run(graphicsModuleTests())&&
            run(mainLoopTests())&&
            run(objectTests())&&
            run(rawMapTests())&&
            run(ruleEngineTests());
    }
    /***
     * Evaluates a list of tests
     * @param tests
     * @return
     */
    bool run(std::vector<AbstractTest*>tests){
        for(auto *test:tests){
            if(!test->run())return false;           //if the test fail , return false
            else delete(test);                      //else delete the test pointer
        }
        return true;

    }
    /**
     * The subscribed RawMap subsystem Tests
     * @return a vector with all AbstractTests
     */
    std::vector<AbstractTest*> rawMapTests() {
        return std::vector<AbstractTest *>({
            new ApplyActionObjectTest(factory),
            new GetPointTest(factory),
            new GettersTest(factory),
            new OverridePointTest(factory)});
    }
    std::vector<AbstractTest*> graphicsModuleTests(){
        return std::vector<AbstractTest*>({
            new NotificationFunctorNotNullTest(factory),
        });
    }
    std::vector<AbstractTest*> mainLoopTests() {
        return std::vector<AbstractTest *>({
            new AggressiveInitializationTest(factory, loop),
            new LoadObjectsTest(factory, loop)});
    }

    std::vector<AbstractTest*> objectTests() {
        return std::vector<AbstractTest *>({
            new GetTypeTest(factory),
            new IsVisibleTest(factory),
            new StandStillActionObjectTest(factory)

        });
    }
    std::vector<AbstractTest*> ruleEngineTests() {
        return std::vector<AbstractTest *>({
            new AvoidCollisionRuleTest(factory),
            new AvoidLevelLimitsRuleTest(factory),
            new AvoidMoveOverOneBlockAwayRuleTest(factory)
    });
    }
};
#endif //MAZE_TESTMODULE_H
