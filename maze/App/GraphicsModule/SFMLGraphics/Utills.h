//
// Created by stefan on 18/04/19.
//

#ifndef MAZE_UTILLS_H
#define MAZE_UTILLS_H

#include "../../Object/DynamicObject/ActionObject/Action.h"
#include <SFML/Graphics.hpp>
#include "../../ProjectFactory/Factory.h"
class SpriteAction{
    ActionType      type;
    sf::Vector2f    from;
    sf::Vector2f    to;
    Object*         parent;
public:
    SpriteAction(ActionType type, const sf::Vector2f &from, const sf::Vector2f &to, Object *parent) : type(type),
                                                                                                      from(from),
                                                                                                      to(to),
                                                                                                      parent(parent) {}

    std::string toString(){
        std::stringstream buffer;
        buffer<<"Object SpriteAction at"<<this<<std::endl;
        buffer<<"from ("<<from.x<<","<<from.y<<")"<<std::endl;
        buffer<<"to ("<<to.x<<","<<to.y<<")"<<std::endl;
        buffer<<"Object At "<<parent<<std::endl;
        return buffer.str();
    }

    class Transformers{
    public:
        /***
         * Convert the coordinates from RawMap tiles to SFML Pixels(basically is a simple scale linear transformation)
         * @param factory the Factory object
         * @param caller  the SFMLGraphics caller object
         * @param rmp     the RawMapPoint
         * @return        a sf::Vector2f containing the x and the y coordinates equilevant to given @param rmp
         * @Note this single method basically handles the requirement of ajusting to every screen out there :p
         */
        static sf::Vector2f toSFMLCoordinateSystem(Factory*factory,SFMLGraphics*caller,RawMapPoint &rmp){
            return sf::Vector2f{rmp.x*(caller->getWindowx()/(float)factory->getMap()->getLenx()),
                                rmp.y*(caller->getWindowy()/(float)factory->getMap()->getLeny())};
        }
        /***
         * Convert Action (RawMap world) to SpriteAction(SFML World)
         * @param factory the Factory object
         * @param caller  the SFMLGraphics caller object
         * @param ao      The Action object
         * @return        a Sprite Object equilevant to Action object given
         */
        static SpriteAction toSpriteAction(Factory*factory,SFMLGraphics*caller,Action&ao){
            return SpriteAction{
                ao.actionType,
                toSFMLCoordinateSystem(factory,caller,ao.from),
                toSFMLCoordinateSystem(factory,caller,ao.to),
                ao.parent
            };
        }


    };
};

#endif //MAZE_UTILLS_H
