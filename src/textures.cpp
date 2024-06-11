#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "textures.hpp"

namespace my {

namespace {
    std::unordered_map<TEXTURE, std::string> file_map = {
        { TX_BG4, "/Battleground4/Bright/Battleground4.png" },
        { TX_BONES, "/Battleground4/Bright/bones.png" },
        { TX_TREE, "/Battleground4/Bright/tree.png" },
        { TX_ORB, "/Icons/Icons_22.png" }
    };
}

Textures::Textures(std::string base_dir)
{
    _base_dir = base_dir;
}

Textures::Textures(std::string base_dir, sf::Vector2f tx_scale)
{
    _tx_scale = tx_scale;
    _base_dir = base_dir;
}

sf::Texture Textures::getTexture(TEXTURE t)
{
    if (_tx_map.count(t)) {
        return _tx_map[t];
    } else if (file_map.count(t)) {
        _tx_map[t] = sf::Texture();
        if (!_tx_map[t].loadFromFile(_base_dir + file_map[t])) {
            std::cout << "ERROR: Unable to load " << file_map[t] << std::endl;
            _tx_map.erase(t);
            return sf::Texture();
        }
        return _tx_map[t];
    } else {
        std::cout << "ERROR: No file path for TEXTURE " << t << std::endl;
        return sf::Texture();
    }
}

sf::Vector2f Textures::getTextureScale(TEXTURE t)
{
    return _tx_scale;
}

}
