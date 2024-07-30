#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

namespace my {

// ====================================
// MATH CONSTANTS
// ====================================

const double PI = 3.14159265;
const float PIXEL_PER_METER = 377.952;

// ====================================
// TEXTURE CONSTANTS
// ====================================

const sf::Vector2f TEX_SCALE = { 1920, 1080 };

enum TEXTURE {
    BG4,
    BONES,
    TREE,
    ICON_ORB
};

// ====================================
// DIRECTORY CONSTANTS
// ====================================

const std::string MEDIA_DIR = "media";

inline std::string TEXTURE_PATH(TEXTURE tex)
{
    static std::unordered_map<TEXTURE, std::string> _TEXTURE_PATH = {
        { BG4, MEDIA_DIR + "/Battleground4/Bright/Battleground4.png" },
        { BONES, MEDIA_DIR + "/Battleground4/Bright/bones.png" },
        { TREE, MEDIA_DIR + "/Battleground4/Bright/tree.png" },
        { ICON_ORB, MEDIA_DIR + "/Icons/Icons_22.png" }
    };
    return _TEXTURE_PATH[tex];
}

}

#endif