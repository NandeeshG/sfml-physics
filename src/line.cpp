#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "ball.hpp"
#include "line.hpp"
#include "utility.hpp"

namespace my {

my::Line::Line()
{
    _rect = sf::RectangleShape(sf::Vector2f(0, 0));
    _points = { sf::Vector2f(0, 0), sf::Vector2f(0, 0) };
}

my::Line::Line(std::vector<sf::Vector2f> points)
{
    assert(points.size() == 2);
    if (points[0].x > points[1].x) {
        std::swap(points[0], points[1]);
    }
    _points = { points[0], points[1] };

    _rect = sf::RectangleShape(sf::Vector2f(my::distance(_points.first, _points.second), 3.0));
    _rect.setPosition(_points.first);
    _rect.setFillColor(sf::Color::Green);
    _rect.setRotation(my::angle(_points.second - _points.first));
}

std::vector<std::unique_ptr<sf::Drawable>> my::Line::draw_list()
{
    std::vector<std::unique_ptr<sf::Drawable>> ret;
    ret.push_back(std::make_unique<sf::RectangleShape>(_rect));
    return ret;
}

std::pair<sf::Vector2f, sf::Vector2f> Line::get_points() const
{
    return _points;
}

}