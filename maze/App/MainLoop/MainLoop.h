//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_MAINLOOP_H
#define MAZE_MAINLOOP_H


#include "../RawMap/RawMap.h"
#include "../RuleEngine/RuleEngine.h"
#include "../ProjectFactory/Factory.h"
#include "../ProjectFactory/ObjectFactory.h"
#include "../Logger/Logger.h"
class MainLoop: private Logger {

public:
    /*Tests*/
    friend class AggressiveInitializationTest;
    friend class LoadObjectsTest;

    MainLoop(Factory *factory);
    virtual ~MainLoop()= default;
    bool start();

private:
    Factory *factory ;//DI Factory
    std::vector<StaticObject*>*staticObjects;
    std::vector<DynamicObject*>*dynamicObjects;


    /***
     * forces the factory to load everything in advance , avoiding possible delays later
     * @return true on success
     */
    bool aggresiveInitialization();
    /***
     * load the Objects into local attributes
     * @return true on success
     */
    bool loadObjects();
    bool drawStaticObjects();
    bool drawDynamicObjects();
    /***
     * The main loop
     * @return true on success
     */
    bool mainLoop();



};


#endif //MAZE_MAINLOOP_H
