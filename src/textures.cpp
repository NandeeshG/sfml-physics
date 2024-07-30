#include <SFML/Graphics.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "constants.hpp"
#include "textures.hpp"

namespace my {

TextureLib* TextureLib::_instance = nullptr;

TextureLib::TextureLib() { }

TextureLib& TextureLib::getInstance()
{
    if (_instance)
        return *_instance;

    _instance = new TextureLib();
    _instance->initTextureMap();
    return *_instance;
}

void TextureLib::initTextureMap(std::string base_dir)
{
    for (const auto& dirEntry : std::filesystem::recursive_directory_iterator("media")) {
        std::string ext = ".png";
        std::string path = dirEntry.path().string();
        if (path.size() > ext.size() and path.substr(path.size() - ext.size()) == ext) {
            _textures[path] = sf::Texture();
            if (!_textures[path].loadFromFile(path)) {
                std::cout << "ERROR: Unable to load " << path << std::endl;
                _textures.erase(path);
            }
        }
    }
}

sf::Texture TextureLib::getTexture(TEXTURE t)
{
    const auto& path = TEXTURE_PATH(t);
    if (getInstance()._textures.count(path)) {
        return getInstance()._textures[path];
    }
    std::cout << "ERROR: Unable to find texture for " << path << std::endl;
    return sf::Texture();
}

}
