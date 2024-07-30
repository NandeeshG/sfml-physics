#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "background.hpp"
#include "constants.hpp"
#include "textures.hpp"

namespace my {

Background::Background(sf::Vector2f window_size)
{
    _window_size = window_size;
}

void Background::add_layer(TEXTURE t)
{
    _texture_types.push_back(t);
    _textures.push_back(TextureLib::getTexture(t));

    sf::Sprite bg;
    bg.setTexture(_textures.back());
    bg.scale(sf::Vector2f(_window_size.x / TEX_SCALE.x, _window_size.y / TEX_SCALE.y));
    // bg.setColor(sf::Color(bg_color.b, bg_color.r, bg_color.g, bg_color.a + 256 / 2));

    _sprites.push_back(bg);
}

std::vector<std::unique_ptr<sf::Drawable>> Background::draw_list()
{
    std::vector<std::unique_ptr<sf::Drawable>> ret;
    for (int i = 0; i < _sprites.size(); ++i) {
        ret.push_back(std::make_unique<sf::Sprite>(_sprites[i]));
    }
    return ret;
}

}