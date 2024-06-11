#ifndef HANDLER_HPP
#define HANDLER_HPP

#include <SFML/Graphics.hpp>

namespace my {

class Handler {
public:
    virtual void onMousePressed(sf::Event::MouseButtonEvent) {};
    virtual void onMouseReleased(sf::Event::MouseButtonEvent) {};
    virtual void onMouseMoved(sf::Event::MouseMoveEvent) {};

    virtual void onKeyPressed(sf::Event::KeyEvent) {};
    virtual void onKeyReleased(sf::Event::KeyEvent) {};

    virtual void onEvent(sf::Event) {};

    void put(sf::Event e)
    {
        switch (e.type) {
        case sf::Event::KeyPressed:
            onKeyPressed(e.key);
            break;

        case sf::Event::KeyReleased:
            onKeyReleased(e.key);
            break;

        case sf::Event::MouseButtonPressed:
            onMousePressed(e.mouseButton);
            break;

        case sf::Event::MouseMoved:
            onMouseMoved(e.mouseMove);
            break;

        default:
            break;
        }

        onEvent(e);
    };
};

}

#endif