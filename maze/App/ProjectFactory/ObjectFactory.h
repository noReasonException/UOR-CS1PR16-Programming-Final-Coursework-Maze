//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_OBJECTFACTORY_H
#define MAZE_OBJECTFACTORY_H

#include "../Object/StaticObject/StaticObject.h"
#include "../Object/DynamicObject/DynamicObject.h"
#include "../Object/StaticObject/Objects/Wall.h"
#include "Factory.h"
#include "../Object/DynamicObject/Objects/Player/Player.h"
#include "../Object/DynamicObject/Objects/MovingWall.h"
#include "../Object/DynamicObject/Objects/Ghost.h"
#include "../Object/StaticObject/Objects/Price.h"
#include "../Object/DynamicObject/Objects/Player/DeriveablePlayer.h"
#include <iostream>
#include <vector>

class ObjectFactory{
public:
    virtual ~ObjectFactory()= default;
    virtual std::vector<StaticObject*>* loadstaticObjects()=0;
    virtual std::vector<DynamicObject*>* loadDynamicObjects()=0;

};

class SFMLObjectFactory:public ObjectFactory{
    std::vector<StaticObject*>* staticObjects;
    std::vector<DynamicObject*>* dynamicObjects;
public:
    std::vector<StaticObject *> *getStaticObjects() const {
            return staticObjects;
    }

    std::vector<DynamicObject *> *getDynamicObjects() const {
            return dynamicObjects;
    }

   void freeStaticObjects() const {
        for(auto every:*getStaticObjects()){
            free(every);
        }
    }

    void freeDynamicObjects() const {
        for(auto every:*getDynamicObjects()){
            free(every);
        }
    }
    SFMLObjectFactory * setStaticObjects(std::vector<StaticObject *> *staticObjects) {
        SFMLObjectFactory::staticObjects = staticObjects;
        return this;
    }

    SFMLObjectFactory* setDynamicObjects(std::vector<DynamicObject *> *dynamicObjects) {
        SFMLObjectFactory::dynamicObjects = dynamicObjects;
        return this;
    }

    SFMLObjectFactory() {}


    virtual ~SFMLObjectFactory(){
        freeStaticObjects();
        freeDynamicObjects();
    }

    std::vector<StaticObject *> *loadstaticObjects() override {
        if(staticObjects!= nullptr)return staticObjects;
        auto retval=new std::vector<StaticObject*>();
        retval->push_back(new Price(RawMapPoint(22,22)));

        retval->push_back(new Wall(RawMapPoint(0,3)));

        retval->push_back(new Wall(RawMapPoint(0,17)));

        retval->push_back(new Wall(RawMapPoint(1,17)));

        retval->push_back(new Wall(RawMapPoint(2,16)));

        retval->push_back(new Wall(RawMapPoint(2,17)));

        retval->push_back(new Wall(RawMapPoint(2,24)));

        retval->push_back(new Wall(RawMapPoint(3,23)));

        retval->push_back(new Wall(RawMapPoint(3,24)));

        retval->push_back(new Wall(RawMapPoint(4,3)));

        retval->push_back(new Wall(RawMapPoint(4,15)));

        retval->push_back(new Wall(RawMapPoint(5,7)));

        retval->push_back(new Wall(RawMapPoint(5,8)));

        retval->push_back(new Wall(RawMapPoint(5,19)));

        retval->push_back(new Wall(RawMapPoint(6,8)));

        retval->push_back(new Wall(RawMapPoint(6,19)));

        retval->push_back(new Wall(RawMapPoint(7,8)));

        retval->push_back(new Wall(RawMapPoint(7,18)));

        retval->push_back(new Wall(RawMapPoint(7,19)));

        retval->push_back(new Wall(RawMapPoint(8,8)));

        retval->push_back(new Wall(RawMapPoint(8,14)));

        retval->push_back(new Wall(RawMapPoint(8,15)));

        retval->push_back(new Wall(RawMapPoint(8,16)));

        retval->push_back(new Wall(RawMapPoint(8,17)));

        retval->push_back(new Wall(RawMapPoint(8,18)));

        retval->push_back(new Wall(RawMapPoint(8,19)));

        retval->push_back(new Wall(RawMapPoint(8,20)));

        retval->push_back(new Wall(RawMapPoint(8,21)));

        retval->push_back(new Wall(RawMapPoint(9,5)));

        retval->push_back(new Wall(RawMapPoint(9,17)));

        retval->push_back(new Wall(RawMapPoint(9,18)));

        retval->push_back(new Wall(RawMapPoint(9,19)));

        retval->push_back(new Wall(RawMapPoint(9,20)));

        retval->push_back(new Wall(RawMapPoint(10,5)));

        retval->push_back(new Wall(RawMapPoint(10,10)));

        retval->push_back(new Wall(RawMapPoint(10,11)));

        retval->push_back(new Wall(RawMapPoint(10,17)));

        retval->push_back(new Wall(RawMapPoint(10,18)));

        retval->push_back(new Wall(RawMapPoint(10,19)));

        retval->push_back(new Wall(RawMapPoint(10,20)));

        retval->push_back(new Wall(RawMapPoint(11,0)));

        retval->push_back(new Wall(RawMapPoint(11,1)));

        retval->push_back(new Wall(RawMapPoint(11,5)));

        retval->push_back(new Wall(RawMapPoint(11,20)));

        retval->push_back(new Wall(RawMapPoint(12,0)));

        retval->push_back(new Wall(RawMapPoint(12,1)));

        retval->push_back(new Wall(RawMapPoint(12,2)));

        retval->push_back(new Wall(RawMapPoint(12,3)));

        retval->push_back(new Wall(RawMapPoint(12,4)));

        retval->push_back(new Wall(RawMapPoint(12,5)));

        retval->push_back(new Wall(RawMapPoint(12,9)));

        retval->push_back(new Wall(RawMapPoint(13,0)));

        retval->push_back(new Wall(RawMapPoint(13,1)));

        retval->push_back(new Wall(RawMapPoint(13,2)));

        retval->push_back(new Wall(RawMapPoint(13,3)));

        retval->push_back(new Wall(RawMapPoint(13,4)));

        retval->push_back(new Wall(RawMapPoint(14,0)));

        retval->push_back(new Wall(RawMapPoint(14,1)));

        retval->push_back(new Wall(RawMapPoint(14,2)));

        retval->push_back(new Wall(RawMapPoint(14,3)));

        retval->push_back(new Wall(RawMapPoint(14,15)));

        retval->push_back(new Wall(RawMapPoint(14,16)));

        retval->push_back(new Wall(RawMapPoint(14,23)));

        retval->push_back(new Wall(RawMapPoint(14,24)));

        retval->push_back(new Wall(RawMapPoint(18,0)));

        retval->push_back(new Wall(RawMapPoint(18,1)));

        retval->push_back(new Wall(RawMapPoint(19,13)));

        retval->push_back(new Wall(RawMapPoint(20,2)));

        retval->push_back(new Wall(RawMapPoint(20,3)));

        retval->push_back(new Wall(RawMapPoint(20,4)));

        retval->push_back(new Wall(RawMapPoint(20,13)));

        retval->push_back(new Wall(RawMapPoint(21,4)));

        retval->push_back(new Wall(RawMapPoint(21,13)));

        retval->push_back(new Wall(RawMapPoint(21,14)));

        retval->push_back(new Wall(RawMapPoint(22,13)));

        retval->push_back(new Wall(RawMapPoint(22,14)));


            return staticObjects=retval;
    }

    std::vector<DynamicObject *> *loadDynamicObjects() override {
        if(dynamicObjects!= nullptr)return dynamicObjects;
        auto retval=new std::vector<DynamicObject*>();
        retval->push_back(new DeriveablePlayer(RawMapPoint(2,2),3));
        retval->push_back(new DeriveablePlayer(RawMapPoint(4,2),3));
        retval->push_back(new Ghost(RawMapPoint(22,20)));
        retval->push_back(new Ghost(RawMapPoint(15,15)));
        retval->push_back(new Ghost(RawMapPoint(17,17)));



        return dynamicObjects=retval;
    }


};

class SFMLObjectFactoryWithLevelGeneration:public SFMLObjectFactory{
public:

    int sizex,sizey;
    float diff;
    std::vector<std::vector<int >> walls;
    std::vector<int>sets;
    RawMapPoint randomPoint(){
        return RawMapPoint(abs(rand()%(sizex)),abs(rand()%(sizey)));
    }
    RawMapPoint randomOnCollumn(int x){
        return RawMapPoint(x,abs(rand()%(sizey)));
    }
    RawMapPoint randomOnRow(int y){
        return  RawMapPoint(abs(rand()%(sizex)),y);
    }

    SFMLObjectFactoryWithLevelGeneration(float _diff,int _rseed,int x,int y):sizex(x),sizey(y),diff(_diff){
        for (int i = 0; i < x; ++i) {
            walls.push_back(getLineOfLen(y));
        }
        for (int j = 0; j < x * y; ++j) {
            sets.push_back(j);
        }
        for (int i = 0; i < 25; ++i) {
            connect(RawMapPoint(0,0),RawMapPoint(i,0));
            connect(RawMapPoint(0,sizey-1),RawMapPoint(i,sizey-1));

        }
        srand(_rseed);
        loadstaticObjects();
        loadDynamicObjects();

    }
    virtual ~SFMLObjectFactoryWithLevelGeneration()= default;
    void cls(){
        for (int j = 0; j < sizex*sizey; ++j) {
            sets[j]=j;
        }
    }
    int fromPointTo1D(RawMapPoint p){
        return sizex*p.x+p.y;
    }
    int connect(RawMapPoint p1,RawMapPoint p2){
        if(p1.x>=sizex||p1.x<0||p1.y>=sizey||p1.y<0||p2.x>=sizex||p2.x<0||p2.y>=sizey||p2.y<0)return 0;
        //if(haveConnection(p1,p2))return 0;
        sets[getHead(p1)]=sets[getHead(p2)];
        walls[p1.x][p1.y]=1;
        walls[p2.x][p2.y]=1;
        return 1;
    }
    int getHead(RawMapPoint p){
        return _getHead(fromPointTo1D(p));
    }
    int _getHead(int x){
        if(sets[x]!=x)return _getHead(sets[x]);
        return x;
    }
    bool haveConnection(RawMapPoint p1,RawMapPoint p2){return getHead(p1)==getHead(p2);}
    std::vector<int>getLineOfLen(int x){
        std::vector<int> retval;//optimised for rvalue return procedure , no pointer needed
        for (int i = 0; i < x; ++i) {
            retval.push_back(0);
        }
        return retval;
    }
    std::vector<StaticObject*>* getWalls(){
        std::vector<StaticObject*> *retval=new std::vector<StaticObject*>();

        for (int i = 0; i < sizex; ++i) {
            for (int j = 0; j < sizey; ++j) {
                if(walls[i][j]==0){
                    retval->push_back(new Wall(RawMapPoint(i,j)));
                }
            }
        }
        return retval;
    }

    RawMapPoint getNextRandomMove(RawMapPoint rmp){
        int i=abs(rand()%20);
        if(i<5){
            return rmp.incX(-1);
        }
        if(i<15){
            return rmp.incY(1);
        }
        if(i<20){
            return rmp.incX(1);
        }

    }

    void makeTunnel(RawMapPoint start,RawMapPoint end){
        cls();
        RawMapPoint cursor=start.incY(0); //this is just copy
        RawMapPoint nextc=cursor.incY(0); //this is also just a copy
        while(!haveConnection(start,end)){
            nextc=getNextRandomMove(cursor);
            if(connect(cursor,nextc)){
                cursor=nextc;
            }

        }
    }
    std::vector<StaticObject *> *loadstaticObjects() override {
        if(getStaticObjects()!= nullptr)return getStaticObjects();
        std::vector<StaticObject*>*retval;
        for (int j = 0; j < 15*(1-diff); ++j) {
            makeTunnel(randomOnRow(0),randomOnRow(sizey-1));
        }
        retval=getWalls();
        retval->push_back(new Price(getRandomFreePosition()));
        return setStaticObjects(retval)->getStaticObjects();
    }

    RawMapPoint getRandomFreePosition(){
        RawMapPoint retval=randomPoint();
        while(!walls[retval.x][retval.y]) {
            retval = randomPoint();
        }
        return retval;
    }
    std::vector<DynamicObject *> *loadDynamicObjects() override {
        if(getDynamicObjects()!= nullptr)return getDynamicObjects();
        auto retval=new std::vector<DynamicObject*>();
        retval->push_back(new DeriveablePlayer(getRandomFreePosition(),3));
        retval->push_back(new DeriveablePlayer(getRandomFreePosition(),3));
        retval->push_back(new DeriveablePlayer(getRandomFreePosition(),3));
        retval->push_back(new DeriveablePlayer(getRandomFreePosition(),3));
        //retval->push_back(new Player(getRandomFreePosition(),3));
        retval->push_back(new Ghost(getRandomFreePosition()));
        retval->push_back(new Ghost(getRandomFreePosition()));
        retval->push_back(new Ghost(getRandomFreePosition()));



        return setDynamicObjects(retval)->getDynamicObjects();
    }
};
#endif //MAZE_OBJECTFACTORY_H
