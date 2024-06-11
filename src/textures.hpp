#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

namespace my {

enum TEXTURE {
    TX_BG4,
    TX_BONES,
    TX_TREE,
    TX_ORB
};

class Textures {
public:
    Textures(std::string base_dir);
    Textures(std::string base_dir, sf::Vector2f tx_scale);
    sf::Texture getTexture(TEXTURE t);
    sf::Vector2f getTextureScale(TEXTURE t);

private:
    std::string _base_dir;
    std::unordered_map<TEXTURE, sf::Texture> _tx_map;
    sf::Vector2f _tx_scale;
};

}

#endif