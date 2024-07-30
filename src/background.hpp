#ifndef BACKGROUND_HPP
#define BACKGROUND_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "drawable.hpp"
#include "handler.hpp"
#include "textures.hpp"

namespace my {

class Background : public Handler, public Drawable {
public:
    Background(sf::Vector2f);
    void add_layer(TEXTURE);
    std::vector<std::unique_ptr<sf::Drawable>> draw_list() override;

private:
    std::vector<sf::Texture> _textures;
    std::vector<TEXTURE> _texture_types;
    std::vector<sf::Sprite> _sprites;
    sf::Vector2f _window_size;
};

}

#endif