//
// Created by sotiris on 3/23/2017.
//

#include "PlayerInfo.h"

PlayerInfo::PlayerInfo(Player &myPlayer, char _Avatar, Coordinate &position):
        player(myPlayer),
        ObjectInfo(_Avatar,position),
        stepCounter(0),
        timesTeleported(0) {
}
PlayerInfo::PlayerInfo(Player &myPlayer, char _Avatar):
        ObjectInfo(_Avatar),
        player(myPlayer),
        stepCounter(0),
        timesTeleported(0) {
}

int PlayerInfo::getSteps() {
    return stepCounter;
}

void PlayerInfo::IncreaseSteps()  {
    this->stepCounter+=1;

}

Player &PlayerInfo::getPlayer() {
    return this->player;
}

bool PlayerInfo::canTeleport() {
    return this->timesTeleported<=TELEPORTS_MAX;
}

void PlayerInfo::playerTeleported() {
    this->timesTeleported+=1;

}

void PlayerInfo::resetTeleportTimes() {
    this->timesTeleported=0;

}

