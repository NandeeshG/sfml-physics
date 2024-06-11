#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace my {

class Drawable {
public:
    virtual std::vector<std::unique_ptr<sf::Drawable>> draw_list() = 0;
};

}

#endif