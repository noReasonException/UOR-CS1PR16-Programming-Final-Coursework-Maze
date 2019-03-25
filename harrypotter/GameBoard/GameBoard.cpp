//
// Created by stefstef on 2/4/2017.
//

#include <conio.h>
#include "GameBoard.h"
#include "../Errors/AllPlayersAreKilledException.h"
#include "../Defaults.h"
#include "../DisplaySystem/Window/Window.h"

class Window;     //Forward Declaration of class Window
class LeaderBoard;//Forward Declaration of class Leaderboard

/***
 *
 * @param _DebugMode  -> Print Esoteric logs (removed at version 1.0)
 * @param MapFileName -> Map File Name of game
 * @param __Players   -> Players Vector
 * @param Level       ->Difficult Level(EASY,MEDIUM,EXETASI_MODE)
 */
GameBoard::GameBoard(int _DebugMode, const char MapFileName[], std::vector<ObjectInfo *> __Players,int Level,InfoBoard*_ptrToInfoBoard)
        : PlayersMap(MapFileName,0,FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN),
          DebugMode(_DebugMode),CupPosition(this->CalculateRandomPosition()),
          ptrToInfoBoard(_ptrToInfoBoard),
          misCupHitten(false),
          misAnyoneHittenByGhost(false)
{
    this->DebugMode = false;
    srand(time(NULL));
    for (int i = 0; i < __Players.size(); i++) {
        __Players[i]->setColor(0);
        static_cast<PlayerInfo*>(__Players[i])->resetTeleportTimes();
        if(!__Players[i]->isAlive()){
            if(!__Players[i]->iskilledByMistake()){
                __Players[i]->revive();
                this->ptrToInfoBoard->setAlive(static_cast<PlayerInfo*>(__Players[i])->getPlayer().getId(),true);


            }
            else{
                __Players[i]->setVisible(false);

            }
        }

        this->PlayersGeneratedAroundView.push_back(this->initializeGeneratedArray());
        this->Players.push_back(__Players[i]); //Copy Inside of GameBoard

    }

    this->ptrMainWindow = new Window(&this->PlayersMap,ptrToInfoBoard);//Initialize Main Window
    this->ptrMainWindow->writeInfoLog("System Starting");                //First Info log..System Started


    if(Level <EASY or Level>EXETASI_MODE){
        Level=EXETASI_MODE;
        this->ptrMainWindow->writeErrorLog("Invalid Level Mode,Exetasi Using Instead ");
    }
    if(Level >EASY){                                                            //In Case of MEDIUM + mode
        Coordinate *fgCoord=new Coordinate(0,0);                       //Location of Fool Ghost);
        DummyGhost *foolGhost = new DummyGhost(this->PlayersMap,*fgCoord);
        Ghosts.push_back(new GhostInfo(*foolGhost,DUMMYGHOST_CHAR,*fgCoord));
    }
    if(Level>MEDIUM){                                                           //In Case of exetasi mode
        Coordinate *cgCoord = new Coordinate(0,0);  //Location of clever ghost
        SmartGhost *cleverGhost = new SmartGhost(30, this->PlayersMap, *cgCoord, Players); //Δημιουργία Αντικειμένων φαντασματων
        Ghosts.push_back(new GhostInfo(*cleverGhost, SMARTGHOST_CHAR, *cgCoord));                      //Αντιγραφη στον Vector

    }
}
/***
 *
 * @return EXIT_SUCCESS in any case
 */
int GameBoard::StartGame() try {
    this->initPrintAllObjects();                                    //Give to everyone A random Position
    this->ptrMainWindow->writeInfoLog("Press Any Key to start :) ");
    getch();


    int MoveTemp = STAND;                                           //Temp Value
    int iteratesThroughAlivePlayer = 0;                                  //To check if everyone is dead
    char killedPlayer = 'n';                                        //Temp Value in case of collision Ghost - Player
    ObjectInfo *tmp;                                                //Temp Pointer
    std::ostringstream temp;                                        //Temp osstringStream to print longs efficienly
    for (;;) {
        this->ptrMainWindow->drawOnMap('W', this->CupPosition);     //Draw Cup

        iteratesThroughAlivePlayer = 0;                               //initalize that in current time , we have check zero players
        for (int i = 0; i < this->Players.size(); i++) {         //For every player
            tmp = this->Players[i];                              //Get the pointer to player
            if (tmp->isAlive()) {                                //if is alive
                iteratesThroughAlivePlayer += 1;                      //We have check one more player
                PlayerInfo *ptr = static_cast<PlayerInfo *>(tmp);                  //Secure cast here , In PLAYERS vector :P
                temp << "Request Move from player :" << ptr->getAvatar();          //Request Log
                this->ptrMainWindow->writeInfoLog(temp.str());                     //Send Log to window
                temp.str("");                                                      //Clear Window

                this->clearGeneratedArray(this->PlayersGeneratedAroundView[i]);    //Clear ViewAround Array
                this->generateAroundView(tmp->getPosition(),
                                         this->PlayersGeneratedAroundView[i]);    //Generate the view around
                MoveTemp = ptr->getPlayer().getMove(
                        const_cast<const char **>(this->PlayersGeneratedAroundView[i])); //Send the view , and Get the Move
                temp << "Player:" << ptr->getAvatar() << " Responce Move : " //Success Log
                     << this->TranslateMoveToString(MoveTemp);
                this->ptrMainWindow->writeInfoLog(temp.str());
                temp.str("");                                                //Clear the temp stream
                this->ptrMainWindow->drawOnMap(' ', ptr->getPosition());     //Clear my current position(to move on..)
                if (this->isValidMove(ptr, MoveTemp)) {                      //If my move was valid
                    if (this->HitsCup(ptr->getPosition(), MoveTemp)) {       //Check if i hit cup :P
                        this->misCupHitten=true;                                                    //SUCCESS
                    }
                    if (this->HitsGhost(ptr->getPosition(),MoveTemp)) {                              //If player hits Ghost
                        this->killPlayerOnInfoBoard(ptr);
                        ptr->kill();                                                                //Then Kill HimSelf :P
                    }
                    this->move(ptr, MoveTemp);                                                      //Make the move
                }
                else {
                    ObjectInfo *tempPlayerInfoToKill;                                                //In case of invalid move
                    tempPlayerInfoToKill=(this->getPlayerByRepresent(tmp->getAvatar()));                         //Find the guy, and kill him
                    tempPlayerInfoToKill->kill();
                    tempPlayerInfoToKill->setkilledByMistake();
                    this->killPlayerByMistakeOnInfoBoard(ptr); //kill in infoboard

                }
            }
            if (tmp->isVisible()) {                                                                 //If the guy is visible
                this->ptrMainWindow->drawOnMap(*this->Players[i]); //here #CHANGE                   //Draw Him :)
            }
        }
        if (iteratesThroughAlivePlayer == 0) {                                                           //If no exist alive player
            throw AllPlayersAreKilledException();                                                       //Throw everyone is dead
        }
        for (int i = 0; i < this->Ghosts.size(); i++) {                                              //For Every Ghost
            tmp = this->Ghosts[i];                                                                   //Get The Temponary pointer
            GhostInfo *ptr = static_cast<GhostInfo *>(tmp);                                          //Safe Cast
            MoveTemp = ptr->getGhost().getMove();                                                    //Get The Move
            temp << "Ghost :" << ptr->getAvatar() << " Move " << this->TranslateMoveToString(MoveTemp); //Logs
            this->ptrMainWindow->writeInfoLog(temp.str());
            temp.str("");
            this->ptrMainWindow->drawOnMap(' ', ptr->getPosition());
            if (MoveTemp == STAND and ptr->getGhost().iAmFool() and
                                                                                                        //Give the foolGhost a random destination if needed
                dynamic_cast<DummyGhost *>(&ptr->getGhost())->iNeedNewRandomTarget) {
                dynamic_cast<DummyGhost *>(&ptr->getGhost())->myNewRandomTargetIs(this->CalculateRandomPosition());
            }
            if (this->isValidMove(ptr->getPosition(), MoveTemp)) {                                                           //Double Check , unnessesary
                if ((killedPlayer = this->HitsPlayer(ptr->getPosition(), MoveTemp))) {                 //If i collide with ObjectInfo
                    this->misAnyoneHittenByGhost=true;
                    /*
                    ObjectInfo *tempPointerToPlayer;
                    if((tempPointerToPlayer=getPlayerByRepresent(killedPlayer))!=NULL){                //And is Player
                        tempPointerToPlayer->kill();
                        this->killPlayerOnInfoBoard(static_cast<PlayerInfo *>(tempPointerToPlayer));
                    } */                                                                                 //I killed him :)
                }
                this->move(ptr, MoveTemp);                                                            //Make the move
            }
            if (ptr->isVisible()) {                                                                   //Unnessesary checking (Debug purposes)
                this->ptrMainWindow->drawOnMap(*this->Ghosts[i]);

            }

        }
        if(this->misAnyoneHittenByGhost){
            this->killAllHittenPlayers(this->getAllHittenPlayers());
            this->misAnyoneHittenByGhost=false;
        }
        if(this->misCupHitten){ //if everyone has hit the cup , then...
            this->givePointsToEveryoneWhoHitsCup(this->getAllPlayersWhoHitsCup()); //obviously
            return EXIT_SUCCESS;//end;
        }
        for (int i = 0; i < 100000000; i++);  //Frame Delay
    }

    return EXIT_SUCCESS;

} catch(AllPlayersAreKilledException &e) { //EveryOne is dead Exception
    this->ptrMainWindow->writeInfoLog("Everyone is dead :)  ");
    return EXIT_SUCCESS;
}

/***
 * @brief -> prepares the window and sets the randomly choosen positions
 */
void GameBoard::initPrintAllObjects() {
    Coordinate *e ;
    int iterateAlivePlayers=0;
    for(int i=0;i<this->Players.size();i++){
        e= new Coordinate(this->CalculateRandomPosition());
        if(this->Players[i]->isAlive()){
            iterateAlivePlayers+=1;
            this->Players[i]->setPosition(*e);
            if(this->Players[i]->isVisible()){
                this->ptrMainWindow->drawOnMap(*this->Players[i]);
                static_cast<PlayerInfo*>(this->Players[i])->getPlayer().init(this->PlayersMap.getRows(),this->PlayersMap.getColumns(),this->Players[i]->getPosition().getX(),this->Players[i]->getPosition().getY());

            }
        }

        delete e;
    }
    if(iterateAlivePlayers==0)throw AllPlayersAreKilledException();
    for(int i=0;i<this->Ghosts.size();i++){
        e= new Coordinate(this->CalculateRandomPosition());
        this->Ghosts[i]->setPosition(*e);
        this->ptrMainWindow->drawOnMap(*this->Ghosts[i]);
        delete e;
    }
    this->ptrMainWindow->drawOnMap('W',this->CupPosition);


    /*for (int j = 0; j < this->Players.size(); ++j) {
        this->PlayersMap.setCharAt(this->Players[j]->getPosition(),' ');
        this->Players[j]->setPosition(*new Coordinate(1,1+j));
    }*/

}

/***
 *
 * @param Avatar ->The represent Character belong to player
 * @return       ->The ObjectInfo Pointer belong to player with given Avatar at @param Avatar
 */
ObjectInfo *GameBoard::getPlayerByRepresent(char Avatar) {
    for(int i=0;i<this->Players.size();i++) {
        if (this->Players[i]->getAvatar() == Avatar)return this->Players[i];
    }
    return NULL;

}
/***
 *
 * @param player -> An player Info Pointer
 * @param Move   -> An Move Instruction Code
 * @return       -> True if the move is Valid , False ElseWhere
 * @brief        -> Used to check if player chossen a correct Move , with additional checks for teleport and correct code
 */
bool GameBoard::isValidMove(PlayerInfo *player, int Move) {
    if(Move!=UP and Move!=DOWN and Move!=LEFT and Move!=RIGHT and Move!=STAND and Move!=TELEPORT){
    	return false;
	}
    if(Move==TELEPORT){
        if((player)->canTeleport()){
            this->teleport((player));
            this->teleport((player));
            return true;
        }
        return false;
    }
    return this->isValidMove(player->getPosition(),Move);
}
/***
 *
 * @param CurrentPosition  -> A Coordinate Reference
 * @param Move             -> An Move Instruction Code
 * @return                 -> True if the move is Valid , False ElseWhere
 * @brief                  -> Used to check if Ghosts chossen a correct Move , with no additional checks for teleport and correct code
 */
bool GameBoard::isValidMove(Coordinate &CurrentPosition, int Move) {
    if(this->PlayersMap.existObject(CurrentPosition,Move)){
        return false;
    }
    if(CurrentPosition.getX()+1>=this->PlayersMap.getRows() and Move==DOWN)return false;
    if(CurrentPosition.getX()-1<=0 and Move==UP)return false;

    if(CurrentPosition.getY()+1>=this->PlayersMap.getColumns() and Move==RIGHT)return false;
    if(CurrentPosition.getY()-1<=0 and Move==LEFT)return false;
    return true;
}
/***
 *
 * @param Object -> An ObjectInfo Pointer
 * @param Move   -> An Move Instruction Code
 * @brief Used to convert a Move Instruction Code to Actual Move the ObjectInfo Object inside Map
 */
void GameBoard::move(ObjectInfo *Object, int Move) {
    switch(Move){
        case UP:Object->getPosition().goUp();break;
        case DOWN:Object->getPosition().goDown();break;
        case LEFT:Object->getPosition().goLeft();break;
        case RIGHT:Object->getPosition().goRight();break;
        case STAND:break;
    }
}
/***
 *
 * @param player -> An PlayerInfo Pointer
 * @brief -> With No Addintional checks , teleport calculates a random valid place inside map , and teleports player there!
 * @ifnot run teleport validation first , teleport() will teleport the player , even if that is not allowed
 */
void GameBoard::teleport(PlayerInfo *player) {
	srand(time(NULL));
    player->playerTeleported();
    this->ptrMainWindow->drawOnMap(' ',player->getPosition());
    player->setPosition(this->CalculateRandomPosition());
}
/***
 *
 * @param Position -> The Current Ghost Position
 * @param MoveTemp -> The next but not performed move instruction code
 * @return a char of player will gonna hit , false otherwise
 * @example
 *          if ((killedPlayer = this->HitsPlayer(ptr->getPosition(), MoveTemp))) {
 *                          ...
 *          }
 * @note if no player exist on ghost way , then the if block is false , else use the killedPlayer variable to access
 * @note the ObjectInfo through getPlayerByRepresent() Function Defined Previously
 *
 */

char GameBoard::HitsPlayer(Coordinate Position,int MoveTemp) {
    ObjectInfo tempObject('\0',Position);
    this->move(&tempObject,MoveTemp);
    if(this->PlayersMap.getCharAt(tempObject.getPosition())>='A' and this->PlayersMap.getCharAt(tempObject.getPosition())<='Z'){
        return this->PlayersMap.getCharAt(tempObject.getPosition());
    }
    return false;
    //return (this->PlayersMap.getCharAt(Position)>='A' and this->PlayersMap.getCharAt(Position)<='Z')?this->PlayersMap.getCharAt(Position):false;
}
/***
 *
 * @param Position -> The Current Player Position
 * @param MoveTemp -> The next but not performed move instruction code
 * @return true if the next move,hits cup , false otherways
 * @example
 *          MoveTemp = ptr->getMove(const_cast<....());
 *          if (this->HitsCup(ptr->getPosition(), MoveTemp)) {
 *              ...
 *          }
 *
 */
bool GameBoard::HitsCup(Coordinate Position,int Move){
    ObjectInfo tempObject('\0',Position);
    this->move(&tempObject,Move);
    if(this->PlayersMap.getCharAt(Position)==CUP_CHAR)return true;
    return false;

}
/***
 *
 * @name   GameBoard::HitsGhost(Coordinate,int)
 * @param Position -> The Current Player Position
 * @param MoveTemp -> The next but not performed move instruction code
 * @return true if the next move,hits Ghost , false otherways
 * @example
 *          MoveTemp = ptr->getMove(const_cast<....());
 *          if (this->HitsGhost(ptr->getPosition(), MoveTemp)) {
 *              ...
 *          }
 *
 */
bool GameBoard::HitsGhost(Coordinate Position, int Move) {
    ObjectInfo tempObject('\0',Position);
    this->move(&tempObject,Move);
    if(this->PlayersMap.getCharAt(Position)==SMARTGHOST_CHAR or this->PlayersMap.getCharAt(Position)==DUMMYGHOST_CHAR )return true;
    return false;
}
/***
 *
 * @name    GameBoard::CalculateRandomPosition(void)

 * @returns Coordinate Object (By Shallow Copy)
 * @brief   Calculates a random valid location , and returns it
 *
 */
Coordinate GameBoard::CalculateRandomPosition(void) {
    int newX=0,newY=0;
    while(this->PlayersMap.getCharAt(newX,newY)!=' '){
        newX=(rand()%this->PlayersMap.getRows());
        newY=(rand()%this->PlayersMap.getColumns());
    }
    Coordinate tempObject(newX,newY);
    return tempObject;
}
/***
 *
 * @name    GameBoard::generateAroundView(void)
 * @param   PlayerGeneratedAroundView -> A 2D[5][5] Array (Pre_initialized)
 * @param   refToCoordinate           -> A reference to current players coordinate
 * @brief   Generates the Around View of eatch player
 * @note    The PlayerGeneratedAroundView , to be valid pointer to this method, must run fist initializeGeneratedArray()
 *
 */
void GameBoard::generateAroundView(Coordinate &refToCoordinate,char **PlayerGeneratedAroundView) {
    char tmp;
    for (int i = 0,x=-2; i < 5 and x<=2; ++i,x++) {
        for (int j = 0,y=-2; j < 5 and y<=2; ++j,y++) {
            (PlayerGeneratedAroundView[i][j]=(tmp=this->PlayersMap.getCharAt((refToCoordinate.getX()+x),(refToCoordinate.getY()+y)))=='@'?'*':tmp);
        }
    }
}
/***
 * @return a 2D[5][5] char array to use as view of eatch player
 */
char **GameBoard::initializeGeneratedArray() {
    char **Array = new char*[5];
    for (int i = 0; i < 5; ++i) {
        Array[i]=new char[5];
        for (int j = 0; j < 5; ++j) {
            Array[i][j]=' ';
        }
    }
    return Array;
}
/***
 *
 * @param Move -> A valid move instruction Code
 *
 * @return a std::string object with the name assosiated with @param Move
 */
std::string GameBoard::TranslateMoveToString(int Move) {
    switch(Move){
        case UP:return std::string("Up");
        case DOWN:return std::string("Down");
        case LEFT:return std::string("Left");
        case RIGHT:return std::string("Right");
        case STAND:return std::string("Stand");
        case TELEPORT:return std::string("Teleport");
    }
    return std::string("Unnown");
}

/***
 *
 * @param ptr -> An 2D[5][5] char array
 * @brief     -> Clears and prepare the eatch array to re-GenerateAroundView()
 */
void GameBoard::clearGeneratedArray(char **ptr) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            ptr[i][j]='*';
        }
    }
}





GameBoard::~GameBoard() {
    delete ptrMainWindow;
    //delete ptrToLeaderboard;

}

void GameBoard::killPlayerOnInfoBoard(PlayerInfo *ptrToPlayer) {
    this->ptrToInfoBoard->setAlive(ptrToPlayer->getPlayer().getId(),false);
    this->ptrMainWindow->updateInfoBoard();
}

void GameBoard::killPlayerByMistakeOnInfoBoard(PlayerInfo *ptrToPlayer) {
    this->ptrMainWindow->writeInfoLog("Player is banned!");
    this->ptrToInfoBoard->setLost(ptrToPlayer->getPlayer().getId(),true);
    this->killPlayerOnInfoBoard(ptrToPlayer);

}

std::vector<std::string> *GameBoard::getMapFileNames(std::string dir) {
    std::vector<std::string>*FileNames = new std::vector<std::string>();

    WIN32_FIND_DATA FindDataHandle;
    TCHAR bufferToCurrentDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH,bufferToCurrentDirectory);
    SetCurrentDirectoryA(dir.c_str());
    HANDLE OperationHandler = FindFirstFile(TEXT("*.txt"),&FindDataHandle);
    while(FindNextFile(OperationHandler,&FindDataHandle)){
        if(FindDataHandle.cFileName[0]=='M'){
            FileNames->push_back(FindDataHandle.cFileName);
        }
    }
    FindClose(OperationHandler);
    SetCurrentDirectory(bufferToCurrentDirectory);
    return FileNames;
}

std::vector<PlayerInfo*> *GameBoard::getAllPlayersWhoHitsCup() {
    std::vector<PlayerInfo*>*ReturnVector=new std::vector<PlayerInfo*>();
    for (int i = 0; i < this->Players.size(); ++i) {
        if(this->Players[i]->getPosition()==this->CupPosition and this->Players[i]->isAlive()){
            ReturnVector->push_back(static_cast<PlayerInfo*>(this->Players[i]));
        }
    }
    return ReturnVector;
}

std::vector<PlayerInfo*> *GameBoard::getAllHittenPlayers(void) {
    std::vector<PlayerInfo *> *ReturnVector = new std::vector<PlayerInfo *>();
    for (int i = 0; i < this->Players.size(); ++i) {
        for (int j = 0; j < this->Ghosts.size(); ++j) {
            if (this->Players[i]->getPosition() == this->Ghosts[j]->getPosition()) {
                ReturnVector->push_back(static_cast<PlayerInfo *>(this->Players[i]));
            }
        }
    }

    return ReturnVector;
}

void GameBoard::givePointsToEveryoneWhoHitsCup(std::vector<PlayerInfo *>* vptrtoPlayerInfo) {
    std::ostringstream tempStringBuffer;

    for (unsigned int i = 0; i < vptrtoPlayerInfo->size(); ++i) {
        tempStringBuffer<<"Player "<<vptrtoPlayerInfo->operator[](i)->getAvatar()<<"Won the Round! :) ";
        this->ptrMainWindow->writeInfoLog(tempStringBuffer.str());
        this->ptrToInfoBoard->increasePoints(vptrtoPlayerInfo->operator[](i)->getPlayer().getId());
        tempStringBuffer.str("");
    }
    delete (vptrtoPlayerInfo);
    return ;

}

void GameBoard::killAllHittenPlayers(std::vector<PlayerInfo *> *vptrtoPlayerInfo) {
    std::ostringstream tempStringBuffer;

    for (unsigned int i = 0; i < vptrtoPlayerInfo->size(); ++i) {
        tempStringBuffer<<"Player "<<vptrtoPlayerInfo->operator[](i)->getAvatar()<<" Killed ! :) ";
        this->ptrMainWindow->writeInfoLog(tempStringBuffer.str());
        tempStringBuffer.str("");
        vptrtoPlayerInfo->operator[](i)->kill();
        this->killPlayerOnInfoBoard(vptrtoPlayerInfo->operator[](i));


    }

}

