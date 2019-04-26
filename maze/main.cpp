#include <iostream>
#include "App/MainLoop/MainLoop.h"
#include "Tests/TestModule.h"

int main() {
    Factory*mainFactory = new SFMLGraphicsFactoryWithMazeGeneration(
            0.6 ,            //difficulty level
            25,             //tiles - x
            25,             //tiles - y
            800,            //window- x
            700,            //window- y
            69);           //random seed
    auto loop=new MainLoop(mainFactory);


    auto testModule = new TestModule(mainFactory,loop);

    if(testModule->passAllTests()){
        loop->start();
    }

}