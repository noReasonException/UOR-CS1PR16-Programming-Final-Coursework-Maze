//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_ABSTRACTFACTORY_H
#define MAZE_ABSTRACTFACTORY_H

#include "../MainLoop/MainLoop.h"
#include "../RawMap/RawMap.h"
#include "../RuleEngine/RuleEngine.h"
#include "../GraphicsModule/Graphics.h"
#include "../GraphicsModule/SFMLGraphics/SFMLGraphics.h"
#include "ObjectFactory.h"


/***
 * The main abstract factory
 * has the responsibillity to resolve depedencies , and create for us every object we want
 */
class Factory {
public:
    virtual ~Factory()= default;
    virtual Graphics        *getGraphicsEngine()=0;
    virtual RawMap          *getMap()=0;
    virtual RuleEngine      *getRuleEngine()=0;
    virtual ObjectFactory   *getObjectFactory()=0;


    ActionObjectAdditionalInfo*allocAdditionalInfo(DynamicObject*object){
        switch(object->getType()){
            case OD_PLAYER:
                return allocPlayerAdditionalInfo(object);
            default:
                return new NOADDITIONALINFO;
        }
    }
    ActionObjectAdditionalInfo*allocPlayerAdditionalInfo(DynamicObject*object){
        auto agg = new PlayerAdditionalInfo();
        auto &fieldOfview=agg->getFieldOfView();
        Object* currObj = object;
        int a,b;
        for (int i = 0; i < fieldOfview.size(); ++i) {
            for (int j = 0; j < fieldOfview[i].size(); ++j) {
                a=object->getPosition().x-(fieldOfview.size()+i);
                b=object->getPosition().y-(fieldOfview[i].size()+j);
                if(a<=0||a>=getMap()->getLenx()||b<=0||b>=getMap()->getLeny()){
                    fieldOfview[i][j]='W';
                }
                else if(!(currObj=getMap()->to2DVector()[a][b])) {
                    fieldOfview[i][j] = 'R';

                }else if(currObj->getType()==OS_WALL){
                    fieldOfview[i][j]='W';
                }else if(currObj->getType()==OD_PLAYER){
                    fieldOfview[i][j]='P';
                }else if(currObj->getType()==OD_GHOST){
                    fieldOfview[i][j]='G';
                }
            }
        }
        return agg;
    }


    void freeAdditionalInfo(ActionObjectAdditionalInfo*ptr){delete(ptr);}


};
/***
 * The DefaultFactory class , provides the standard RawMap and RuleEngine Objects but leaves the
 * Graphics not implemented . You need to choose the more concrete implementations such as
 *  1)SFMLGraphicsFactory
 *  2)SFMLGraphicsFactoryWithMazeGeneration
 *
 */
class DefaultFactory: public Factory{
    RawMap     *map= nullptr;
    RuleEngine *ruleEngine= nullptr;
protected:
    unsigned int rawmapx,rawmapy;
public:
    DefaultFactory(unsigned int rawmapx, unsigned int rawmapy) : rawmapx(rawmapx), rawmapy(rawmapy) {}
    virtual ~DefaultFactory(){
        delete(map);
        map= nullptr;
        delete(ruleEngine);
        ruleEngine= nullptr;
    }
public:
    RawMap *getMap() override {
        if(map)return map;
        auto graphicsEngine=getGraphicsEngine();
        RawMap* retval= map=new RawMap(rawmapx,rawmapy);
        retval->subscribeToNotifications(graphicsEngine->getNotificationFunctor());
        return retval;
    }

    RuleEngine *getRuleEngine() override {
        return (!ruleEngine)?ruleEngine=new RuleEngine(getMap()):ruleEngine;
    }
};

class SFMLGraphicsFactory: public DefaultFactory{
protected:
    unsigned int windowx,windowy;
    Graphics        *graphics= nullptr;
    ObjectFactory   *objectFactory= nullptr;
public:
    SFMLGraphicsFactory(unsigned int rawmapx,unsigned int rawmapy,unsigned int windowx, unsigned int windowy) :
    DefaultFactory(rawmapx,rawmapy),
    windowx(windowx), windowy(windowy) {}
    virtual ~SFMLGraphicsFactory(){
        delete(graphics);
        graphics= nullptr;
        delete(objectFactory);
        objectFactory=nullptr;
    }

public:

    Graphics *getGraphicsEngine() override {
        return (!graphics)?graphics=new SFMLGraphics((Factory*)this,windowx,windowy):graphics;}
    ObjectFactory*getObjectFactory(){
        return (!objectFactory)?objectFactory=new SFMLObjectFactory():objectFactory;
    }
};
class SFMLGraphicsFactoryWithMazeGeneration:public SFMLGraphicsFactory{
    int rseed;
    float diff;

public:
    SFMLGraphicsFactoryWithMazeGeneration(float _diff,unsigned int rawmapx, unsigned int rawmapy, unsigned int windowx,
                                          unsigned int windowy,int _rseed):
                                          SFMLGraphicsFactory(rawmapx, rawmapy, windowx,windowy),rseed(_rseed),diff(_diff) {}
    virtual ~SFMLGraphicsFactoryWithMazeGeneration()= default;
    ObjectFactory*getObjectFactory(){
        return (!objectFactory)?objectFactory=new SFMLObjectFactoryWithLevelGeneration(diff,rseed,rawmapx,rawmapy):objectFactory;
    }
};

#endif //MAZE_ABSTRACTFACTORY_H
