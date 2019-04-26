//
// Created by stefan on 17/04/19.
//

#include "SFMLGraphics.h"
#include "Utills.h"

void SFMLGraphics::apply(Action &ao) {
 //   SpriteAction e=SpriteAction::Transformers::toSpriteAction(getfactory(),this,ao);
//    std::cout<<e.toString()<<std::endl;
}

NotificationFunctor *SFMLGraphics::getNotificationFunctor() {
    return new SFMLNotificationFunctor(this);
}

SFMLGraphics::SFMLGraphics(Factory *_factory,unsigned int _windowx,unsigned int _windowy) : Graphics(_factory),windowx(_windowx),windowy(_windowy) {
    dynobjects=_factory->getObjectFactory()->loadDynamicObjects();
    statobjects=_factory->getObjectFactory()->loadstaticObjects();
    drawThread=new sf::Thread(&SFMLGraphics::graphicsEntryPoint,this);
    drawThread->launch();

}

unsigned int SFMLGraphics::getWindowx() const {
    return windowx;
}

unsigned int SFMLGraphics::getWindowy() const {
    return windowy;
}
/***
 * graphicsEntryPoint()
 * this is the method who is given to the draw thread for execution. as you can see draws the events to the screen
 */
void SFMLGraphics::graphicsEntryPoint() {

    sf::RenderWindow window(sf::VideoMode(this->getWindowx(),this->getWindowy()), "The Maze");




    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(*getFloorSprite());

        drawStaticObjects(&window);
        drawDynamicObjects(&window);

        window.display();
    }
}

sf::Sprite* SFMLGraphics::getPlayerSprite() {
    if(sprites.PlayerSprite!= nullptr)return sprites.PlayerSprite;
    return sprites.PlayerSprite=loadSprite("playersets.png",sf::IntRect{128,75,16,32});
}

sf::Sprite *SFMLGraphics::getGhostSprite() {
    if(sprites.GhostSprite!= nullptr)return sprites.GhostSprite;
    return sprites.GhostSprite=loadSprite("playersets.png",sf::IntRect{22,325,32,32});
}

sf::Sprite *SFMLGraphics::getMovingWallSprite() {
    if(sprites.WallSprite!= nullptr)return sprites.WallSprite;
    return sprites.WallSprite=loadSprite("levelsets.png",sf::IntRect{22,325,32,32});
}

sf::Sprite *SFMLGraphics::getWallSprite() {
    /*if(sprites.WallSprite!= nullptr)return sprites.WallSprite;
    return sprites.WallSprite=loadSprite("levelsets.png",sf::IntRect{192,256,32,32});*/

    if(sprites.WallSprite!= nullptr)return sprites.WallSprite;
    return sprites.WallSprite=loadSprite("levelsets.png",sf::IntRect{418,264,32,32});
}
sf::Sprite *SFMLGraphics::getPriceSprite() {
    if(sprites.PriceSprite!= nullptr)return sprites.PriceSprite;
    return sprites.PriceSprite=loadSprite("playersets.png",sf::IntRect{240,242,16,32});
}
sf::Sprite *SFMLGraphics::getFloorSprite() {
    if(sprites.FloorSprite!= nullptr)return sprites.FloorSprite;
    sf::Texture *texture=new sf::Texture;
    sf::Sprite *sprite=new sf::Sprite;
    if(!texture->loadFromFile("levelsets.png",sf::IntRect{192,256,32,32}));
    sprite->setTextureRect(sf::IntRect{0,0,(int)getWindowx(),(int)getWindowy()});

    texture->setRepeated(true);
    sprite->setTexture(*texture);


    return sprites.FloorSprite=sprite;
}
void SFMLGraphics::drawStaticObjects(sf::RenderWindow *window) {
    sf::Sprite *shape = nullptr;
    for (auto *every:*statobjects) {
        auto spriteaction = SpriteAction::Transformers::toSFMLCoordinateSystem(getfactory(), this,
                                                                               every->getPosition());
        switch (every->getType()) {
            case OS_WALL:
                shape = getWallSprite();
                break;
            case OS_PRICE:
                shape = getPriceSprite();
                break;
            default:
                shape = getWallSprite();
                break;
        }
        shape->setPosition(spriteaction.x, spriteaction.y);
        window->draw(*shape);
    }
}

void SFMLGraphics::drawDynamicObjects(sf::RenderWindow *window) {
    sf::Sprite *shape = nullptr;
    for (auto *every:*dynobjects) {
        if(!every->isVisible())continue;
        auto spriteaction = SpriteAction::Transformers::toSFMLCoordinateSystem(getfactory(), this,
                                                                               every->getPosition());
        switch (every->getType()) {
            case OD_GHOST:
                shape = getGhostSprite();
                break;
            case OD_PLAYER:
                shape = getPlayerSprite();
                break;
            default:
                shape = getWallSprite();
                break;
        }
        shape->setPosition(spriteaction.x, spriteaction.y);
        window->draw(*shape);
    }
}
/***
 * Load any sprite from any image
 * @param tilesetfilename the filename
 * @param rect The chopped rentangle who the sprite belongs
 * @return a sf::Sprite pointer
 */
sf::Sprite *SFMLGraphics::loadSprite(std::string tilesetfilename, sf::IntRect rect) {
    sf::Texture *texture=new sf::Texture;
    sf::Sprite *sprite=new sf::Sprite;
    if(!texture->loadFromFile(tilesetfilename,rect));
    sprite->setTexture(*texture);
    sprite->setScale(sf::Vector2f{getWindowx()/getfactory()->getMap()->getLenx()/32.d,getWindowy()/getfactory()->getMap()->getLeny()/32.d});
    return sprite;
}

SFMLGraphics::~SFMLGraphics() {
    if(drawThread)drawThread->terminate();
    delete(drawThread);
    delete(sprites.WallSprite);
    delete(sprites.PriceSprite);
    delete(sprites.PlayerSprite);
    delete(sprites.GhostSprite);
    delete(sprites.FloorSprite);
}


