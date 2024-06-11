#ifndef BALL_HPP
#define BALL_HPP

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "drawable.hpp"
#include "handler.hpp"
#include "identifiable.hpp"
#include "line.hpp"
#include "utility.hpp"

namespace my {

const double GRAVITY = 9.8; // in m/s^2
const double DENSITY = 10; // in Kg/m^2

enum ARROW_SCANCODE {
    ARROW_RIGHT = 86,
    ARROW_LEFT,
    ARROW_DOWN,
    ARROW_UP
};

class Ball : public Handler, public Drawable, public Identifiable {
public:
    Ball();
    Ball(float radius, sf::Vector2f pos, bool is_ghost = false);
    // Ball(const Ball& other) = delete;

    void update(const std::vector<Line>&);

    void setTexture(sf::Texture texture);

    std::vector<std::unique_ptr<sf::Drawable>> draw_list() override;

private:
    sf::Texture _texture;
    std::chrono::time_point<std::chrono::steady_clock> _last_updated;
    double _radius, _mass;
    sf::Vector2f _gravitational_force;
    sf::Vector2f _force, _acc, _vel;
    sf::Vector2f _center;
    sf::CircleShape _ball;

    bool _is_ghost;

    void onKeyReleased(sf::Event::KeyEvent event) override;
    void onKeyPressed(sf::Event::KeyEvent event) override;

    std::unordered_map<int, sf::Vector2f> _force_by_obj;
};

}

#endif