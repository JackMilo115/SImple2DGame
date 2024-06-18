#include <SFML/Graphics.hpp>
#include "Player.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Top-Down 2D Game");
    window.setFramerateLimit(60);

    Player player;
    sf::RectangleShape obstacle;
    obstacle.setSize(sf::Vector2f(100.0f, 100.0f));
    obstacle.setFillColor(sf::Color::Cyan);
    obstacle.setPosition(100.0f, 100.0f);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player.handleInput();
        player.update();
        player.move();
        player.resolveCollision(obstacle);

        window.clear();
        player.draw(window);
        window.draw(obstacle);
        window.display();
    }

    return 0;
}