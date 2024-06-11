#ifndef LINE_HPP
#define LINE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "drawable.hpp"
#include "handler.hpp"
#include "identifiable.hpp"

namespace my {

class Line : public Handler, public Drawable, public Identifiable {
public:
    Line();
    Line(std::vector<sf::Vector2f> points);
    // Line(const Line& other) = delete;
    std::vector<std::unique_ptr<sf::Drawable>> draw_list() override;

    std::pair<sf::Vector2f, sf::Vector2f> get_points() const;

private:
    sf::RectangleShape _rect;
    std::pair<sf::Vector2f, sf::Vector2f> _points;
};

}

#endif