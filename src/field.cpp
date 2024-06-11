#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "ball.hpp"
#include "field.hpp"
#include "textures.hpp"
#include "utility.hpp"

namespace my {

Field::Field(Textures tex_prov, sf::FloatRect bounding_rect)
    : _texture_provider(tex_prov)
{
    _bounding_rect = sf::RectangleShape(bounding_rect.getSize());
    _bounding_rect.setPosition(bounding_rect.getPosition());
    _bounding_rect.setFillColor(sf::Color::Transparent);
    _bounding_rect.setOutlineThickness(3.0);
    _bounding_rect.setOutlineColor(sf::Color::Black);
}

std::vector<std::unique_ptr<sf::Drawable>> Field::draw_list()
{
    // TODO: How to delete ball on going outside field/screen?

    std::vector<std::unique_ptr<sf::Drawable>> ret;

    ret.push_back(std::make_unique<sf::RectangleShape>(_bounding_rect));

    for (auto& line : _lines) {
        auto _line_d = line.draw_list();
        for (auto& d : _line_d) {
            ret.push_back(std::move(d));
        }
    }
    for (auto& ball : _balls) {
        ball.update(_lines);
        auto _ball_d = ball.draw_list();
        for (auto& d : _ball_d) {
            ret.push_back(std::move(d));
        }
    }

    auto _line_d = _ghost_line.draw_list();
    for (auto& d : _line_d) {
        ret.push_back(std::move(d));
    }

    auto _ball_d = _ghost_ball.draw_list();
    for (auto& d : _ball_d) {
        ret.push_back(std::move(d));
    }
    return ret;
}

void Field::onEvent(sf::Event e)
{
    for (auto& ball : _balls) {
        ball.put(e);
    }
    for (auto& line : _lines) {
        line.put(e);
    }
}

void Field::onKeyPressed(sf::Event::KeyEvent e)
{
    if (e.scancode == sf::Keyboard::Scancode::Tab) {
        _draw_mode = my::switch_draw_mode(_draw_mode);
        reset_drawing();
    } else if (e.scancode == sf::Keyboard::Scancode::R) {
        _balls.clear();
        _lines.clear();
        reset_drawing();
    }
}

void Field::handle_drawing_ball(sf::Event::MouseButtonEvent e)
{
    if (_new_ball_center.x == -1 && _new_ball_center.y == -1) {
        _new_ball_center = sf::Vector2f(e.x, e.y);
        _ghost_ball_center = sf::Vector2f(e.x, e.y);
        _drawing = true;
    } else {
        double radius = my::distance(_new_ball_center, sf::Vector2f(e.x, e.y));
        _balls.emplace_back(radius, _new_ball_center);
        // _balls.back().setTexture(_texture_provider.getTexture(my::TEXTURE::TX_ORB));

        reset_drawing();
    }
}

void Field::handle_drawing_line(sf::Event::MouseButtonEvent e)
{
    _ghost_line_start = sf::Vector2f(e.x, e.y);
    _new_line_points.push_back(_ghost_line_start);
    _drawing = true;

    if (_new_line_points.size() == 2) {
        _lines.emplace_back(_new_line_points);

        reset_drawing();
    }
}

void Field::onMousePressed(sf::Event::MouseButtonEvent e)
{
    if (e.button == sf::Mouse::Button::Left) {
        if (_draw_mode == DM_BALL) {
            handle_drawing_ball(e);
        } else if (_draw_mode == DM_LINE) {
            handle_drawing_line(e);
        }
    }
}

void Field::onMouseMoved(sf::Event::MouseMoveEvent e)
{
    if (_drawing) {
        if (_draw_mode == DM_BALL) {
            double radius = my::distance(_ghost_ball_center, sf::Vector2f(e.x, e.y));
            _ghost_ball = Ball(radius, { _ghost_ball_center.x, _ghost_ball_center.y }, true);
        } else if (_draw_mode == DM_LINE) {
            _ghost_line = Line({ _ghost_line_start, sf::Vector2f(e.x, e.y) });
        }
    }
}

void Field::reset_drawing()
{
    _drawing = false;
    _ghost_ball = Ball();
    _ghost_line = Line();
    _new_ball_center = sf::Vector2f(-1, -1);
    _new_line_points.clear();
}

}