#ifndef FIELD_HPP
#define FIELD_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include "ball.hpp"
#include "drawable.hpp"
#include "handler.hpp"
#include "line.hpp"
#include "textures.hpp"

namespace my {

enum DRAW_MODE {
    DM_BALL,
    DM_LINE
};

inline DRAW_MODE switch_draw_mode(DRAW_MODE c)
{
    if (c == DM_BALL)
        return DM_LINE;
    if (c == DM_LINE)
        return DM_BALL;
    return DM_BALL;
}

class Field : public Handler, public Drawable {
public:
    Field(my::Textures texture_provider, sf::FloatRect bounding_rect);
    std::vector<std::unique_ptr<sf::Drawable>> draw_list() override;

private:
    sf::RectangleShape _bounding_rect;
    std::vector<my::Ball> _balls;
    std::vector<my::Line> _lines;

    bool _drawing = false;
    sf::Vector2f _ghost_ball_center;
    my::Ball _ghost_ball;
    my::Line _ghost_line;
    sf::Vector2f _ghost_line_start;

    my::Textures _texture_provider;

    DRAW_MODE _draw_mode = DM_LINE;

    std::vector<sf::Vector2f> _new_line_points = {};
    sf::Vector2f _new_ball_center = sf::Vector2f(-1, -1);

    void handle_drawing_ball(sf::Event::MouseButtonEvent);
    void handle_drawing_line(sf::Event::MouseButtonEvent);

    void onEvent(sf::Event) override;
    void onKeyPressed(sf::Event::KeyEvent) override;
    void onMousePressed(sf::Event::MouseButtonEvent) override;
    void onMouseMoved(sf::Event::MouseMoveEvent) override;

    void reset_drawing();
};

}

#endif