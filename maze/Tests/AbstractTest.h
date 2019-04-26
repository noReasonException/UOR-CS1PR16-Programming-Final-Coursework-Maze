//
// Created by stefan on 24/04/19.
//

#ifndef MAZE_ABSTRACTTEST_H
#define MAZE_ABSTRACTTEST_H

#include "../App/ProjectFactory/Factory.h"

class AbstractTest{
    Factory*factory;

public:


    AbstractTest(Factory *factory) : factory(factory) {}
    virtual ~AbstractTest(){}


    bool run(){
        beforeTest();
        bool retval=applyTest();
        afterTest();
        return retval;
    }
    virtual std::string getTestName()=0;

protected:
    Factory *getFactory() const {
        return factory;
    }


    virtual void beforeTest(){
        std::cout<<"Run "<<getTestName()<<std::endl;
    }
    virtual bool applyTest()=0;
    virtual void afterTest(){
        return;
    }

};
#endif //MAZE_ABSTRACTTEST_H
