#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

#include "background.hpp"
#include "ball.hpp"
#include "field.hpp"
#include "textures.hpp"
#include "utility.hpp"

const sf::Vector2f WIN_SCALE = { 1366, 768 };

int main()
{
    my::Background background(WIN_SCALE);
    background.add_layer(my::TEXTURE::BG4);

    my::Field field(sf::FloatRect(100, 100, WIN_SCALE.x - 200, WIN_SCALE.y - 200));

    auto window = sf::RenderWindow(sf::VideoMode(WIN_SCALE.x, WIN_SCALE.y), "Physics Project");
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        for (auto event = sf::Event {}; window.pollEvent(event);) {
            switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }

            background.put(event);
            field.put(event);
        }

        window.clear();

        for (auto& drawable : background.draw_list()) {
            window.draw(*drawable);
        }
        for (auto& drawable : field.draw_list()) {
            window.draw(*drawable);
        }

        window.display();
    }

    return 0;
}
