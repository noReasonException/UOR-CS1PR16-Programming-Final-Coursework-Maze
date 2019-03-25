//
// Created by sotiris on 3/23/2017.
//

#ifndef HARRYPOTTER_PLAYERINFO_H
#define HARRYPOTTER_PLAYERINFO_H

#include "../Coordinate/Coordinate.h"
#include "../Player/Player.h"
#include "../ObjectInfo/ObjectInfo.h"
#include "../StupidPlayer/StupidPlayer.h"

#define maxTeleports 2

class PlayerInfo : public ObjectInfo{
public:
    PlayerInfo(Player &myPlayer,char Avatar,Coordinate &position);
    PlayerInfo(Player &myPlayer,char Avatar);
    int getSteps();
    void IncreaseSteps();
    Player &getPlayer();
    bool canTeleport();
    void playerTeleported();
    void resetTeleportTimes();
private:
    Player &player;
    int timesTeleported;
    int stepCounter;
};
#endif //HARRYPOTTER_PLAYERINFO_H