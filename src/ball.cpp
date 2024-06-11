#include <SFML/Graphics.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <unordered_map>

#include "ball.hpp"
#include "line.hpp"
#include "utility.hpp"

namespace my {

Ball::Ball()
{
    Ball(0, { 0, 0 }, 0);
}

Ball::Ball(float radius, sf::Vector2f center, bool is_ghost)
{
    _is_ghost = is_ghost;
    _radius = radius;
    _center = center;
    _last_updated = std::chrono::steady_clock::now();
    _vel = sf::Vector2f(0, 0);
    _acc = sf::Vector2f(0, 0);
    _mass = std::max(1e-4, DENSITY * my::area(_radius / PIXEL_PER_METER));
    _gravitational_force = sf::Vector2f(0, _is_ghost ? 0 : _mass * GRAVITY * PIXEL_PER_METER);

    _ball = sf::CircleShape(_radius);
    _ball.setPosition({ _center.x - _radius, _center.y - _radius });
    _ball.setFillColor(_is_ghost ? sf::Color(0, 0, 0, 100) : sf::Color::Red);
}

void Ball::update(const std::vector<Line>& lines = {})

{
    std::clock_t time_now = std::clock();
    std::chrono::duration dur = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - _last_updated);
    double secs = dur.count() / (double)1000;
    if (secs < 0.0001) {
        return;
    }

    for (auto& l : lines) {
        if (my::distance(_center, l.get_points()) <= _radius) {
            sf::Vector2f cp = closest_point_on_line(_center, l.get_points());
            sf::Vector2f normal(_center.x - cp.x, _center.y - cp.y);

            double deg = angle_between(normal, _gravitational_force);
            sf::Vector2f addn_force = vector_by_mag_angle(
                vector_mag(_gravitational_force) * cos(deg),
                angle(normal));

            deg = angle_between(normal, _vel);
            addn_force += vector_by_mag_angle(
                1.0 * vector_mag(_vel) * cos(deg) * _mass / secs,
                angle(normal));
            _force_by_obj[l.get_id()] = addn_force;

            // _vel += vector_by_mag_angle(vector_mag(_vel) * 0.1, angle(normal));
        } else {
            _force_by_obj[l.get_id()] = sf::Vector2f(0, 0);
        }
    }

    _last_updated = std::chrono::steady_clock::now();
    _force = _gravitational_force;
    for (auto& mp : _force_by_obj) {
        _force += mp.second;
    }
    _acc = sf::Vector2f(_force.x / _mass, _force.y / _mass);
    _vel += sf::Vector2f(_acc.x * secs, _acc.y * secs);
    _center += sf::Vector2f(_vel.x * secs, _vel.y * secs);

    _ball.setPosition({ _center.x - _radius, _center.y - _radius });
}

std::vector<std::unique_ptr<sf::Drawable>> Ball::draw_list()
{
    std::vector<std::unique_ptr<sf::Drawable>> ret;
    ret.push_back(std::move(std::make_unique<sf::CircleShape>(_ball)));
    return ret;
}

void Ball::setTexture(sf::Texture texture)
{
    _texture = texture;
    _ball.setTexture(&_texture);
}

void Ball::onKeyReleased(sf::Event::KeyEvent event)
{
    switch (event.scancode) {
    case ARROW_UP:
        _vel.y = 0;
        break;

    case ARROW_DOWN:
        _vel.y = 0;
        break;

    case ARROW_LEFT:
        _vel.x = 0;
        break;

    case ARROW_RIGHT:
        _vel.x = 0;
        break;

    default:
        break;
    }
}

void Ball::onKeyPressed(sf::Event::KeyEvent event)
{
    auto shift_change = [](bool boost, float& val, float scale) {
        val = (boost ? 4e3 : 2e3) * scale;
    };

    switch (event.scancode) {
    case ARROW_UP:
        shift_change(event.shift, _vel.y, -1);
        _vel.x = 0;
        break;

    case ARROW_DOWN:
        shift_change(event.shift, _vel.y, 1);
        _vel.x = 0;
        break;

    case ARROW_LEFT:
        shift_change(event.shift, _vel.x, -1);
        _vel.y = 0;
        break;

    case ARROW_RIGHT:
        shift_change(event.shift, _vel.x, 1);
        _vel.y = 0;
        break;

    default:
        break;
    }
}

}