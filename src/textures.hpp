#ifndef TEXTURES_HPP
#define TEXTURES_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "constants.hpp"

namespace my {

class TextureLib {
    /**
     * Class to manage all the Textures present with us.
     * Parses the base_dir recursively and reads all pngs as textures.
     * Creates a dot separated name to texture map.
     */

    /**
     * Private constructor
     */
    TextureLib();

    /**
     * Makes the _textures map
     */
    void initTextureMap(std::string base_dir = MEDIA_DIR);

    /**
     * Init the singleton and calls make_map.
     */
    static TextureLib& getInstance();

    /**
     * Map from full path to texture object.
     */
    std::unordered_map<std::string, sf::Texture> _textures;

    /**
     * The base dir to begin dfs in
     */
    std::string _base_dir = "";

    TextureLib(TextureLib const&) = delete;
    TextureLib& operator=(TextureLib const&) = delete;
    TextureLib(TextureLib const&&) = delete;
    TextureLib& operator=(TextureLib const&&) = delete;

    static TextureLib* _instance;

public:
    /**
     * Gets a copy of the requested texture
     */
    static sf::Texture getTexture(TEXTURE t);
};

}

#endif