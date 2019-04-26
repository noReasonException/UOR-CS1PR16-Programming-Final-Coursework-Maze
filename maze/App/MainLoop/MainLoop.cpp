//
// Created by stefan on 17/04/19.
//

#include "MainLoop.h"

bool MainLoop::aggresiveInitialization() {
    return  factory->getMap()&&
            factory->getRuleEngine()&&
            factory->getGraphicsEngine()&&
            factory->getObjectFactory();

}

MainLoop::MainLoop(Factory *factory) : factory(factory) {}

bool MainLoop::start() {
    return aggresiveInitialization()&&
    loadObjects()&&
    drawStaticObjects()&&
    mainLoop();
}

bool MainLoop::loadObjects() {
    return  (this->staticObjects=factory->getObjectFactory()->loadstaticObjects())&&
            (this->dynamicObjects=factory->getObjectFactory()->loadDynamicObjects());


}

bool MainLoop::drawStaticObjects() {

    for(StaticObject*every:*staticObjects){
        Action curr = Object::standStillActionObject(every);
        try{

            factory->getRuleEngine()->applyActionObject(curr);
            factory->getMap()->applyActionObject(curr);

        }catch (GenericRuleException&e){
            this->error(e);

        }catch(std::exception&e){
            return false;
        }

    }
    return true;
}
/***
 * This method draws the dynamic objects into memory
 * @return true if the loop needs to be continued , false if the game is over
 *  There are 2 ways for the game to be over
 *      1)a std::exception happens (something strange , a bug maybe?)
 *      2)we are run out of players(All players are dead)
 *      3)Some player has take the price
 */
bool  MainLoop::drawDynamicObjects() {
    bool hasNoOtherPlayers=true;
    ActionObjectAdditionalInfo*tmp;
    for(DynamicObject*every:*dynamicObjects){
        if (__glibc_unlikely(every->getType()==OD_PLAYER&&every->isVisible()))hasNoOtherPlayers=false;
        Action curr = every->nextActionObject(tmp=factory->allocAdditionalInfo(every));
        factory->freeAdditionalInfo(tmp);
        try{
            factory->getRuleEngine()->applyActionObject(curr);          //is the requested move a valid one?
            factory->getMap()->applyActionObject(curr);                 //draw it!
            every->applyQualifyingActionObject(curr);                   //inform the object for the position change

        }catch (GenericRuleException&e){
            this->error(e);                                             //logger
            Action responce=every->failedActionObjectHandler(curr,e);   //inform the object for the nature of the error
            if(responce.actionType==IPRICETAKEN){                       //if price is taken
                return false;                                           //stop the loop
            }
        }catch (std::exception&e){
            this->error(e);
            return false;
        }

    }
    return !hasNoOtherPlayers;                                                        //loop again!
}

bool MainLoop::mainLoop() {
    while(1){
        system("sleep 0.5");
        if(!drawDynamicObjects()){
            break;
        }

    }
    this->info("Game Over");
    while(1){

    }
    return true;
}