//
// Created by stefan on 17/04/19.
//

#ifndef MAZE_TEXTGRAPHIGS_H
#define MAZE_TEXTGRAPHIGS_H


#include <vector>
#include <SFML/System/Thread.hpp>
#include <SFML/Graphics.hpp>

#include "../Graphics.h"
#include "../../Object/DynamicObject/DynamicObject.h"
#include "../../Object/StaticObject/StaticObject.h"
/***
 * This struct holds the pointers for every different sprite used in game
 */
struct spriteData{
    sf::Sprite*WallSprite= nullptr;
    sf::Sprite*PriceSprite= nullptr;
    sf::Sprite*PlayerSprite= nullptr;
    sf::Sprite*GhostSprite= nullptr;
    sf::Sprite*FloorSprite= nullptr;
};

class NotificationFunctor;

/***
 * This is the Concrete Graphics implementation.Uses the SFML Library.
 */
class SFMLGraphics : public Graphics{
    unsigned int windowx,windowy;
    std::vector<DynamicObject*> *dynobjects;
    std::vector<StaticObject*>  *statobjects;
    sf::Thread *drawThread;
    spriteData sprites;

public:
    /***
     *
     * @param _factory The main factory object
     * @param _windowx The window size , x-axis
     * @param _windowy The window size , y-axis
     */
    SFMLGraphics(Factory *_factory,unsigned int _windowx,unsigned int _windowy);


    virtual ~SFMLGraphics();

    //The implementations derived from parent
    void apply(Action &ao) override;

    NotificationFunctor *getNotificationFunctor() override;

    //Getters and Setters
    unsigned int getWindowx() const;

    unsigned int getWindowy() const;


    //SFML Methods
    void graphicsEntryPoint();
    void drawStaticObjects(sf::RenderWindow *window);
    void drawDynamicObjects(sf::RenderWindow *window);
    sf::Sprite* getPlayerSprite();
    sf::Sprite* getPriceSprite();
    sf::Sprite *getFloorSprite();
    sf::Sprite* getGhostSprite();
    sf::Sprite* getMovingWallSprite();
    sf::Sprite* getWallSprite();

    sf::Sprite* loadSprite(std::string tilesetfilename,sf::IntRect);
};
struct SFMLNotificationFunctor:public NotificationFunctor{
    SFMLNotificationFunctor(Graphics *notifiedGraphicsModule) : NotificationFunctor(notifiedGraphicsModule) {}

public:
    void operator()(Action obj) override {
        getNotifiedGraphicsModule()->apply(obj);
    }
};



#endif //MAZE_TEXTGRAPHIGS_H
