//
// Created by stefan on 17/04/19.
//

#include "RawMap.h"
#include "MapException.h"


std::vector<Object*> RawMap::lineOfLen(int x) {
    std::vector<Object*> retval;//optimised for rvalue return procedure , no pointer needed
    for (int i = 0; i < x; ++i) {
        retval.push_back(nullptr);
    }
    return retval;
}

void RawMap::initializeEmptyMap() {
    for (int i = 0; i < leny; ++i) {
        map.push_back(lineOfLen(lenx));
    }
}

std::vector<std::vector<Object *>> RawMap::to2DVector() {
    return map;
}

void RawMap::applyActionObject(Action actionObject) {
    overridePoint(actionObject.from, nullptr);
    overridePoint(actionObject.to,actionObject.parent);
    for(auto every:this->notificationCallbacks){
        (*every)(actionObject);
    }
}

Object *RawMap::getPoint(RawMapPoint point) {
    return this->to2DVector()[point.x][point.y];
}

Object *RawMap::overridePoint(RawMapPoint point,Object*object) {
    map[point.x][point.y]=object;
    return this->to2DVector()[point.x][point.y];
}

unsigned long  RawMap::subscribeToNotifications(NotificationFunctor *callback) {
    this->notificationCallbacks.push_back(callback);
    return this->notificationCallbacks.size();

}

int RawMap::getLenx() const {
    return lenx;
}

int RawMap::getLeny() const {
    return leny;
}

RawMap RawMap::copy() {
    return RawMap(getLenx(), getLeny());
}


